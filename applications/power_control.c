#include "power_control.h"

#define LOG_TAG     "POWER"     // 该模块对应的标签。不定义时，默认：NO_TAG
#define LOG_LVL     LOG_LVL_DBG   // 该模块对应的日志输出级别。不定义时，默认：调试级别
#include <ulog.h>                 // 必须在 LOG_TAG 与 LOG_LVL 下面



int power_control_gpio_init(void)
{
    rt_pin_mode(PIN_CH224K_CFG1, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_CH224K_CFG2, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_CH224K_CFG3, PIN_MODE_OUTPUT);

    rt_pin_mode(PIN_PD_OUT_ENABLE, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_PD_SINK_STATE, PIN_MODE_INPUT);

    rt_pin_mode(PIN_3V3_OUT_ENABLE, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_5V0_OUT_ENABLE, PIN_MODE_OUTPUT);

    // 配置PD诱骗芯片默认电压为5V,已有外部电阻确保芯片上电工作前诱骗电压也是5V
    rt_pin_write(PIN_CH224K_CFG1, PIN_HIGH);
    rt_pin_write(PIN_CH224K_CFG2, PIN_LOW);
    rt_pin_write(PIN_CH224K_CFG3, PIN_LOW);

    // 先关闭所有输出
    rt_pin_write(PIN_PD_OUT_ENABLE, PIN_LOW);
    rt_pin_write(PIN_3V3_OUT_ENABLE, PIN_LOW);
    rt_pin_write(PIN_5V0_OUT_ENABLE, PIN_LOW);

    return 1;
}
INIT_PREV_EXPORT(power_control_gpio_init);

void power_control_switch(enum POWER_SWITCH power_switch, enum POWER_STATE power_state)
{
    switch (power_switch)
    {
    case POWER_PD:
        if (power_state == POWER_STATE_ON)
        {
            rt_pin_write(PIN_PD_OUT_ENABLE, PIN_HIGH);
        }
        else
        {
            rt_pin_write(PIN_PD_OUT_ENABLE, PIN_LOW);
        }
        break;
    case POWER_3V3:
        if (power_state == POWER_STATE_ON)
        {
            rt_pin_write(PIN_3V3_OUT_ENABLE, PIN_HIGH);
        }
        else
        {
            rt_pin_write(PIN_3V3_OUT_ENABLE, PIN_LOW);
        }
        break;
    case POWER_5V0:
        if (power_state == POWER_STATE_ON)
        {
            rt_pin_write(PIN_5V0_OUT_ENABLE, PIN_HIGH);
        }
        else
        {
            rt_pin_write(PIN_5V0_OUT_ENABLE, PIN_LOW);
        }
        break;
    default:
        break;
    }
}

