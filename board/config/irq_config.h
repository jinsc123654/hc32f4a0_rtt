/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __IRQ_CONFIG_H__
#define __IRQ_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_EXTINT0_IRQ_NUM             INT022_IRQn
#define BSP_EXTINT0_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT1_IRQ_NUM             INT023_IRQn
#define BSP_EXTINT1_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT2_IRQ_NUM             INT024_IRQn
#define BSP_EXTINT2_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT3_IRQ_NUM             INT025_IRQn
#define BSP_EXTINT3_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT4_IRQ_NUM             INT026_IRQn
#define BSP_EXTINT4_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT5_IRQ_NUM             INT027_IRQn
#define BSP_EXTINT5_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT6_IRQ_NUM             INT028_IRQn
#define BSP_EXTINT6_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT7_IRQ_NUM             INT029_IRQn
#define BSP_EXTINT7_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT8_IRQ_NUM             INT030_IRQn
#define BSP_EXTINT8_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT9_IRQ_NUM             INT031_IRQn
#define BSP_EXTINT9_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT10_IRQ_NUM            INT032_IRQn
#define BSP_EXTINT10_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT11_IRQ_NUM            INT033_IRQn
#define BSP_EXTINT11_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT12_IRQ_NUM            INT034_IRQn
#define BSP_EXTINT12_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT13_IRQ_NUM            INT035_IRQn
#define BSP_EXTINT13_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT14_IRQ_NUM            INT036_IRQn
#define BSP_EXTINT14_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT15_IRQ_NUM            INT037_IRQn
#define BSP_EXTINT15_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

/* DMA1 ch0 */
#define BSP_DMA1_CH0_IRQ_NUM            INT038_IRQn
#define BSP_DMA1_CH0_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch1 */
#define BSP_DMA1_CH1_IRQ_NUM            INT039_IRQn
#define BSP_DMA1_CH1_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch2 */
#define BSP_DMA1_CH2_IRQ_NUM            INT040_IRQn
#define BSP_DMA1_CH2_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch3 */
#define BSP_DMA1_CH3_IRQ_NUM            INT041_IRQn
#define BSP_DMA1_CH3_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch4 */
#define BSP_DMA1_CH4_IRQ_NUM            INT042_IRQn
#define BSP_DMA1_CH4_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch5 */
#define BSP_DMA1_CH5_IRQ_NUM            INT043_IRQn
#define BSP_DMA1_CH5_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch6 */
#define BSP_DMA1_CH6_IRQ_NUM            INT018_IRQn
#define BSP_DMA1_CH6_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch7 */
#define BSP_DMA1_CH7_IRQ_NUM            INT019_IRQn
#define BSP_DMA1_CH7_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

