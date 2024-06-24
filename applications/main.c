/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_FS.h>
#include "power_control.h"

#include "lcd.h"
#include "lcd_init.h"

#define DBG_TAG               "MAIN"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

/* defined the LED_GREEN pin: PB2 */
#define LED_GREEN_PIN GET_PIN(B, 2)


__RAM_FUNC void led_tog(void)
{
    rt_pin_write(LED_GREEN_PIN, !rt_pin_read(LED_GREEN_PIN));
}

int main(void)
{
    int cnt = 0;
    /* set LED_GREEN_PIN pin mode to output */
    rt_pin_mode(LED_GREEN_PIN, PIN_MODE_OUTPUT);
    power_control_switch(POWER_3V3,POWER_STATE_ON);
  
    rt_err_t ret = RT_EOK;

    /* 挂载sd卡 */
//    while(cnt++ < 10)
//    {
//        led_tog();
//        rt_thread_mdelay(200);
//        //mkdir("/sdcard",0x777);
//        if(dfs_mount("sd","","elm",0,0)==0)
//        {
//            LOG_I("File System initialized");
//            break;
//        }
//        else
//        {
//            LOG_E("File System init failed");
//                      /* 格式化文件系统 */
//            if (RT_EOK != dfs_mkfs("elm", "sd"))
//            {
//                LOG_E("Failed to Format fs!");
//            }
//        }
//    }
    

//    /* 设置日期 */
//    ret = set_date(2024, 6, 6);
//    if (ret != RT_EOK)
//    {
//        rt_kprintf("set RTC date failed\n");
//        return ret;
//    }
//    /* 设置时间 */
//    ret = set_time(12, 00, 00);
//    if (ret != RT_EOK)
//    {
//        rt_kprintf("set RTC time failed\n");
//        return ret;
//    }

//    /* 挂载sd卡 */
//    while(cnt++ < 10)
//    {
//        rt_thread_mdelay(200);
//        mkdir("/sdcard",0x777);
//        if(dfs_mount("sd","/sdcard","elm",0,0)==0)
//        {
//            LOG_I("File System initialized");
//            break;
//        }
//        else
//        {
//            LOG_E("File System init failed");
//                      /* 格式化文件系统 */
//            if (RT_EOK != dfs_mkfs("elm", "sd"))
//            {
//                LOG_E("Failed to Format fs!");
//            }
//        }
//    }
//    cnt = 0;
    LCD_Init();
    LCD_Fill(0,0,LCD_W,LCD_H,GRAY);
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

    while (1)
    {     
        extern void bsp_led_left_right_move(void);
        //bsp_led_left_right_move();
        if(++cnt % 5 == 0)
        {
            //rt_pin_write(LED_GREEN_PIN, !rt_pin_read(LED_GREEN_PIN));
          led_tog();
        }
        rt_thread_mdelay(100);
    }
    
    return 0;
}
#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     14           /* ADC 通道 */
static const uint8_t adc_chx_arr[] = {3,                         10,           11,                         12,          13,                         14,             15                         };
static const float adc_chx_arr_x[] = {3.3f / (0.3f * 50) * 1000, 3.3f * 2.0f,  3.3f / (0.12f * 50) * 1000, 3.3f * 1.2f, 3.3f / (0.12f * 50) * 1000, 3.3f * 7.2463f, 3.3f / (0.012f * 50) * 1000};
                                      /* PD输出电流2             5V输出电压    5V输出电流                  3.3V输出电压 3.3V输出电流                PD输出电压      PD输出电流1 */
static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value;
    float vol;
    rt_err_t ret = RT_EOK;
    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }
    /* 使能设备 */
    for(int i = 0; i < sizeof(adc_chx_arr); i++)
    {
        ret = rt_adc_enable(adc_dev, adc_chx_arr[i]);
        /* 读取采样值 */
        value = rt_adc_read(adc_dev, adc_chx_arr[i]);
        rt_kprintf("the value is :%d \n", value);
        /* 转换为对应电压值,3.3V对应12位最大值4096,数据精度乘以100保留2位小数 */
        vol = value / 4095.0 * adc_chx_arr_x[i];
        rt_kprintf("ch[%d]the voltage is :%d.%02d \n", adc_chx_arr[i], (int)vol, (int)(vol*1000) % 1000);
        /* 关闭通道 */
        ret = rt_adc_disable(adc_dev, adc_chx_arr[i]);
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);

#define SAMPLE_UART_NAME       "uart1"      /* 串口设备名称 */
/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;
static rt_device_t serial;
/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);
    return RT_EOK;
}
static void serial_thread_entry(void *parameter)
{
    char ch;
    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        /* 读取到的数据通过串口错位输出 */
        ch = ch + 1;
        rt_device_write(serial, 0, &ch, 1);
    }
}
static int uart_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread!\r\n";
    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }
    /* 查找串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }
    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* 以读写及中断接收方式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);
    /* 发送字符串 */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));
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
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart_sample, uart device sample);

#define DAC_DEV_NAME        "dac1"  /* DAC 设备名称 */  
#define DAC_DEV_CHANNEL     1       /* DAC 通道 */
static rt_dac_device_t dac_dev;            /* DAC 设备句柄 */
static int dac_sample(int argc, char *argv[])
{
  static uint8_t init_flag = 0;


    if(init_flag == 0)
    {
        init_flag = 1;
        /* 查找设备 */
        dac_dev = (rt_dac_device_t)rt_device_find(DAC_DEV_NAME);
        if (dac_dev == RT_NULL)
        {
            rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
            return RT_ERROR;
        }
        /* 使能设备 */
        rt_dac_enable(dac_dev, DAC_DEV_CHANNEL);
        rt_uint32_t value = 1000;          /* DAC 数据保持寄存器值 */
        /* 输出电压值 */
        rt_dac_write(dac_dev, DAC_DEV_CHANNEL, value);
        /* 关闭通道 */
        //rt_dac_disable(dac_dev, DAC_DEV_CHANNEL);
    }
    DAC_Start(CM_DAC1, DAC_CH1);
    DAC_SetChData(CM_DAC1, DAC_CH1, 200);
    if(argc == 2)
    {
        if (dac_dev == RT_NULL)
        {
            rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
            return RT_ERROR;
        }
        rt_dac_write(dac_dev, DAC_DEV_CHANNEL, atoi(argv[1]));
    }
    
    return 0;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(dac_sample, dac device sample);