uint8_t is_5V0_power_on(void)
{
    if (rt_pin_read(PIN_5V0_OUT_ENABLE) == PIN_HIGH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t is_3V3_power_on(void)
{
    if (rt_pin_read(PIN_3V3_OUT_ENABLE) == PIN_HIGH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t is_PD_power_on(void)
{
    if (rt_pin_read(PIN_PD_OUT_ENABLE) == PIN_HIGH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

enum POWER_PD_VOLTAGE get_current_pd_voltage(void)
{
    if ((rt_pin_read(PIN_CH224K_CFG1) == PIN_HIGH)
        && (rt_pin_read(PIN_CH224K_CFG2) == PIN_LOW)
        && (rt_pin_read(PIN_CH224K_CFG3) == PIN_LOW))
    {
        return POWER_PD_5V;
    }
    else if ((rt_pin_read(PIN_CH224K_CFG1) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG2) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG3) == PIN_LOW))
    {
        return POWER_PD_9V;
    }
    else if ((rt_pin_read(PIN_CH224K_CFG1) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG2) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG3) == PIN_HIGH))
    {
        return POWER_PD_12V;
    }
    else if ((rt_pin_read(PIN_CH224K_CFG1) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG2) == PIN_HIGH)
             && (rt_pin_read(PIN_CH224K_CFG3) == PIN_HIGH))
    {
        return POWER_PD_15V;
    }
    else if ((rt_pin_read(PIN_CH224K_CFG1) == PIN_LOW)
             && (rt_pin_read(PIN_CH224K_CFG2) == PIN_HIGH)
             && (rt_pin_read(PIN_CH224K_CFG3) == PIN_LOW))
    {
        return POWER_PD_20V;
    }
    return POWER_PD_5V;
}

void power_control_pd_sink_state(enum POWER_PD_VOLTAGE pd_sink_voltage)
{
    switch (pd_sink_voltage)
    {
    case POWER_PD_5V:
        rt_pin_write(PIN_CH224K_CFG1, PIN_HIGH);
        rt_pin_write(PIN_CH224K_CFG2, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG3, PIN_LOW);
        break;
    case POWER_PD_9V:
        rt_pin_write(PIN_CH224K_CFG1, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG2, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG3, PIN_LOW);
        break;
    case POWER_PD_12V:
        rt_pin_write(PIN_CH224K_CFG1, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG2, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG3, PIN_HIGH);
        break;
    case POWER_PD_15V:
        rt_pin_write(PIN_CH224K_CFG1, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG2, PIN_HIGH);
        rt_pin_write(PIN_CH224K_CFG3, PIN_HIGH);
        break;
    case POWER_PD_20V:
        rt_pin_write(PIN_CH224K_CFG1, PIN_LOW);
        rt_pin_write(PIN_CH224K_CFG2, PIN_HIGH);
        rt_pin_write(PIN_CH224K_CFG3, PIN_LOW);
        break;
    default:
        break;
    }
}

enum POWER_PD_SINK_STATE power_control_pd_sink_check(rt_tick_t _time_out_ms)
{
//    static enum POWER_PD_SINK_STATE pd_sink_state = PD_SINK_FAILED;
    rt_tick_t _start_tick = rt_tick_get();
    rt_thread_mdelay(1000);
    if (rt_pin_read(PIN_PD_SINK_STATE) == PIN_LOW)
    {
        LOG_I("PD sink check success\n");
        return PD_SINK_SUCCESS;
    }
    while ((rt_pin_read(PIN_PD_SINK_STATE) == PIN_HIGH)
           && ((rt_tick_get() - _start_tick) < _time_out_ms))
    {
        if (rt_pin_read(PIN_PD_SINK_STATE) == PIN_LOW)
        {
            LOG_I("PD sink check success\n");
            return PD_SINK_SUCCESS;
        }
        rt_thread_mdelay(100);
    }
    LOG_E("PD sink check failed\n");
    return PD_SINK_FAILED;
}

static void power_control(int argc, char**argv)
{
    static uint8_t init_flag = 0;

    if(init_flag == 0)
    {
        power_control_gpio_init();
        init_flag++;
    }

    if (argc < 2)
    {
        LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
        return;
    }

    if (!rt_strcmp(argv[1], "PD"))
    {
        if(!rt_strcmp(argv[2], "ON"))
        {
            power_control_switch(POWER_PD, POWER_STATE_ON);
        }
        else if(!rt_strcmp(argv[2], "OFF"))
        {
            power_control_switch(POWER_PD, POWER_STATE_OFF);
        }else
        {
            LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
        }
    }
    else if (!rt_strcmp(argv[1], "3V3"))
    {
        if(!rt_strcmp(argv[2], "ON"))
        {
            power_control_switch(POWER_3V3, POWER_STATE_ON);
        }
        else if(!rt_strcmp(argv[2], "OFF"))
        {
            power_control_switch(POWER_3V3, POWER_STATE_OFF);
        }
        else
        {
            LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
        }
    }
    else if (!rt_strcmp(argv[1], "5V0"))
    {
        if(!rt_strcmp(argv[2], "ON"))
        {
            power_control_switch(POWER_5V0, POWER_STATE_ON);
        }
        else if(!rt_strcmp(argv[2], "OFF"))
        {
            power_control_switch(POWER_5V0, POWER_STATE_OFF);
        }
        else
        {
            LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
        }
    }
    else if (!rt_strcmp(argv[1], "PD_SINK"))
    {
        if(!rt_strcmp(argv[2], "5V"))
        {
            power_control_pd_sink_state(POWER_PD_5V);
        }
        else if(!rt_strcmp(argv[2], "9V"))
        {
            power_control_pd_sink_state(POWER_PD_9V);
        }
        else if(!rt_strcmp(argv[2], "12V"))
        {
            power_control_pd_sink_state(POWER_PD_12V);
        }
        else if(!rt_strcmp(argv[2], "15V"))
        {
            power_control_pd_sink_state(POWER_PD_15V);
        }
        else if(!rt_strcmp(argv[2], "20V"))
        {
            power_control_pd_sink_state(POWER_PD_20V);
        }
        else
        {
            LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
        }
        power_control_pd_sink_check(3000);
    }
    else
    {
        LOG_E("Please input'power_control <PD|3V3|5V0> <ON|OFF>'\n  <PD_SINK> <5V|9V|12V|15V|20V>\n");
    }
}

MSH_CMD_EXPORT(power_control, pd control sample: pd_control <5V|9V|12V|15V|20V>>);
