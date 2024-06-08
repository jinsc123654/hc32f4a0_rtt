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

#include "irq_config.h"
#include "board_config.h"
#include "drv_usbd.h"


#define EXAMPLE_PERIPH_WE               (LL_PERIPH_GPIO | LL_PERIPH_EFM | LL_PERIPH_FCG | \
                                         LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM)
#define EXAMPLE_PERIPH_WP               (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_SRAM)


#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    #if defined(BSP_USING_USBFS)
        /* USBFS Core*/
        #define USBF_DP_PORT                    (GPIO_PORT_A)
        #define USBF_DP_PIN                     (GPIO_PIN_12)
        #define USBF_DP_FUNC                    (GPIO_FUNC_10)
        #define USBF_DM_PORT                    (GPIO_PORT_A)
        #define USBF_DM_PIN                     (GPIO_PIN_11)
        #define USBF_DM_FUNC                    (GPIO_FUNC_10)
        #define USBF_VBUS_PORT                  (GPIO_PORT_A)
        #define USBF_VBUS_PIN                   (GPIO_PIN_09)
        #define USBF_VBUS_FUNC                  (GPIO_FUNC_10)
        #define USBF_DRVVBUS_PORT               (GPIO_PORT_C)
        #define USBF_DRVVBUS_PIN                (GPIO_PIN_09)
        #define USBF_DRVVBUS_FUNC               (GPIO_FUNC_10)
    #elif defined(BSP_USING_USBHS)
        /* USBHS Core*/
        #if defined(BSP_USING_USBHS_PHY_EMBED)
            #define USBH_DP_PORT                    (GPIO_PORT_B)
            #define USBH_DP_PIN                     (GPIO_PIN_15)
            #define USBH_DP_FUNC                    (GPIO_FUNC_10)
            #define USBH_DM_PORT                    (GPIO_PORT_B)
            #define USBH_DM_PIN                     (GPIO_PIN_14)
            #define USBH_DM_FUNC                    (GPIO_FUNC_10)
            #define USBH_VBUS_PORT                  (GPIO_PORT_B)
            #define USBH_VBUS_PIN                   (GPIO_PIN_13)
            #define USBH_VBUS_FUNC                  (GPIO_FUNC_12)
            #define USBH_DRVVBUS_PORT               (GPIO_PORT_B)
            #define USBH_DRVVBUS_PIN                (GPIO_PIN_11)
            #define USBH_DRVVBUS_FUNC               (GPIO_FUNC_10)
        #else
            /* USBHS Core, external PHY */
            #define USBH_ULPI_CLK_PORT              (GPIO_PORT_E)
            #define USBH_ULPI_CLK_PIN               (GPIO_PIN_12)
            #define USBH_ULPI_CLK_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_DIR_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_DIR_PIN               (GPIO_PIN_02)
            #define USBH_ULPI_DIR_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_NXT_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_NXT_PIN               (GPIO_PIN_03)
            #define USBH_ULPI_NXT_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_STP_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_STP_PIN               (GPIO_PIN_00)
            #define USBH_ULPI_STP_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_D0_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D0_PIN                (GPIO_PIN_13)
            #define USBH_ULPI_D0_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D1_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D1_PIN                (GPIO_PIN_14)
            #define USBH_ULPI_D1_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D2_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D2_PIN                (GPIO_PIN_15)
            #define USBH_ULPI_D2_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D3_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D3_PIN                (GPIO_PIN_10)
            #define USBH_ULPI_D3_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D4_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D4_PIN                (GPIO_PIN_11)
            #define USBH_ULPI_D4_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D5_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D5_PIN                (GPIO_PIN_12)
            #define USBH_ULPI_D5_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D6_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D6_PIN                (GPIO_PIN_13)
            #define USBH_ULPI_D6_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D7_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D7_PIN                (GPIO_PIN_11)
            #define USBH_ULPI_D7_FUNC               (GPIO_FUNC_10)
            /* 3300 reset */
            #define USB_3300_RESET_PORT             (EIO_PORT1)
            #define USB_3300_RESET_PIN              (EIO_USB3300_RST)
        #endif
    #endif
#endif


#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)

static rt_err_t usb_io_init(void)
{
    stc_gpio_init_t stcGpioCfg;
    (void)GPIO_StructInit(&stcGpioCfg);
#if defined(BSP_USING_USBFS)
    stcGpioCfg.u16PinAttr = PIN_ATTR_ANALOG;
    (void)GPIO_Init(USBF_DM_PORT, USBF_DM_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBF_DP_PORT, USBF_DP_PIN, &stcGpioCfg);
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBFS, ENABLE);
#if defined(BSP_USING_USBD)
    //GPIO_SetFunc(USBF_VBUS_PORT, USBF_VBUS_PIN, USBF_VBUS_FUNC); /* VBUS */

#endif
#if defined(BSP_USING_USBH)
    GPIO_SetFunc(USBF_DRVVBUS_PORT, USBF_DRVVBUS_PIN, USBF_DRVVBUS_FUNC); /* DRV VBUS */
