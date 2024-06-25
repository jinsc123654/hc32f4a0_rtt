#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_spi.h>
#include "board_config.h"

#define PWM_DEV_NAME        "pwm_a7"  /* 背光的PWM设备名称 */
#define PWM_DEV_CHANNEL     2         /* PWM通道 */
static struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */

// 下方配置来自 #include "board_config.h"
#define SPI2_SCK_PORT               (GPIO_PORT_B)
#define SPI2_SCK_PIN                (GPIO_PIN_13)
#define SPI2_SCK_FUNC               (GPIO_FUNC_43)
#define SPI2_MOSI_PORT              (GPIO_PORT_B)
#define SPI2_MOSI_PIN               (GPIO_PIN_15)
#define SPI2_MOSI_FUNC              (GPIO_FUNC_44)

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

/* Configuration for Example */
#define EXAMPLE_SPI_MASTER_SLAVE        (SPI_MASTER)

/* SPI definition */
#define SPI_UNIT                        (CM_SPI2)
#define SPI_CLK                         (FCG1_PERIPH_SPI2)
/* DMA definition */
#define TX_DMA_UNIT                     (CM_DMA1)
#define TX_DMA_CH                       (DMA_CH3)
#define TX_DMA_FCG_ENABLE()             (FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_DMA1, ENABLE))

#define TX_DMA_TRIG_SEL                 (AOS_DMA1_3)
#define TX_DMA_TRIG_EVT_SRC             (EVT_SRC_SPI2_SPTI)

#define TX_DMA_TC_INT                   (DMA_INT_TC_CH3)
#define TX_DMA_TC_FLAG                  (DMA_FLAG_TC_CH3)
#define TX_DMA_TC_IRQn                  (TX_DMA1_TC3_IRQn)
#define TX_DMA_TC_INT_SRC               (INT_SRC_DMA1_TC3)

/* SPI interrupt definition */
#define SPI_TX_CPLT_IRQn                (SPI2_TX_CPLT_IRQn)
#define SPI_TX_CPLT_INT_SRC             (INT_SRC_SPI2_SPII)

//#define LCD_CLK GET_PIN(B, 13)
//#define LCD_SDA GET_PIN(B, 15)
#define LCD_CS  GET_PIN(B, 12)
#define LCD_RST GET_PIN(E, 14)
#define LCD_DC  GET_PIN(E, 15)
//#define LCD_BLK GET_PIN(B, 14)
                      
#define LCD_RES_Clr()  rt_pin_write(LCD_RST, 0);
#define LCD_RES_Set()  rt_pin_write(LCD_RST, 1);
                       
#define LCD_DC_Clr()   rt_pin_write(LCD_DC, 0);
#define LCD_DC_Set()   rt_pin_write(LCD_DC, 1);
                       
#define LCD_CS_Clr()   rt_pin_write(LCD_CS, 0);
#define LCD_CS_Set()   rt_pin_write(LCD_CS, 0);
                       
#define LCD_BLK_Clr()  //rt_pin_write(LCD_BLK, 1);
#define LCD_BLK_Set()  //rt_pin_write(LCD_BLK, 0);


static volatile uint8_t dma_tx_in = 0;
static struct rt_spi_device *lcd_dev; 


/**
 * @brief  DMA transmit complete callback.
 * @param  None
 * @retval None
 */
static void TX_DMA_TC_IrqCallback(void)
{
    SPI_IntCmd(SPI_UNIT, SPI_INT_IDLE, ENABLE);
    DMA_ClearTransCompleteStatus(TX_DMA_UNIT, TX_DMA_TC_FLAG);
}

/**
 * @brief  SPI TC 束回调
 * @param  None
 * @retval None
 */
static void SPI_TxComplete_IrqCallback(void)
{
    DMA_ChCmd(TX_DMA_UNIT, TX_DMA_CH, DISABLE);
    SPI_Cmd(SPI_UNIT, DISABLE);
    SPI_IntCmd(SPI_UNIT, SPI_INT_IDLE, DISABLE);
    dma_tx_in = 0;
    extern void lv_disp_flush_ready_spi_cb(void);
    lv_disp_flush_ready_spi_cb();
}

/**
 * @brief  SPI configure.
 * @param  None
 * @retval None
 */
