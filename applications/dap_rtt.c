#include "board.h"
#include "swd_host.h"
#include "dap_main.h"

/* 本地上行 数据缓存 */
typedef struct {
  const     char*    sName;         // Optional name. Standard names so far are: "Terminal", "SysView", "J-Scope_t4i4"
            char*    pBuffer;       // Pointer to start of buffer
            unsigned SizeOfBuffer;  // Buffer size in bytes. Note that one byte is lost, as this implementation does not fill up the buffer in order to avoid the problem of being unable to distinguish between full and empty.
            unsigned WrOff;         // Position of next item to be written by either target.
  volatile  unsigned RdOff;         // Position of next item to be read by host. Must be volatile since it may be modified by host.
            unsigned Flags;         // Contains configuration flags. Flags[31:24] are used for validity check and must be zero. Flags[23:2] are reserved for future use. Flags[1:0] = RTT operating mode.
} SEGGER_RTT_BUFFER_UP;

/* 上位机下行 数据缓存 */
typedef struct {
  const     char*    sName;         // Optional name. Standard names so far are: "Terminal", "SysView", "J-Scope_t4i4"
            char*    pBuffer;       // Pointer to start of buffer
            unsigned SizeOfBuffer;  // Buffer size in bytes. Note that one byte is lost, as this implementation does not fill up the buffer in order to avoid the problem of being unable to distinguish between full and empty.
  volatile  unsigned WrOff;         // Position of next item to be written by host. Must be volatile since it may be modified by host.
            unsigned RdOff;         // Position of next item to be read by target (down-buffer).
            unsigned Flags;         // Contains configuration flags. Flags[31:24] are used for validity check and must be zero. Flags[23:2] are reserved for future use. Flags[1:0] = RTT operating mode. 
} SEGGER_RTT_BUFFER_DOWN;

/* SEGGER RTT 控制结构体 */
typedef struct {
  char                    acID[16];                                 // Initialized to "SEGGER RTT"
  int                     MaxNumUpBuffers;                          // Initialized to SEGGER_RTT_MAX_NUM_UP_BUFFERS (type. 2)
  int                     MaxNumDownBuffers;                        // Initialized to SEGGER_RTT_MAX_NUM_DOWN_BUFFERS (type. 2)
  SEGGER_RTT_BUFFER_UP    *aUp;                                     // Up buffers, transferring information up from target via debug probe to host
  SEGGER_RTT_BUFFER_DOWN  *aDown;                                   // Down buffers, transferring information down from host via debug probe to target
#if SEGGER_RTT__CB_PADDING
  unsigned char           aDummy[SEGGER_RTT__CB_PADDING];
#endif
} SEGGER_RTT_CB;

static SEGGER_RTT_CB dap_rtt_mem;//__attribute__ ((at(0x20000000)));

#define target_rtt_add (0x20000000)
static uint32_t target_up_arr_size;
static uint32_t target_dw_arr_size;
static char* up_buff_temp;
static char* dw_buff_temp;
static uint32_t acID_head = 0;

rt_device_t get_console_device(void);