/* DMA2 ch0 */
#define BSP_DMA2_CH0_IRQ_NUM            INT044_IRQn
#define BSP_DMA2_CH0_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch1 */
#define BSP_DMA2_CH1_IRQ_NUM            INT045_IRQn
#define BSP_DMA2_CH1_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch2 */
#define BSP_DMA2_CH2_IRQ_NUM            INT046_IRQn
#define BSP_DMA2_CH2_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch3 */
#define BSP_DMA2_CH3_IRQ_NUM            INT047_IRQn
#define BSP_DMA2_CH3_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch4 */
#define BSP_DMA2_CH4_IRQ_NUM            INT048_IRQn
#define BSP_DMA2_CH4_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch5 */
#define BSP_DMA2_CH5_IRQ_NUM            INT049_IRQn
#define BSP_DMA2_CH5_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch6 */
#define BSP_DMA2_CH6_IRQ_NUM            INT020_IRQn
#define BSP_DMA2_CH6_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch7 */
#define BSP_DMA2_CH7_IRQ_NUM            INT021_IRQn
#define BSP_DMA2_CH7_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_USING_ETH)
#define BSP_ETH_IRQ_NUM                 INT104_IRQn
#define BSP_ETH_IRQ_PRIO                DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_UART1)
#define BSP_UART1_RXERR_IRQ_NUM         INT010_IRQn
#define BSP_UART1_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART1_RX_IRQ_NUM            INT089_IRQn
#define BSP_UART1_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART1_TX_IRQ_NUM            INT088_IRQn
#define BSP_UART1_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_UART1_RX_USING_DMA)
#define BSP_UART1_RXTO_IRQ_NUM          INT006_IRQn
#define BSP_UART1_RXTO_IRQ_PRIO         DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART1_TX_USING_DMA)
#define BSP_UART1_TX_CPLT_IRQ_NUM       INT086_IRQn
#define BSP_UART1_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#elif defined(RT_USING_SERIAL_V2)
#define BSP_UART1_TX_CPLT_IRQ_NUM       INT086_IRQn
#define BSP_UART1_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#define BSP_UART2_RXERR_IRQ_NUM         INT011_IRQn
#define BSP_UART2_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART2_RX_IRQ_NUM            INT091_IRQn
#define BSP_UART2_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART2_TX_IRQ_NUM            INT090_IRQn
#define BSP_UART2_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_UART2_RX_USING_DMA)
#define BSP_UART2_RXTO_IRQ_NUM          INT007_IRQn
#define BSP_UART2_RXTO_IRQ_PRIO         DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART2_TX_USING_DMA)
#define BSP_UART2_TX_CPLT_IRQ_NUM       INT087_IRQn
#define BSP_UART2_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#elif defined(RT_USING_SERIAL_V2)
#define BSP_UART2_TX_CPLT_IRQ_NUM       INT087_IRQn
#define BSP_UART2_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#define BSP_UART3_RXERR_IRQ_NUM         INT012_IRQn
#define BSP_UART3_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART3_RX_IRQ_NUM            INT095_IRQn
#define BSP_UART3_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART3_TX_IRQ_NUM            INT094_IRQn
#define BSP_UART3_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#define BSP_UART4_RXERR_IRQ_NUM         INT013_IRQn
#define BSP_UART4_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART4_RX_IRQ_NUM            INT097_IRQn
#define BSP_UART4_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART4_TX_IRQ_NUM            INT096_IRQn
#define BSP_UART4_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#define BSP_UART5_RXERR_IRQ_NUM         INT014_IRQn
#define BSP_UART5_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART5_RX_IRQ_NUM            INT101_IRQn
#define BSP_UART5_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART5_TX_IRQ_NUM            INT100_IRQn
#define BSP_UART5_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#define BSP_UART6_RXERR_IRQ_NUM         INT015_IRQn
#define BSP_UART6_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART6_RX_IRQ_NUM            INT103_IRQn
#define BSP_UART6_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART6_TX_IRQ_NUM            INT102_IRQn
#define BSP_UART6_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_UART6_RX_USING_DMA)
#define BSP_UART6_RXTO_IRQ_NUM          INT008_IRQn
#define BSP_UART6_RXTO_IRQ_PRIO         DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART6_TX_USING_DMA)
#define BSP_UART6_TX_CPLT_IRQ_NUM       INT099_IRQn
#define BSP_UART6_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#elif defined(RT_USING_SERIAL_V2)
#define BSP_UART6_TX_CPLT_IRQ_NUM       INT099_IRQn
#define BSP_UART6_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#define BSP_UART7_RXERR_IRQ_NUM         INT016_IRQn
#define BSP_UART7_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART7_RX_IRQ_NUM            INT107_IRQn
#define BSP_UART7_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART7_TX_IRQ_NUM            INT106_IRQn
#define BSP_UART7_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_UART7_RX_USING_DMA)
#define BSP_UART7_RXTO_IRQ_NUM          INT009_IRQn
#define BSP_UART7_RXTO_IRQ_PRIO         DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART7_TX_USING_DMA)
#define BSP_UART7_TX_CPLT_IRQ_NUM       INT105_IRQn
#define BSP_UART7_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#elif defined(RT_USING_SERIAL_V2)
#define BSP_UART7_TX_CPLT_IRQ_NUM       INT105_IRQn
#define BSP_UART7_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#elif defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2)
#define BSP_SPI1_ERR_IRQ_NUM            INT009_IRQn
#define BSP_SPI1_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_SPI2_ERR_IRQ_NUM            INT016_IRQn
#define BSP_SPI2_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_SPI3)
#define BSP_SPI3_ERR_IRQ_NUM            INT092_IRQn
#define BSP_SPI3_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_SPI4)
#define BSP_SPI4_ERR_IRQ_NUM            INT093_IRQn
#define BSP_SPI4_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_UART8)
#define BSP_UART8_RXERR_IRQ_NUM         INT017_IRQn
#define BSP_UART8_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART8_RX_IRQ_NUM            INT109_IRQn
#define BSP_UART8_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART8_TX_IRQ_NUM            INT108_IRQn
#define BSP_UART8_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#if defined(RT_USING_SERIAL_V2)
#define BSP_UART8_TX_CPLT_IRQ_NUM       INT001_IRQn
#define BSP_UART8_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART8 */

