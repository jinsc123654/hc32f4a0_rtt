/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     the first version
 * 2022-05-10     Meco Man     improve rt-thread initialization process
 */

#ifdef __RTTHREAD__

#include <lvgl.h>
#include <rtthread.h>
#include "lv_rt_thread_conf.h"
#include "lv_pm/core/include/lv_pm_core.h"
#include "lv_pm/core/include/lv_pm_port.h"
#include "lv_port_indev.h"

#define DBG_TAG    "LVGL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif /* PKG_LVGL_THREAD_STACK_SIZE */

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif /* PKG_LVGL_THREAD_PRIO */

extern void lv_port_disp_init(void);
extern void lv_port_indev_init(void);
extern void lv_user_gui_init(void);

static struct rt_thread lvgl_thread;

#ifdef rt_align
rt_align(RT_ALIGN_SIZE)
#else
ALIGN(RT_ALIGN_SIZE)
#endif
static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

#if LV_USE_LOG
static void lv_rt_log(const char *buf)
{
    LOG_I(buf);
}
#endif /* LV_USE_LOG */
static void lv_pm_set_group_init(lv_group_t* set_group)
{
    lv_group_set_default(set_group);
    lv_indev_set_group(indev_keypad, set_group);
}

static void event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        lv_pm_open_page_msg(PM_ID_START_UP, NULL);
        LV_LOG_USER("Clicked");
    }
    else if (code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}
static void page_onLoad1(void* pm_page)
{
 
    lv_obj_t* page = lv_pm_get_pm_page(pm_page)->page;
    lv_obj_t* tip_lab;

    tip_lab = lv_label_create(page);


    lv_label_set_text(tip_lab, lv_pm_get_pm_page(pm_page)->name);
    lv_obj_align(tip_lab, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* label;

    lv_obj_t* btn1 = lv_btn_create(page);
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);
    lv_pm_set_focus_obj(pm_page, btn1);

}

static void page_onLoad2(void* pm_page)
{

    lv_obj_t* page = lv_pm_get_pm_page(pm_page)->page;
    lv_obj_t* tip_lab;

    tip_lab = lv_label_create(page);


    lv_label_set_text(tip_lab, lv_pm_get_pm_page(pm_page)->name);
    lv_obj_align(tip_lab, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(page, lv_palette_main(LV_PALETTE_PURPLE)/* 默认的背景颜色 */, LV_PART_MAIN);
}


static void lvgl_thread_entry(void *parameter)
{
#if LV_USE_LOG
    lv_log_register_print_cb(lv_rt_log);
#endif /* LV_USE_LOG */
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
//    lv_user_gui_init();
//    extern void lv_demo_music(void);
//    lv_demo_music();
    set_lv_pm_set_group_default_ex(lv_pm_set_group_init);
    lv_pm_init(PM_ID_TAIL);

    lv_obj_t* label = lv_label_create(get_status_bar_cont());
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_label_set_text(label, "This is Top bar");
    lv_obj_center(label);

    label = lv_label_create(get_status_bar_main());
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_label_set_text(label, "This is Top Mian");
    lv_obj_center(label);


    lv_pm_page_t lv_pm_page_pm = 0;
    lv_pm_page_pm = lv_pm_create_page(PM_ID_HAED, "test1");
    lv_pm_set_open(lv_pm_page_pm, page_onLoad1);
    lv_pm_set_open_options(lv_pm_page_pm , &lv_pm_popup_anima, LV_PM_TARGET_NEW, 1, 1500 );
    lv_pm_page_pm->flag.top_bar_en = 1;
    lv_pm_page_pm->flag.back_bar_en = 0;
    lv_pm_page_pm = lv_pm_create_page(PM_ID_START_UP, "test2");
    lv_pm_set_open(lv_pm_page_pm, page_onLoad2);
    lv_pm_set_open_options(lv_pm_page_pm, &lv_pm_popup_anima, LV_PM_TARGET_NEW, 1, 1500);
    lv_pm_page_pm->flag.top_bar_en = 0;
    lv_pm_page_pm->flag.back_bar_en = 1;
    printf_all_page();

    lv_pm_open_page_msg(PM_ID_HAED, NULL);
  
  
    /* handle the tasks of LVGL */
    
    uint32_t tick_ms = 0;
    while(1)
    {
        tick_ms = lv_task_handler();
        rt_thread_mdelay(tick_ms);
    }
}

static int lvgl_thread_init(void)
{
    rt_err_t err;

    err = rt_thread_init(&lvgl_thread, "LVGL", lvgl_thread_entry, RT_NULL,
           &lvgl_thread_stack[0], sizeof(lvgl_thread_stack), PKG_LVGL_THREAD_PRIO, 10);
    if(err != RT_EOK)
    {
        LOG_E("Failed to create LVGL thread");
        return -1;
    }
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_ENV_EXPORT(lvgl_thread_init);

#endif /*__RTTHREAD__*/
