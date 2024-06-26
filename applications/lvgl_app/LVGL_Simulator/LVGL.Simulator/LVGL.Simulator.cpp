/*
 * PROJECT:   LVGL PC Simulator using Visual Studio
 * FILE:      LVGL.Simulator.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/win32drv/win32drv.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>

bool single_display_mode_initialization()
{
    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        800,
        480,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return false;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    return true;
}

#include <process.h>

HANDLE g_window_mutex = NULL;
bool g_initialization_status = false;

#define LVGL_SIMULATOR_MAXIMUM_DISPLAYS 16
HWND g_display_window_handles[LVGL_SIMULATOR_MAXIMUM_DISPLAYS];

unsigned int __stdcall lv_win32_window_thread_entrypoint(
    void* raw_parameter)
{
    size_t display_id = *(size_t*)(raw_parameter);

    HINSTANCE instance_handle = GetModuleHandleW(NULL);
    int show_window_mode = SW_SHOW;
    HICON icon_handle = LoadIconW(instance_handle, MAKEINTRESOURCE(IDI_LVGL));
    lv_coord_t hor_res = 800;
    lv_coord_t ver_res = 450;

    wchar_t window_title[256];
    memset(window_title, 0, sizeof(window_title));
    _snwprintf(
        window_title,
        256,
        L"LVGL Simulator for Windows Desktop (Display %d)",
        display_id);

    g_display_window_handles[display_id] = lv_win32_create_display_window(
        window_title,
        hor_res,
        ver_res,
        instance_handle,
        icon_handle,
        show_window_mode);
    if (!g_display_window_handles[display_id])
    {
        return 0;
    }

    g_initialization_status = true;

    SetEvent(g_window_mutex);

    MSG message;
    while (GetMessageW(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    lv_win32_quit_signal = true;

    return 0;
}

bool multiple_display_mode_initialization()
{
    if (!lv_win32_init_window_class())
    {
        return false;
    }

    for (size_t i = 0; i < LVGL_SIMULATOR_MAXIMUM_DISPLAYS; ++i)
    {
        g_initialization_status = false;

        g_window_mutex = CreateEventExW(NULL, NULL, 0, EVENT_ALL_ACCESS);

        _beginthreadex(
            NULL,
            0,
            lv_win32_window_thread_entrypoint,
            &i,
            0,
            NULL);

        WaitForSingleObjectEx(g_window_mutex, INFINITE, FALSE);

        CloseHandle(g_window_mutex);

        if (!g_initialization_status)
        {
            return false;
        }
    }

    lv_win32_window_context_t* context = (lv_win32_window_context_t*)(
        lv_win32_get_window_context(g_display_window_handles[0]));
    if (context)
    {
        lv_win32_pointer_device_object = context->mouse_device_object;
        lv_win32_keypad_device_object = context->keyboard_device_object;
        lv_win32_encoder_device_object = context->mousewheel_device_object;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    return true;
}
#include "lv_pm/core/include/lv_pm_core.h"
#include "lv_pm/core/include/lv_pm_port.h"


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
static void anim_x_cb(void* var, int32_t v)
{
 
}
static void anim_de_cb(struct _lv_anim_t* a)
{
    LV_LOG_ERROR("动画结束");
}
int main()
{
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    lv_init();

    if (!single_display_mode_initialization())
    {
        return -1;
    }
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
    printf_all_page();

    int iii = 0;
    while (!lv_win32_quit_signal)
    {
        lv_task_handler();
        Sleep(1);
        iii++;
        if (iii == 300)
        {
            //printf("打开测试\r\n");
            //lv_pm_open_page_msg(PM_ID_START_UP, NULL);
            //printf_all_page();
        }
        //else if (iii == 600)
        //{
        //    printf("关闭测试\r\n");
        //    lv_pm_close_page_msg(NULL);
        //    printf_all_page();
        //}
        //else if (iii == 800)
        //{
        //    printf("关闭测试\r\n");
        //    lv_pm_close_page_msg(NULL);
        //    printf_all_page();
        //}
    }

    return 0;
}