#if defined(BSP_USING_UART9)
#define BSP_UART9_RXERR_IRQ_NUM         INT112_IRQn
#define BSP_UART9_RXERR_IRQ_PRIO        DDL_IRQ_PRIO_DEFAULT
#define BSP_UART9_RX_IRQ_NUM            INT110_IRQn
#define BSP_UART9_RX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_UART9_TX_IRQ_NUM            INT111_IRQn
#define BSP_UART9_TX_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART9 */

#if defined(BSP_USING_UART10)
#define BSP_UART10_RXERR_IRQ_NUM        INT115_IRQn
#define BSP_UART10_RXERR_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#define BSP_UART10_RX_IRQ_NUM           INT114_IRQn
#define BSP_UART10_RX_IRQ_PRIO          DDL_IRQ_PRIO_DEFAULT
#define BSP_UART10_TX_IRQ_NUM           INT113_IRQn
#define BSP_UART10_TX_IRQ_PRIO          DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART10 */

#if defined(BSP_USING_CAN1)
#define BSP_CAN1_IRQ_NUM                INT092_IRQn
#define BSP_CAN1_IRQ_PRIO               DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_CAN1 */

#if defined(BSP_USING_CAN2)
#define BSP_CAN2_IRQ_NUM                INT093_IRQn
#define BSP_CAN2_IRQ_PRIO               DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_CAN2 */

#if defined(BSP_USING_SDIO1)
#define BSP_SDIO1_IRQ_NUM               INT004_IRQn
#define BSP_SDIO1_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_SDIO1 */

#if defined(BSP_USING_SDIO2)
#define BSP_SDIO2_IRQ_NUM               INT005_IRQn
#define BSP_SDIO2_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_SDIO2 */

#if defined(RT_USING_ALARM)
#define BSP_RTC_ALARM_IRQ_NUM           INT050_IRQn
#define BSP_RTC_ALARM_IRQ_PRIO          DDL_IRQ_PRIO_DEFAULT
#endif/* RT_USING_ALARM */


#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
#define BSP_USB_GLB_IRQ_NUM             INT003_IRQn
#define BSP_USB_GLB_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_USBD */

#if defined (BSP_USING_QSPI)
#define BSP_QSPI_ERR_IRQ_NUM            INT002_IRQn
#define BSP_QSPI_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_QSPI */