static void SPI_Config(void)
{
    stc_spi_init_t stcSpiInit;
    stc_gpio_init_t stcGpioInit;
    stc_irq_signin_config_t stcIrqSigninConfig;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv       = PIN_HIGH_DRV;
    //(void)GPIO_Init(SPI_SS_PORT,   SPI_SS_PIN,   &stcGpioInit);
    (void)GPIO_Init(SPI2_SCK_PORT,  SPI2_SCK_PIN,  &stcGpioInit);
    (void)GPIO_Init(SPI2_MOSI_PORT, SPI2_MOSI_PIN, &stcGpioInit);
//    (void)GPIO_Init(SPI_MISO_PORT, SPI_MISO_PIN, &stcGpioInit);

    /* Configure Port */
    //GPIO_SetFunc(SPI_SS_PORT,   SPI_SS_PIN,   SPI_SS_FUNC);
    GPIO_SetFunc(SPI2_SCK_PORT,  SPI2_SCK_PIN,  SPI2_SCK_FUNC);
    GPIO_SetFunc(SPI2_MOSI_PORT, SPI2_MOSI_PIN, SPI2_MOSI_FUNC);
//    GPIO_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC);

    /* Configuration SPI */
    FCG_Fcg1PeriphClockCmd(SPI_CLK, ENABLE);
    SPI_StructInit(&stcSpiInit);
    stcSpiInit.u32WireMode          = SPI_3_WIRE;
    stcSpiInit.u32TransMode         = SPI_SEND_ONLY;
    stcSpiInit.u32MasterSlave       = EXAMPLE_SPI_MASTER_SLAVE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVD;
    stcSpiInit.u32SpiMode           = SPI_MD_0;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV2;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    stcSpiInit.u32FrameLevel        = SPI_1_FRAME;
    (void)SPI_Init(SPI_UNIT, &stcSpiInit);
    
    
    /* Register TX complete IRQ handler. */
    stcIrqSigninConfig.enIRQn = SPI_TX_CPLT_IRQn;
    stcIrqSigninConfig.enIntSrc = SPI_TX_CPLT_INT_SRC;
    stcIrqSigninConfig.pfnCallback = &SPI_TxComplete_IrqCallback;
    (void)INTC_IrqSignIn(&stcIrqSigninConfig);
    NVIC_ClearPendingIRQ(stcIrqSigninConfig.enIRQn);
    NVIC_SetPriority(stcIrqSigninConfig.enIRQn, DDL_IRQ_PRIO_DEFAULT);
    NVIC_EnableIRQ(stcIrqSigninConfig.enIRQn);
    
    rt_pin_mode(LCD_CS, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_RST, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_DC, PIN_MODE_OUTPUT);
//    rt_pin_mode(LCD_BLK, PIN_MODE_OUTPUT);
    
    rt_pin_write(LCD_CS, 1);
    rt_pin_write(LCD_RST, 1);
    rt_pin_write(LCD_DC, 1);
//    rt_pin_write(LCD_BLK, 1);
    
}


/**
 * @brief  Initialize DMA.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       Initialization parameters is invalid.
 */
static int32_t DMA_Config(void)
{
    int32_t i32Ret;
    stc_dma_init_t stcDmaInit;
    stc_irq_signin_config_t stcIrqSignConfig;

    /* DMA&AOS FCG enable */
    TX_DMA_FCG_ENABLE();
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_AOS, ENABLE);

    /* USART_TX_DMA */
    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32IntEn = DMA_INT_ENABLE;
    stcDmaInit.u32BlockSize = 1UL;
    stcDmaInit.u32TransCount = 0;
    stcDmaInit.u32DataWidth = DMA_DATAWIDTH_8BIT;
    stcDmaInit.u32DestAddr = (uint32_t)(&SPI_UNIT->DR);
    stcDmaInit.u32SrcAddr = 0;
    stcDmaInit.u32SrcAddrInc = DMA_SRC_ADDR_INC;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    i32Ret = DMA_Init(TX_DMA_UNIT, TX_DMA_CH, &stcDmaInit);
    if (LL_OK == i32Ret) {
        stcIrqSignConfig.enIntSrc = TX_DMA_TC_INT_SRC;
        stcIrqSignConfig.enIRQn  = TX_DMA_TC_IRQn;
        stcIrqSignConfig.pfnCallback = &TX_DMA_TC_IrqCallback;
        (void)INTC_IrqSignIn(&stcIrqSignConfig);
        NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
        NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_DEFAULT);
        NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);

        AOS_SetTriggerEventSrc(TX_DMA_TRIG_SEL, TX_DMA_TRIG_EVT_SRC);

        DMA_Cmd(TX_DMA_UNIT, ENABLE);
        DMA_TransCompleteIntCmd(TX_DMA_UNIT, TX_DMA_TC_INT, ENABLE);
    }

    return i32Ret;
}

