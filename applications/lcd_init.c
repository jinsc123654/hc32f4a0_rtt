//#include "lcd_init.h"
////#include "delay.h"
//#include <drv_spi.h>
//static struct rt_spi_device *lcd_spi_dev; 
//  
//static void spi_lcd_sample(void)
//{
//    rt_hw_spi_device_attach("spi2", "spi_lcd", GPIO_PORT(LCD_CS), GPIO_PIN(LCD_CS));

//    lcd_spi_dev = (struct rt_spi_device *)rt_device_find("spi_lcd");
//    if (!lcd_spi_dev)
//    {
//        rt_kprintf("spi sample run failed! can't find %s device!\n", "spi10");
//    }
//    else
//    {
//        lcd_spi_dev->bus->owner = lcd_spi_dev; 
//        // 配置spi
//        struct rt_spi_configuration cfg;
//        cfg.data_width = 8;
//        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;  // 主机,模式0,高位在前
//        cfg.max_hz = 80 * 1000 * 1000; // SPI 接口时钟频率
//        rt_spi_configure(lcd_spi_dev, &cfg);
//    }
//}

//void LCD_GPIO_Init(void)
//{
//    spi_lcd_sample();
////    rt_pin_mode(LCD_CLK, PIN_MODE_OUTPUT);
////    rt_pin_mode(LCD_SDA, PIN_MODE_OUTPUT);
//    rt_pin_mode(LCD_CS, PIN_MODE_OUTPUT);
//    rt_pin_mode(LCD_RST, PIN_MODE_OUTPUT);
//    rt_pin_mode(LCD_DC, PIN_MODE_OUTPUT);
//    rt_pin_mode(LCD_BLK, PIN_MODE_OUTPUT);
//  
////    rt_pin_write(LCD_CLK, 1);
////    rt_pin_write(LCD_SDA, 1);
//    rt_pin_write(LCD_CS, 1);
//    rt_pin_write(LCD_RST, 1);
//    rt_pin_write(LCD_DC, 1);
//    rt_pin_write(LCD_BLK, 1);
//  
//}
//void LCD_Writ_Bus(uint8_t byte)
//{

//    struct rt_spi_message msg1;

//    msg1.send_buf   = &byte;
//    msg1.recv_buf   = RT_NULL;
//    msg1.length     = 1;
//    msg1.cs_take    = 1;
//    msg1.cs_release = 1;
//    msg1.next       = RT_NULL;

//    rt_spi_transfer_message(lcd_spi_dev, &msg1);
//}


///******************************************************************************
//      函数说明：LCD串行数据写入函数
//      入口数据：dat  要写入的串行数据
//      返回值：  无
//******************************************************************************/
////void LCD_Writ_Bus(uint8_t dat) 
////{	
////	uint8_t i;
////	LCD_CS_Clr();
////	for(i=0;i<8;i++)
////	{			  
////		LCD_SCLK_Clr();
////		if(dat&0x80)
////		{
////		   LCD_MOSI_Set();
////		}
////		else
////		{
////		   LCD_MOSI_Clr();
////		}
////		LCD_SCLK_Set();
////		dat<<=1;
////	}	
////  LCD_CS_Set();	
////}


///******************************************************************************
//      函数说明：LCD写入数据
//      入口数据：dat 写入的数据
//      返回值：  无
//******************************************************************************/
//void LCD_WR_DATA8(uint8_t dat)
//{
//    LCD_Writ_Bus(dat);
//}


///******************************************************************************
//      函数说明：LCD写入数据
//      入口数据：dat 写入的数据
//      返回值：  无
//******************************************************************************/
//void LCD_WR_DATA(uint16_t dat)
//{
//	LCD_Writ_Bus(dat>>8);
//	LCD_Writ_Bus(dat);
//}


///******************************************************************************
//      函数说明：LCD写入命令
//      入口数据：dat 写入的命令
//      返回值：  无
//******************************************************************************/
//void LCD_WR_REG(uint8_t dat)
//{
//	LCD_DC_Clr();//写命令
//	LCD_Writ_Bus(dat);
//	LCD_DC_Set();//写数据
//}


