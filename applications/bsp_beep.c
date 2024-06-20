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
#include <stdio.h>
#include <board.h>
#include <bsp_beep.h>

/**
 -  @brief  蜂鸣器PWM引脚初始化
 -  @note   None
 -  @param  None
 -  @retval None
   */
static void beep_pwm_gpio_init(void)
{
    // servo pwm gpio init

    return;
}

/**
 -  @brief  蜂鸣器定时器初始化
 -  @note   None
 -  @param  None
 -  @retval None
   */
static void beep_timer_init(void)
{
    // beep pwm timer init


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

}


/**
 -  @brief  蜂鸣器引脚和定时器初始化
 -  @note   None
 -  @param  None
 -  @retval RT_EOK
   */
int beep_init(void)
{
    beep_pwm_gpio_init();
    beep_timer_init();
    return 1;
}
INIT_PREV_EXPORT(beep_init);
