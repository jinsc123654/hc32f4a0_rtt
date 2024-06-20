/*
* 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源
* 开发板官网：www.lckfb.com
* 技术支持常驻论坛，任何技术问题欢迎随时交流学习
* 立创论坛：club.szlcsc.com
* 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
* 不靠卖板赚钱，以培养中国工程师为己任
* Change Logs:
* Date           Author       Notes
* 2024-02-22     LCKFB-yzh    first version
*/
#ifndef __BSP_BEEP_H__
#define __BSP_BEEP_H__

#include "stdint.h"
/* defined the beep PWM timer -*/
#define BEEP_TIMER           TIMER10
#define BEEP_TIMER_CLK       RCU_TIMER10
/* defined the beep pin: PB9 -*/
#define BEEP_GPIO_CLK      RCU_GPIOB
#define BEEP_GPIO_PORT     GPIOB
#define BEEP_GPIO_ALT_FUNC GPIO_AF_3
#define BEEP_GPIO_PUPD     GPIO_PUPD_NONE
#define BEEP_GPIO_PIN      GPIO_PIN_9


int beep_init(void);
void buzzer_beep_set(uint16_t _tone_freq, uint8_t _volume);

#endif //__BSP_BEEP_H__

