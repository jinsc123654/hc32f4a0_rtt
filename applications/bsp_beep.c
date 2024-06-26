#include <stdio.h>
#include <board.h>
#include <bsp_beep.h>

#define PWM_DEV_NAME        "pwm_a4"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL     4       /* PWM通道 */
struct rt_device_pwm *beep_pwm_dev;      /* PWM设备句柄 */

/**
 -  @brief  蜂鸣器PWM引脚初始化
 -  @note   None
 -  @param  None
 -  @retval None
   */
static void beep_driver_init(void)
{
    // servo pwm gpio init
    /* 查找设备 */
    beep_pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (beep_pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return;
    }
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(beep_pwm_dev, PWM_DEV_CHANNEL, 500000, 0);
    /* 使能设备 */
    rt_pwm_enable(beep_pwm_dev, PWM_DEV_CHANNEL);
    return;
}

/**
 -  @brief  蜂鸣器的PWM频率和周期设置
 -  @note   None
-  @param  _tone_freq:PWM频率，_volume:PWM占空比，100时蜂鸣器声音最大，代表PWM占空比为50%
 -  @retval None
   */
void buzzer_beep_set(uint16_t _tone_freq, uint8_t _volume)
{
  if(beep_pwm_dev != RT_NULL)
  {
    uint32_t _tone_time = 1000*1000*1000 / _tone_freq;/* ns与周期转换 1 / freq * 10^9 */
    rt_pwm_set(beep_pwm_dev, PWM_DEV_CHANNEL, _tone_time, _tone_time * _volume / 100);    
  }
}


/**
 -  @brief  蜂鸣器引脚和定时器初始化
 -  @note   None
 -  @param  None
 -  @retval RT_EOK
   */
static int beep_init(void)
{
    beep_driver_init();
    buzzer_beep_set(1*1000, 0);
    return 1;
}
INIT_COMPONENT_EXPORT(beep_init);