#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
#define BSP_PULSE_ENCODER_TMRA_1_OVF_IRQ_NUM   INT074_IRQn
#define BSP_PULSE_ENCODER_TMRA_1_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_1_UDF_IRQ_NUM   INT075_IRQn
#define BSP_PULSE_ENCODER_TMRA_1_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_1 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_2)
#define BSP_PULSE_ENCODER_TMRA_2_OVF_IRQ_NUM   INT076_IRQn
#define BSP_PULSE_ENCODER_TMRA_2_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_2_UDF_IRQ_NUM   INT077_IRQn
#define BSP_PULSE_ENCODER_TMRA_2_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_2 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_3)
#define BSP_PULSE_ENCODER_TMRA_3_OVF_IRQ_NUM   INT080_IRQn
#define BSP_PULSE_ENCODER_TMRA_3_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_3_UDF_IRQ_NUM   INT081_IRQn
#define BSP_PULSE_ENCODER_TMRA_3_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_3 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_4)
#define BSP_PULSE_ENCODER_TMRA_4_OVF_IRQ_NUM   INT082_IRQn
#define BSP_PULSE_ENCODER_TMRA_4_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_4_UDF_IRQ_NUM   INT083_IRQn
#define BSP_PULSE_ENCODER_TMRA_4_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_4 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_5)
#define BSP_PULSE_ENCODER_TMRA_5_OVF_IRQ_NUM   INT092_IRQn
#define BSP_PULSE_ENCODER_TMRA_5_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_5_UDF_IRQ_NUM   INT093_IRQn
#define BSP_PULSE_ENCODER_TMRA_5_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_5 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_6)
#define BSP_PULSE_ENCODER_TMRA_6_OVF_IRQ_NUM   INT094_IRQn
#define BSP_PULSE_ENCODER_TMRA_6_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_6_UDF_IRQ_NUM   INT095_IRQn
#define BSP_PULSE_ENCODER_TMRA_6_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_6 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_7)
#define BSP_PULSE_ENCODER_TMRA_7_OVF_IRQ_NUM   INT096_IRQn
#define BSP_PULSE_ENCODER_TMRA_7_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_7_UDF_IRQ_NUM   INT097_IRQn
#define BSP_PULSE_ENCODER_TMRA_7_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_7 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_8)
#define BSP_PULSE_ENCODER_TMRA_8_OVF_IRQ_NUM   INT096_IRQn
#define BSP_PULSE_ENCODER_TMRA_8_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_8_UDF_IRQ_NUM   INT097_IRQn
#define BSP_PULSE_ENCODER_TMRA_8_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_8 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_9)
#define BSP_PULSE_ENCODER_TMRA_9_OVF_IRQ_NUM   INT098_IRQn
#define BSP_PULSE_ENCODER_TMRA_9_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_9_UDF_IRQ_NUM   INT099_IRQn
#define BSP_PULSE_ENCODER_TMRA_9_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_9 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_10)
#define BSP_PULSE_ENCODER_TMRA_10_OVF_IRQ_NUM   INT100_IRQn
#define BSP_PULSE_ENCODER_TMRA_10_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_10_UDF_IRQ_NUM   INT101_IRQn
#define BSP_PULSE_ENCODER_TMRA_10_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_10 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_11)
#define BSP_PULSE_ENCODER_TMRA_11_OVF_IRQ_NUM   INT102_IRQn
#define BSP_PULSE_ENCODER_TMRA_11_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_11_UDF_IRQ_NUM   INT103_IRQn
#define BSP_PULSE_ENCODER_TMRA_11_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_11 */
#if defined(BSP_USING_PULSE_ENCODER_TMRA_12)
#define BSP_PULSE_ENCODER_TMRA_12_OVF_IRQ_NUM   INT102_IRQn
#define BSP_PULSE_ENCODER_TMRA_12_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMRA_12_UDF_IRQ_NUM   INT103_IRQn
#define BSP_PULSE_ENCODER_TMRA_12_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMRA_12 */

