#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#define LCD_W 240
#define LCD_H 240


#define LCD_CLK GET_PIN(B, 13)
#define LCD_SDA GET_PIN(B, 15)

#define LCD_RST GET_PIN(E, 14)
#define LCD_DC  GET_PIN(E, 15)
#define LCD_CS  GET_PIN(B, 12)
#define LCD_BLK GET_PIN(B, 14)

//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() rt_pin_write(LCD_CLK, 0);
#define LCD_SCLK_Set() rt_pin_write(LCD_CLK, 1);
                       
#define LCD_MOSI_Clr() rt_pin_write(LCD_SDA, 0);
#define LCD_MOSI_Set() rt_pin_write(LCD_SDA, 1);
                       
#define LCD_RES_Clr()  rt_pin_write(LCD_RST, 0);
#define LCD_RES_Set()  rt_pin_write(LCD_RST, 1);
                       
#define LCD_DC_Clr()   rt_pin_write(LCD_DC, 0);
#define LCD_DC_Set()   rt_pin_write(LCD_DC, 1);
                       
#define LCD_CS_Clr()   rt_pin_write(LCD_CS, 0);
#define LCD_CS_Set()   rt_pin_write(LCD_CS, 0);
                       
#define LCD_BLK_Clr()  rt_pin_write(LCD_BLK, 1);
#define LCD_BLK_Set()  rt_pin_write(LCD_BLK, 0);




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(uint8_t dat);//模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




