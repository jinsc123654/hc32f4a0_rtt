/*
* 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源
* 开发板官网：www.lckfb.com
* 技术支持常驻论坛，任何技术问题欢迎随时交流学习
* 立创论坛：club.szlcsc.com
* 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
* 不靠卖板赚钱，以培养中国工程师为己任
* Change Logs:
* Date           Author       Notes
* 2024-04-23     LCKFB-yzh    first version
*/

#ifndef __SWD_DOWLNLOAD_FILE_H__
#define __SWD_DOWLNLOAD_FILE_H__

#include "board.h"
#include "rtthread.h"

// 定义结构体来存储脱机下载信息
struct offline_download_info_t {
    uint16_t success_download_count; // 成功下载次数
    char info_message[20]; // 错误提示信息，最多20个字符
    uint8_t progress; // 进度指示，以百分比为单位
};


uint16_t get_offline_success_download_count(void);
char *get_offline_info_message(void);
uint8_t get_offline_progress(void);

int8_t is_on_offline_swd_downloading(void);

#endif /* __SWD_DOWLNLOAD_FILE_H__ */