#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
#define BSP_PULSE_ENCODER_TMR6_1_OVF_IRQ_NUM   INT056_IRQn
#define BSP_PULSE_ENCODER_TMR6_1_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_1_UDF_IRQ_NUM   INT057_IRQn
#define BSP_PULSE_ENCODER_TMR6_1_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_1 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_2)
#define BSP_PULSE_ENCODER_TMR6_2_OVF_IRQ_NUM   INT058_IRQn
#define BSP_PULSE_ENCODER_TMR6_2_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_2_UDF_IRQ_NUM   INT059_IRQn
#define BSP_PULSE_ENCODER_TMR6_2_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_2 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_3)
#define BSP_PULSE_ENCODER_TMR6_3_OVF_IRQ_NUM   INT062_IRQn
#define BSP_PULSE_ENCODER_TMR6_3_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_3_UDF_IRQ_NUM   INT063_IRQn
#define BSP_PULSE_ENCODER_TMR6_3_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_3 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_4)
#define BSP_PULSE_ENCODER_TMR6_4_OVF_IRQ_NUM   INT068_IRQn
#define BSP_PULSE_ENCODER_TMR6_4_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_4_UDF_IRQ_NUM   INT069_IRQn
#define BSP_PULSE_ENCODER_TMR6_4_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_4 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_5)
#define BSP_PULSE_ENCODER_TMR6_5_OVF_IRQ_NUM   INT074_IRQn
#define BSP_PULSE_ENCODER_TMR6_5_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_5_UDF_IRQ_NUM   INT075_IRQn
#define BSP_PULSE_ENCODER_TMR6_5_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_5 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_6)
#define BSP_PULSE_ENCODER_TMR6_6_OVF_IRQ_NUM   INT076_IRQn
#define BSP_PULSE_ENCODER_TMR6_6_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_6_UDF_IRQ_NUM   INT077_IRQn
#define BSP_PULSE_ENCODER_TMR6_6_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_6 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_7)
#define BSP_PULSE_ENCODER_TMR6_7_OVF_IRQ_NUM   INT080_IRQn
#define BSP_PULSE_ENCODER_TMR6_7_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_7_UDF_IRQ_NUM   INT081_IRQn
#define BSP_PULSE_ENCODER_TMR6_7_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_7 */
#if defined(BSP_USING_PULSE_ENCODER_TMR6_8)
#define BSP_PULSE_ENCODER_TMR6_8_OVF_IRQ_NUM   INT082_IRQn
#define BSP_PULSE_ENCODER_TMR6_8_OVF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#define BSP_PULSE_ENCODER_TMR6_8_UDF_IRQ_NUM   INT083_IRQn
#define BSP_PULSE_ENCODER_TMR6_8_UDF_IRQ_PRIO  DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_PULSE_ENCODER_TMR6_8 */

#if defined(BSP_USING_TMRA_1)
#define BSP_USING_TMRA_1_IRQ_NUM        INT074_IRQn
#define BSP_USING_TMRA_1_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_1 */
#if defined(BSP_USING_TMRA_2)
#define BSP_USING_TMRA_2_IRQ_NUM        INT075_IRQn
#define BSP_USING_TMRA_2_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_2 */
#if defined(BSP_USING_TMRA_3)
#define BSP_USING_TMRA_3_IRQ_NUM        INT080_IRQn
#define BSP_USING_TMRA_3_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_3 */
#if defined(BSP_USING_TMRA_4)
#define BSP_USING_TMRA_4_IRQ_NUM        INT081_IRQn
#define BSP_USING_TMRA_4_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_4 */
#if defined(BSP_USING_TMRA_5)
#define BSP_USING_TMRA_5_IRQ_NUM        INT092_IRQn
#define BSP_USING_TMRA_5_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_5 */
#if defined(BSP_USING_TMRA_6)
#define BSP_USING_TMRA_6_IRQ_NUM        INT093_IRQn
#define BSP_USING_TMRA_6_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_6 */
#if defined(BSP_USING_TMRA_7)
#define BSP_USING_TMRA_7_IRQ_NUM        INT094_IRQn
#define BSP_USING_TMRA_7_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_7 */
#if defined(BSP_USING_TMRA_8)
#define BSP_USING_TMRA_8_IRQ_NUM        INT095_IRQn
#define BSP_USING_TMRA_8_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_8 */
#if defined(BSP_USING_TMRA_9)
#define BSP_USING_TMRA_9_IRQ_NUM        INT098_IRQn
#define BSP_USING_TMRA_9_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_9 */
#if defined(BSP_USING_TMRA_10)
#define BSP_USING_TMRA_10_IRQ_NUM       INT099_IRQn
#define BSP_USING_TMRA_10_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_10 */
#if defined(BSP_USING_TMRA_11)
#define BSP_USING_TMRA_11_IRQ_NUM       INT100_IRQn
#define BSP_USING_TMRA_11_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_11 */
#if defined(BSP_USING_TMRA_12)
#define BSP_USING_TMRA_12_IRQ_NUM       INT101_IRQn
#define BSP_USING_TMRA_12_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_12 */

#define TX_DMA1_TC3_IRQn                (INT013_IRQn)
#define SPI2_TX_CPLT_IRQn               (INT014_IRQn)
#ifdef __cplusplus
}
#endif

#endif /* __IRQ_CONFIG_H__ */
