/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-18     yuanzihao    first implementation
 */

#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "dap_main.h"

#include "dap.h"
#include "swd_host.h"
#include "swd_download_file.h"


#define DAP_THREAD_PRIORITY         30
#define DAP_THREAD_TIMESLICE        20

static uint32_t IDCODE = 0x00000000;

char volatile current_dap_mode = 0;

extern  DAP_Data_t DAP_Data;           // DAP Data

extern chry_ringbuffer_t g_uartrx;
extern uint32_t g_uart_tx_transfer_length;

extern uint8_t swd_read_idcode(uint32_t *id);

void soft_reset_target(void);
static void ID_timeout(void);

rt_align(RT_ALIGN_SIZE)
__attribute__((section (".TCM"))) static char dap_thread_stack[1024];

static struct rt_thread dap_thread;
/* DAPLINK 线程 入口 */
static void dap_thread_entry(void *param)
{
    while (1)
    {
        chry_dap_handle();
        chry_dap_usb2uart_handle();

        if ((rt_tick_get() % 300 == 0)
            && (is_on_offline_swd_downloading() == 0))
        {
            ID_timeout();
        }
    }
}

/* 启动DAPLINK线程 */
int dap_thread_startup(void)
{
  rt_thread_init(&dap_thread,
                 "dap_loop",
                 dap_thread_entry,
                 RT_NULL,
                 &dap_thread_stack[0],
                 sizeof(dap_thread_stack),
                 DAP_THREAD_PRIORITY - 1, DAP_THREAD_TIMESLICE);
  rt_thread_startup(&dap_thread);

  return 0;
}

INIT_APP_EXPORT(dap_thread_startup);

void soft_reset_target(void)
{
    static uint32_t val;
    if (current_dap_mode == 1)
    {
        // Perform a soft reset
        if (!swd_read_word((0xe000e000) + 0x0D0C, &val))
        {
            rt_kprintf("swd_read_word is %x\r\n", val);
            return;
        }

        if (!swd_write_word((0xe000e000) + 0x0D0C,
                            0x05FA0000 | (val & SCB_AIRCR_PRIGROUP_Msk)
                                | 0x00000004))
        {
            rt_kprintf("swd_write_word is %x\r\n", val);
            return;
        }
    }
    rt_kprintf("!!swd_read_word is %x\r\n", val);
}

uint32_t get_idcode(void)
{
    return IDCODE;
}

/* 定时器 1 超时函数 */
static void ID_timeout(void)
{
    static uint32_t id = 0;

    if (current_dap_mode == 1)
    {
        if (swd_read_idcode(&id))
        {
            IDCODE = id;
            // rt_kprintf("chip id code is %x\r\n", id);
        }
        else
        {
            IDCODE = 0x00000000;
            // rt_kprintf("no chip\r\n");
            swd_init_debug();
        }
    }
}
