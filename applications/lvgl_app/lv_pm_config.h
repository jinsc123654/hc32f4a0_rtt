#ifndef LV_PM_CONFIG_H
#define LV_PM_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#ifdef _MSC_VER
#define user_lv_simulator
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#include "rtthread.h"
#endif

#define LV_PM_USE_STA_BAR   1   /* 是否使用状态栏 */
#define LV_PM_USE_BACK_BAR  1   /* 是否使用返回栏 */
#define LV_PM_USE_ANMI_STA  1   /* 是否在状态栏中使用动画 */
#define LV_PM_USE_ANMI_BACK 1   /* 是否在返回栏中使用动画 */


/* 给页面一个专有ID 通过编译器警告 防止打开未知界面 */
typedef enum
{
    PM_ID_HAED = 0,
    PM_ID_START_UP,
    PM_ID_DEVELOP,
    PM_ID_STANDBY,
    PM_ID_MENU,
    PM_ID_DISTR_NETWORK,/* 配网界面 */
    PM_ID_TAIL

} lv_pm_id;


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
