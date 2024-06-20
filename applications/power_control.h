/*
* 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源
* 开发板官网：www.lckfb.com
* 技术支持常驻论坛，任何技术问题欢迎随时交流学习
* 立创论坛：club.szlcsc.com
* 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
* 不靠卖板赚钱，以培养中国工程师为己任
* Change Logs:
* Date           Author       Notes
* 2024-02-21     LCKFB-yzh    first version
*/

#ifndef __POWER_CONTROL_H__
#define __POWER_CONTROL_H__

#include "board.h"

/* defined the CH224K pin */
#define PIN_CH224K_CFG1   GET_PIN(D, 4)
#define PIN_CH224K_CFG2   GET_PIN(D, 5)
#define PIN_CH224K_CFG3   GET_PIN(D, 7)

#define PIN_PD_OUT_ENABLE GET_PIN(D, 10)
#define PIN_PD_SINK_STATE GET_PIN(C, 6)

#define PIN_3V3_OUT_ENABLE GET_PIN(E, 0)
#define PIN_5V0_OUT_ENABLE GET_PIN(E, 2)

enum POWER_SWITCH
{
    POWER_PD = 1,
    POWER_3V3,
    POWER_5V0
};

enum POWER_STATE
{
    POWER_STATE_ON = 1,
    POWER_STATE_OFF
};

enum POWER_PD_VOLTAGE
{
    POWER_PD_5V = 1,
    POWER_PD_9V,
    POWER_PD_12V,
    POWER_PD_15V,
    POWER_PD_20V
};

enum POWER_PD_SINK_STATE
{
    PD_SINK_SUCCESS = 1,
    PD_SINK_FAILED
};

void power_control_switch(enum POWER_SWITCH power_switch, enum POWER_STATE power_state);
void power_control_pd_sink_state(enum POWER_PD_VOLTAGE pd_sink_voltage);
enum POWER_PD_SINK_STATE power_control_pd_sink_check(rt_tick_t _time_out_ms);

uint8_t is_5V0_power_on(void);
uint8_t is_3V3_power_on(void);
uint8_t is_PD_power_on(void);
enum POWER_PD_VOLTAGE get_current_pd_voltage(void);

#endif /* __POWER_CONTROL_H__ */
