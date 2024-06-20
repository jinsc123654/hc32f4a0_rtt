#include "bsp_led.h"


static const rt_base_t LED_PORT[LED_MAX_NUM] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

 /**
  -  @brief  初始化所有LED灯，并设置LED为关闭状态
  -  @note   None
  -  @param  None
  -  @retval None
 */
static int bsp_led_init(void)
{
    for (led_type_def _led = LED1; _led < LED_MAX_NUM; _led++)
    {
        rt_pin_mode(LED_PORT[_led], PIN_MODE_OUTPUT);
        bsp_led_off(_led);
    }
    
    return 0;
}
INIT_APP_EXPORT(bsp_led_init);
 /**
  -  @brief  点亮led
  -  @note   None
  -  @param  led：LED1,LED2,LED3,LED4
  -  @retval None
 */
void bsp_led_on(led_type_def led)
{
    rt_pin_write(LED_PORT[led], PIN_LOW);
}

/**
 -  @brief  熄灭led
 -  @note   None
 -  @param  led：LED1,LED2,LED3,LED4
 -  @retval None
*/
void bsp_led_off(led_type_def led)
{
    rt_pin_write(LED_PORT[led], PIN_HIGH);
}

/**
 -  @brief  翻转led
 -  @note   None
 -  @param  led：LED1,LED2,LED3,LED4
 -  @retval None
*/
void bsp_led_toggle(led_type_def led)
{
  
  rt_pin_write(LED_PORT[led], rt_pin_read(LED_PORT[led]));
}

/**
 -  @brief  获取LED状态
 -  @note   None
 -  @param  None
 -  @retval 0：LED灯熄灭，1：LED灯亮了
*/
uint8_t bsp_led_get_status(led_type_def led)
{
    uint8_t  led_status = SET;
    led_status = rt_pin_read(led);
    if (led_status == SET)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
-  @brief  让天空星多功能调试器上的led来回闪烁，每调用一次就切换成下一个灯亮
 -  @note   None
 -  @param  None
 -  @retval None
*/
void bsp_led_left_right_move(void)
{
    static int8_t led_direction = 0;
    static led_type_def _led_pos = LED1;
    if (led_direction == 0)
    {
        if (_led_pos != LED1)
        {
            bsp_led_off((led_type_def)(_led_pos - 1));
        }
        bsp_led_on(_led_pos);
        if (_led_pos >= LED4)
        {
            led_direction = 1;
        }
        _led_pos++;
    }
    else
    {
        _led_pos--;
        if (_led_pos != LED4)
        {
            bsp_led_off((led_type_def)(_led_pos + 1));
        }
        bsp_led_on(_led_pos);
        if (_led_pos <= LED1)
        {
            led_direction = 0;
        }
    }
}