#endif
#elif defined(BSP_USING_USBHS)
#if defined(BSP_USING_USBHS_PHY_EMBED)
    /* USBHS work in embedded PHY */
    stcGpioCfg.u16PinAttr = PIN_ATTR_ANALOG;
    (void)GPIO_Init(USBH_DM_PORT, USBH_DM_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_DP_PORT, USBH_DP_PIN, &stcGpioCfg);
#if defined(BSP_USING_USBD)
    GPIO_SetFunc(USBH_VBUS_PORT, USBH_VBUS_PIN, USBH_VBUS_FUNC);
#endif
#if defined(BSP_USING_USBH)
    GPIO_OutputCmd(USBH_DRVVBUS_PORT, USBH_DRVVBUS_PIN, ENABLE);
    GPIO_SetPins(USBH_DRVVBUS_PORT, USBH_DRVVBUS_PIN); /* DRV VBUS with GPIO funciton */
#endif
#else
    /* Reset 3300 */
    TCA9539_WritePin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_PIN_SET);
    TCA9539_ConfigPin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_DIR_OUT);

    (void)GPIO_StructInit(&stcGpioCfg);
    /* High drive capability */
    stcGpioCfg.u16PinDrv = PIN_HIGH_DRV;
    (void)GPIO_Init(USBH_ULPI_D0_PORT, USBH_ULPI_D0_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D1_PORT, USBH_ULPI_D1_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D2_PORT, USBH_ULPI_D2_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D3_PORT, USBH_ULPI_D3_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D4_PORT, USBH_ULPI_D4_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D5_PORT, USBH_ULPI_D5_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D6_PORT, USBH_ULPI_D6_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D7_PORT, USBH_ULPI_D7_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_STP_PORT, USBH_ULPI_STP_PIN, &stcGpioCfg);

    GPIO_SetFunc(USBH_ULPI_CLK_PORT, USBH_ULPI_CLK_PIN, USBH_ULPI_CLK_FUNC);
    GPIO_SetFunc(USBH_ULPI_DIR_PORT, USBH_ULPI_DIR_PIN, USBH_ULPI_DIR_FUNC);
    GPIO_SetFunc(USBH_ULPI_NXT_PORT, USBH_ULPI_NXT_PIN, USBH_ULPI_NXT_FUNC);
    GPIO_SetFunc(USBH_ULPI_STP_PORT, USBH_ULPI_STP_PIN, USBH_ULPI_STP_FUNC);
    GPIO_SetFunc(USBH_ULPI_D0_PORT,  USBH_ULPI_D0_PIN,  USBH_ULPI_D0_FUNC);
    GPIO_SetFunc(USBH_ULPI_D1_PORT,  USBH_ULPI_D1_PIN,  USBH_ULPI_D1_FUNC);
    GPIO_SetFunc(USBH_ULPI_D2_PORT,  USBH_ULPI_D2_PIN,  USBH_ULPI_D2_FUNC);
    GPIO_SetFunc(USBH_ULPI_D3_PORT,  USBH_ULPI_D3_PIN,  USBH_ULPI_D3_FUNC);
    GPIO_SetFunc(USBH_ULPI_D4_PORT,  USBH_ULPI_D4_PIN,  USBH_ULPI_D4_FUNC);
    GPIO_SetFunc(USBH_ULPI_D5_PORT,  USBH_ULPI_D5_PIN,  USBH_ULPI_D5_FUNC);
    GPIO_SetFunc(USBH_ULPI_D6_PORT,  USBH_ULPI_D6_PIN,  USBH_ULPI_D6_FUNC);
    GPIO_SetFunc(USBH_ULPI_D7_PORT,  USBH_ULPI_D7_PIN,  USBH_ULPI_D7_FUNC);

    TCA9539_WritePin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_PIN_RESET);
#endif

#endif
    return RT_EOK;
}
#endif

static void usbd_irq_handler(void)
{
    rt_interrupt_enter();
    extern void USBD_IRQHandler(uint8_t busid);
    USBD_IRQHandler(0);
    rt_interrupt_leave();
}

static int rt_hw_usbd_init(void)
{
    LL_PERIPH_WE(EXAMPLE_PERIPH_WE);
  
    struct hc32_irq_config irq_config;

    /* USB clock source configure */
    CLK_SetUSBClockSrc(CLK_USBCLK_SYSCLK_DIV5);
    usb_io_init();

  #if !defined(BSP_USING_USBHS)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBFS, ENABLE);
#else
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBHS, ENABLE);
#endif
    /* NVIC Config */
    irq_config.irq_num = BSP_USB_GLB_IRQ_NUM; //INT003_IRQn
#if !defined(BSP_USING_USBHS)
    irq_config.int_src = INT_SRC_USBFS_GLB;
#else
    irq_config.int_src = INT_SRC_USBHS_GLB;
#endif
    irq_config.irq_prio = BSP_USB_GLB_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             usbd_irq_handler,
                             RT_TRUE);
  
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_usbd_init);


void usb_udelay(const uint32_t usec)
{
    rt_hw_us_delay(usec);
}

void usb_mdelay(const uint32_t msec)
{
    rt_thread_mdelay(msec);
}

