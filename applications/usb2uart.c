#include "board.h"
#include "dap_main.h"
//#include "screens.h"
//#include "lvgl_data_update.h"

/* 当前使用的串口引脚为 TX:D8  RX:D9 */
#define DAP_UART_NAME       "uart1"      /* 串口设备名称 */
/* 用于接收消息的信号量 */
static struct rt_semaphore dap_urt_rx_sem;
static rt_device_t dap_uart_dev;

// 定义全局变量，用于记录UART发送数据的长度
static volatile uint32_t g_uart_tx_transfer_length = 0;


/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&dap_urt_rx_sem);
    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    char ch;
    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while (rt_device_read(dap_uart_dev, -1, &ch, 1) != 1)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(&dap_urt_rx_sem, RT_WAITING_FOREVER);
        }
        /* 读取到的数据通过串口错位输出 */
        ch = ch + 1;
        rt_device_write(dap_uart_dev, 0, &ch, 1);
    }
}

static int chry_dap_uart_init(void)
{
    rt_err_t ret = RT_EOK;
    char str[] = "hello RT-Thread!\r\n";
  
    /* 查找串口设备 */
    dap_uart_dev = rt_device_find(DAP_UART_NAME);
    if (!dap_uart_dev)
    {
        rt_kprintf("find %s failed!\n", DAP_UART_NAME);
        return RT_ERROR;
    }
    /* 初始化信号量 */
    rt_sem_init(&dap_urt_rx_sem, "dap_urt_rx", 0, RT_IPC_FLAG_FIFO);
    /* 以读写及中断接收方式打开串口设备 */
    rt_device_open(dap_uart_dev, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(dap_uart_dev, uart_input);
    /* 发送字符串 */
    rt_device_write(dap_uart_dev, 0, str, (sizeof(str) - 1));
    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }
    return ret;
}

INIT_APP_EXPORT(chry_dap_uart_init);

// CDC UART配置回调函数
void chry_dap_usb2uart_uart_config_callback(struct cdc_line_coding *line_coding)
{

}


// CDC UART通过DMA发送数据函数
void chry_dap_usb2uart_uart_send_bydma(uint8_t *data, uint16_t len)
{

}