///******************************************************************************
//      函数说明：设置起始和结束地址
//      入口数据：x1,x2 设置列的起始和结束地址
//                y1,y2 设置行的起始和结束地址
//      返回值：  无
//******************************************************************************/
//void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
//{
//    if(USE_HORIZONTAL==0)
//    {
//        LCD_WR_REG(0x2a);//列地址设置
//        LCD_WR_DATA(x1);
//        LCD_WR_DATA(x2);
//        LCD_WR_REG(0x2b);//行地址设置
//        LCD_WR_DATA(y1);
//        LCD_WR_DATA(y2);
//        LCD_WR_REG(0x2c);//储存器写
//    }
//    else if(USE_HORIZONTAL==1)
//    {
//        LCD_WR_REG(0x2a);//列地址设置
//        LCD_WR_DATA(x1);
//        LCD_WR_DATA(x2);
//        LCD_WR_REG(0x2b);//行地址设置
//        LCD_WR_DATA(y1+80);
//        LCD_WR_DATA(y2+80);
//        LCD_WR_REG(0x2c);//储存器写
//    }
//    else if(USE_HORIZONTAL==2)
//    {
//        LCD_WR_REG(0x2a);//列地址设置
//        LCD_WR_DATA(x1);
//        LCD_WR_DATA(x2);
//        LCD_WR_REG(0x2b);//行地址设置
//        LCD_WR_DATA(y1);
//        LCD_WR_DATA(y2);
//        LCD_WR_REG(0x2c);//储存器写
//    }
//    else
//    {
//        LCD_WR_REG(0x2a);//列地址设置
//        LCD_WR_DATA(x1+80);
//        LCD_WR_DATA(x2+80);
//        LCD_WR_REG(0x2b);//行地址设置
//        LCD_WR_DATA(y1);
//        LCD_WR_DATA(y2);
//        LCD_WR_REG(0x2c);//储存器写
//    }
//}

//void LCD_Init(void)
//{
//    LCD_GPIO_Init();//初始化GPIO

//    LCD_RES_Clr();//复位
//    rt_thread_mdelay(100);
//    LCD_RES_Set();
//    rt_thread_mdelay(100);

//    LCD_BLK_Set();//打开背光
//    rt_thread_mdelay(100);

//    //************* Start Initial Sequence **********//
//    LCD_WR_REG(0x11); //Sleep out 
//    rt_thread_mdelay(120);              //Delay 120ms 
//    //************* Start Initial Sequence **********// 
//    LCD_WR_REG(0x36);
//    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
//    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
//    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
//    else LCD_WR_DATA8(0xA0);

//    LCD_WR_REG(0x3A);
//    LCD_WR_DATA8(0x05);

//    LCD_WR_REG(0xB2);
//    LCD_WR_DATA8(0x0C);
//    LCD_WR_DATA8(0x0C);
//    LCD_WR_DATA8(0x00);
//    LCD_WR_DATA8(0x33);
//    LCD_WR_DATA8(0x33);

//    LCD_WR_REG(0xB7);
//    LCD_WR_DATA8(0x35);

//    LCD_WR_REG(0xBB);
//    LCD_WR_DATA8(0x32); //Vcom=1.35V

//    LCD_WR_REG(0xC2);
//    LCD_WR_DATA8(0x01);

//    LCD_WR_REG(0xC3);
//    LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度

//    LCD_WR_REG(0xC4);
//    LCD_WR_DATA8(0x20); //VDV, 0x20:0v

//    LCD_WR_REG(0xC6);
//    LCD_WR_DATA8(0x0F); //0x0F:60Hz

//    LCD_WR_REG(0xD0);
//    LCD_WR_DATA8(0xA4);
//    LCD_WR_DATA8(0xA1); 

//    LCD_WR_REG(0xE0);
//    LCD_WR_DATA8(0xD0);   
//    LCD_WR_DATA8(0x08);   
//    LCD_WR_DATA8(0x0E);   
//    LCD_WR_DATA8(0x09);   
//    LCD_WR_DATA8(0x09);   
//    LCD_WR_DATA8(0x05);   
//    LCD_WR_DATA8(0x31);   
//    LCD_WR_DATA8(0x33);   
//    LCD_WR_DATA8(0x48);   
//    LCD_WR_DATA8(0x17);   
//    LCD_WR_DATA8(0x14);   
//    LCD_WR_DATA8(0x15);   
//    LCD_WR_DATA8(0x31);   
//    LCD_WR_DATA8(0x34);   

//    LCD_WR_REG(0xE1);     
//    LCD_WR_DATA8(0xD0);   
//    LCD_WR_DATA8(0x08);   
//    LCD_WR_DATA8(0x0E);   
//    LCD_WR_DATA8(0x09);   
//    LCD_WR_DATA8(0x09);   
//    LCD_WR_DATA8(0x15);   
//    LCD_WR_DATA8(0x31);   
//    LCD_WR_DATA8(0x33);   
//    LCD_WR_DATA8(0x48);   
//    LCD_WR_DATA8(0x17);   
//    LCD_WR_DATA8(0x14);   
//    LCD_WR_DATA8(0x15);   
//    LCD_WR_DATA8(0x31);   
//    LCD_WR_DATA8(0x34);
//    LCD_WR_REG(0x21); 

//    LCD_WR_REG(0x29);
//} 