static uint8_t jlinl_dap_init_flag = 0;
void chry_dap_rtt_handle(void)
{
    static uint32_t time_tick = 0;

    if(get_idcode() != 0)
    {
        //rt_kprintf("find SEGGER RTT \r\n");
        if(jlinl_dap_init_flag == 0)
        {
            if (rt_tick_get() - time_tick > 10 && swd_read_memory(target_rtt_add, (uint8_t*)&dap_rtt_mem, (sizeof(char)*16 + sizeof(int)*2 ))  == 1)
            {
                if( rt_strcmp(dap_rtt_mem.acID, "SEGGER RTT") == 0 )
                {
                    jlinl_dap_init_flag = 1;
                    memcpy(&acID_head, dap_rtt_mem.acID, 4);
                    rt_kprintf("dap_rtt\r");
                    rt_kprintf("acID: %s\r", dap_rtt_mem.acID);
                    rt_kprintf("NumUp: %d\r", dap_rtt_mem.MaxNumUpBuffers);
                    rt_kprintf("NumDw: %d\r", dap_rtt_mem.MaxNumDownBuffers);
                    target_up_arr_size = sizeof(SEGGER_RTT_BUFFER_UP)*dap_rtt_mem.MaxNumUpBuffers;
                    target_dw_arr_size = sizeof(SEGGER_RTT_BUFFER_DOWN)*dap_rtt_mem.MaxNumDownBuffers;
                    dap_rtt_mem.aUp = rt_malloc(target_up_arr_size);
                    dap_rtt_mem.aDown = rt_malloc(target_dw_arr_size);
                    
                    /* 继续读取上行缓存 */
                    if (swd_read_memory(target_rtt_add + (sizeof(char)*16 + sizeof(int)*2 ), (uint8_t*)dap_rtt_mem.aUp, target_up_arr_size ) == 1)
                    {
                        rt_kprintf("\tNumUp->sName:s\r", dap_rtt_mem.aUp[0].sName);
                        rt_kprintf("\tNumUp->Size:d\r", dap_rtt_mem.aUp[0].SizeOfBuffer);
                        up_buff_temp = rt_malloc(dap_rtt_mem.aUp[0].SizeOfBuffer);
                        
                    }
                    /* 继续读取上行缓存 */
                    if (swd_read_memory(target_rtt_add + (sizeof(char)*16 + sizeof(int)*2 ) + target_up_arr_size, (uint8_t*)dap_rtt_mem.aDown, target_dw_arr_size ) == 1)
                    {
                        rt_kprintf("\tNumUp->sName:s\r", dap_rtt_mem.aDown[0].sName);
                        rt_kprintf("\tNumUp->Size:d\r", dap_rtt_mem.aDown[0].SizeOfBuffer);
                        dw_buff_temp = rt_malloc(dap_rtt_mem.aDown[0].SizeOfBuffer);
                    }
                }
                else
                {
                    rt_kprintf("SEGGER RTT is no find\r\n");
                }

                time_tick = rt_tick_get();
            }
        }
        
        /* 每10个tick进行一次数据读取 */
        if(0&&rt_tick_get() - time_tick > 10 )
        {
            time_tick = rt_tick_get();
            /* 保证还有jlinkrtt在目标mcu中还存在 */
            uint32_t acID_head_temp = 0;
            swd_read_word(target_rtt_add, &acID_head_temp);
            if( acID_head_temp == acID_head )
            {
                if (swd_read_memory(target_rtt_add + sizeof(char)*16 + sizeof(int)*2 + sizeof(int)*3, (uint8_t*)&(dap_rtt_mem.aUp[0].WrOff), sizeof(int)*2)  == 1)
                {
                    if(dap_rtt_mem.aUp[0].WrOff > dap_rtt_mem.aUp[0].SizeOfBuffer)
                    {
                        dap_rtt_mem.aUp[0].WrOff = dap_rtt_mem.aUp[0].SizeOfBuffer;
                    }
                    //rt_kprintf("read %d, %d\r\n", dap_rtt_mem.aUp[0].WrOff, dap_rtt_mem.aUp[0].RdOff);
                    /* 环形队列还出现从头部计数 */
                    if(dap_rtt_mem.aUp[0].WrOff > dap_rtt_mem.aUp[0].RdOff)
                    {
                        if (swd_read_memory((uint32_t)dap_rtt_mem.aUp[0].pBuffer, (uint8_t*)up_buff_temp, dap_rtt_mem.aUp[0].WrOff - dap_rtt_mem.aUp[0].RdOff)== 1)
                        {
                            swd_write_word(target_rtt_add + sizeof(char)*16 + sizeof(int)*2 + sizeof(int)*4, dap_rtt_mem.aUp[0].WrOff);
                            if(get_console_device() != RT_NULL)
                            {
                                rt_device_write(get_console_device(), 0, up_buff_temp, dap_rtt_mem.aUp[0].WrOff - dap_rtt_mem.aUp[0].RdOff);
                            }
                        }
                    }
                     /* 环形队列出现从头部计数 */
                    else if(dap_rtt_mem.aUp[0].WrOff < dap_rtt_mem.aUp[0].RdOff)
                    {
                        /* 先读取尾部 */
                        if (swd_read_memory((uint32_t)dap_rtt_mem.aUp[0].pBuffer + dap_rtt_mem.aUp[0].RdOff, (uint8_t*)up_buff_temp, dap_rtt_mem.aUp[0].SizeOfBuffer - dap_rtt_mem.aUp[0].RdOff)== 1)
                        {
                            /* 再从头部读取 */
                            if (swd_read_memory((uint32_t)dap_rtt_mem.aUp[0].pBuffer, (uint8_t*)up_buff_temp + dap_rtt_mem.aUp[0].SizeOfBuffer - dap_rtt_mem.aUp[0].RdOff, dap_rtt_mem.aUp[0].WrOff)== 1)
                            {
                                swd_write_word(target_rtt_add + sizeof(char)*16 + sizeof(int)*2 + sizeof(int)*4, dap_rtt_mem.aUp[0].WrOff);
                                if(get_console_device() != RT_NULL)
                                {
                                    rt_device_write(get_console_device(), 0, up_buff_temp, dap_rtt_mem.aUp[0].SizeOfBuffer - dap_rtt_mem.aUp[0].RdOff + dap_rtt_mem.aUp[0].WrOff);
                                }
                            }
                        }


                    }
                }
            }

        }
                                                            
    }
}

/**********************外部调用**************************/
void reinit_jlinkrtt_dap(void)
{
    jlinl_dap_init_flag = 0;

    if( dap_rtt_mem.aUp != 0 )
    {
        rt_free(dap_rtt_mem.aUp);
        dap_rtt_mem.aUp = 0;
    }

    if(dap_rtt_mem.aDown != 0)
    {
        rt_free(dap_rtt_mem.aDown);
        dap_rtt_mem.aDown = 0;
    }
    
    if(up_buff_temp != 0)
    {
        rt_free(up_buff_temp);
        up_buff_temp = 0;
    }
    
    if(dw_buff_temp != 0)
    {
        rt_free(dw_buff_temp);
        dw_buff_temp = 0;
    }

    memset(&dap_rtt_mem, 0, sizeof(dap_rtt_mem));
}