void spi_lcd_dma_send(void* src, size_t len)
{
    while(dma_tx_in == 1){};
    dma_tx_in = 1;
    SPI_Cmd(SPI_UNIT, DISABLE);
    DMA_SetSrcAddr(TX_DMA_UNIT, TX_DMA_CH, (uint32_t)(src));
    DMA_SetTransCount(TX_DMA_UNIT, TX_DMA_CH, len);

    /* Enable DMA channel */
    DMA_ChCmd(TX_DMA_UNIT, TX_DMA_CH, ENABLE);
    SPI_Cmd(SPI_UNIT, ENABLE);
}

static void spi_lcd_polling_send(void* src, size_t len)
{
    DMA_ChCmd(TX_DMA_UNIT, TX_DMA_CH, DISABLE);
    SPI_Cmd(SPI_UNIT, ENABLE);
    SPI_Trans(SPI_UNIT, src, len, 0x20000000UL);
}

static void LCD_WR_REG(uint8_t dat)
{
    LCD_DC_Clr();//写命令
    spi_lcd_polling_send(&dat, 1);
    LCD_DC_Set();//写数据
}

static void LCD_WR_DATA8(uint8_t dat)
{
    spi_lcd_polling_send(&dat, 1);
}
void LCD_WR_DATA(uint16_t dat)
{
    LCD_WR_DATA8(dat>>8);
    LCD_WR_DATA8(dat);
}


static void lcd_dev_init(void)
{
    LCD_RES_Clr();//复位
    rt_thread_mdelay(100);
    LCD_RES_Set();
    rt_thread_mdelay(100);

    LCD_CS_Clr();
    LCD_BLK_Set();//打开背光
    rt_thread_mdelay(100);

    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); //Sleep out 
    rt_thread_mdelay(120);              //Delay 120ms 
    //************* Start Initial Sequence **********// 
    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x32); //Vcom=1.35V

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20); //VDV, 0x20:0v

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x0F); //0x0F:60Hz

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1); 

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xD0);   
    LCD_WR_DATA8(0x08);   
    LCD_WR_DATA8(0x0E);   
    LCD_WR_DATA8(0x09);   
    LCD_WR_DATA8(0x09);   
    LCD_WR_DATA8(0x05);   
    LCD_WR_DATA8(0x31);   
    LCD_WR_DATA8(0x33);   
    LCD_WR_DATA8(0x48);   
    LCD_WR_DATA8(0x17);   
    LCD_WR_DATA8(0x14);   
    LCD_WR_DATA8(0x15);   
    LCD_WR_DATA8(0x31);   
    LCD_WR_DATA8(0x34);   

    LCD_WR_REG(0xE1);     
    LCD_WR_DATA8(0xD0);   
    LCD_WR_DATA8(0x08);   
    LCD_WR_DATA8(0x0E);   
    LCD_WR_DATA8(0x09);   
    LCD_WR_DATA8(0x09);   
    LCD_WR_DATA8(0x15);   
    LCD_WR_DATA8(0x31);   
    LCD_WR_DATA8(0x33);   
    LCD_WR_DATA8(0x48);   
    LCD_WR_DATA8(0x17);   
    LCD_WR_DATA8(0x14);   
    LCD_WR_DATA8(0x15);   
    LCD_WR_DATA8(0x31);   
    LCD_WR_DATA8(0x34);
    LCD_WR_REG(0x21); 

    LCD_WR_REG(0x29);
} 


void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+80);
        LCD_WR_DATA(y2+80);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
    else
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+80);
        LCD_WR_DATA(x2+80);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//储存器写
    }
}
/******************************************************************************/
/**********************************LCD 驱动框架**********************************/
/******************************************************************************/

static int lcd_device_reg(void)
{
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, 500000, 0);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    
    SPI_Config();
    DMA_Config();
    lcd_dev_init();
}
INIT_COMPONENT_EXPORT(lcd_device_reg);

