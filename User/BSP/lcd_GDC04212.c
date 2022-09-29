/*
  ******************************************************************************
  * @file    lcd_GDC04212.c
  * @author  CWT
  * @version V1.0.0
  * @date    2021
  * @brief   lcd for GDC04212 demo source code.
  *******************************************************************************/
  
  
#include "lcd_GDC04212.h"

LCD_SegComInitTypeDef LCD_SegComInitStructure;

LCD_HandleTypeDef         lcdhandle_GDC04212;
  
 GPIO_InitTypeDef GPIO_Init_GDC04212; 

/**
  @verbatim
================================================================================
                              GDC04212 LCD 真值表
================================================================================
屏幕参数：运行电压：3V   占空比:1/4   偏压:1/3   引脚：C0M0-COM3   SEG0-SEG7，共12个
真值表如下：
                                   A
                               ----------
                              |         |
                             F|         |B
                              |         |
                              ---- G-----          共4个
                              |         |
                             E|         |C
                              |         |   _ 
                              -----------  |_|P  
                                   D

将LCD_GDC03828的SEG依次与芯片SEG连接，即:
          SEG0    SEG1    SEG2    SEG3     SEG4    SEG5    SEG6     SEG7  
  COM0  { 1F ,     1A ,    2F ,    2A ,     3F ,    3A ,    4F ,     4A ,}
  COM1  { 1G ,     1B ,    2G ,    2B ,     3G ,    3B ,    4G ,     4B ,}
  COM2  { 1E ,     1C ,    2E ,    2C ,     3E ,    3C ,    4E ,     4C ,}
  COM3  { P1 ,     1D ,    P2 ,    2D ,     P3 ,    3D ,    P4 ,     4D ,}
  
  
  如第一个位置需要显示‘0’，则需点亮以下位置
          SEG0    SEG1    SEG2    SEG3   SEG4   SEG5   SEG6    SEG7  
  COM0  { 1 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM1  { 0 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM2  { 1 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM3  { 0 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}

===>按照显示模式0，则只需要配置LCDRAM0，LCDRAM0=0xF05;
===>按照显示模式1，4个COM，需要配置4个LCDRAM，且代码不易实现
故，此LCD驱动利用显示模式0完成
================================================================================
  @endverbatim
  */
  
uint16_t Dis[10]={NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9};

/*********************************************************************************
* Function    : LCD_GPIO_Config
* Description : Config the GPIO of LCD use.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_GPIO_Config_GDC04212(void)//配置LCD所需的GPIO
{
    memset(&GPIO_Init_GDC04212,0,sizeof(GPIO_Init_GDC04212));//初始化清零Handl
    /* COM0-COM3:PA9-PA12  SEG0:PA8  */
    GPIO_Init_GDC04212.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_8;	
    GPIO_Init_GDC04212.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_GDC04212);//
    
    
    /* SEG1-4:PC9-6 */
    GPIO_Init_GDC04212.Pin = GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6;	
    GPIO_Init_GDC04212.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_GDC04212);    
    
    /* SEG5-7:PB15-13 */
    GPIO_Init_GDC04212.Pin = GPIO_PIN_9|GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13;	
    GPIO_Init_GDC04212.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_Init_GDC04212);     
}



/*********************************************************************************
* Function    : LCD_SegCom_Config
* Description : Config the SEG and COM  of LCD use.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_SegCom_Config_GDC04212(void)//配置LCD所需的COM和SEG口
{
    LCD_SegComInitStructure.SEG0_31=0xFFFFFF00;//开启SEG0-SEG7
    
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEG32_39_COM0_8=0xFFFFFFFF;//初始化LCD_POEN1寄存器 关闭全部输出
    
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.COM0_3=0;//开启COM0-COM3
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG32_35=0xf;//关闭SEG32_35和COM4-7
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG36_COM7=1;
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG37_COM6=1;
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG38_COM5=1;
    LCD_SegComInitStructure.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG39_COM4=1;
    
    HAL_LCD_SegComConfig(&lcdhandle_GDC04212,&LCD_SegComInitStructure);
}
/*********************************************************************************
* Function    : LCD_Init_Config
* Description : LCD  Init Config
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_Init_GDC04212(void)
{  
    memset(&lcdhandle_GDC04212,0,sizeof(lcdhandle_GDC04212));//初始化清零Handle
    lcdhandle_GDC04212.Instance=LCD;
    lcdhandle_GDC04212.Init.Bias=LCD_BIAS_1_3;
    lcdhandle_GDC04212.Init.Duty=LCD_DUTY_1_4;
    lcdhandle_GDC04212.Init.DisplayMode=LCD_DisplayMode_0;
    lcdhandle_GDC04212.Init.LCDFrequency=LCD_LCDFrequency_512HZ;
    lcdhandle_GDC04212.Init.Driving_Waveform=LCD_Driving_Waveform_A;
    lcdhandle_GDC04212.Init.BiasSrc=LCD_BiasSrc_InRes_Seg31_35_Normal;//内部电阻模式
    //   lcdhandle_GDC04212.Init.BlinkEN=LCD_BlinkEN_Enable;//闪频使能
    lcdhandle_GDC04212.Init.BlinkFrequency =0x3;//帧间隔时间，影响帧中断时间和LCD DMA请求时间 以及闪烁时间
    HAL_LCD_Init(&lcdhandle_GDC04212);
    
    LCD_InResInitTypeDef  Resstrcut;
    memset(&Resstrcut,0,sizeof(Resstrcut));//初始化清零Handle
    Resstrcut.Contrast=LCD_Contrast_903VDD;
    Resstrcut.BiasRes=LCD_BiasRes_240k;//LCD_BiasRes_240k  LCD_BiasRes_4M
    Resstrcut.FastCharge=LCD_FastCharge_Enable;//快速充电配置
    Resstrcut.PONTime=0x3f;
    Resstrcut.DriveMod=LCD_DriveMod_FC;
    HAL_LCD_InResConfig(&lcdhandle_GDC04212,&Resstrcut);
    
    
    LCD_GPIO_Config_GDC04212();
    LCD_SegCom_Config_GDC04212(); 

}


/*********************************************************************************
* Function    : LCD_DisplayNum
* Description : Display function,use to display the number.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_DisplayNum_GDC04212(uint32_t Num)
 {
    if(Num>9999) Num=9999;//4位数，最大显示9999
    int Display_1=Num/1000%10;//千位,LCD第1个位置(从左到右)
    int Display_2=Num/100%10;//白位,LCD第2个位置(从左到右)
    int Display_3=Num/10%10;//十位,LCD第3个位置(从左到右)
    int Display_4=Num/1%10;//个位,LCD第4个位置(从左到右)
    uint32_t data=0;
    data=(Dis[Display_2]<<16)|(Dis[Display_1]);
    HAL_LCD_Write(&lcdhandle_GDC04212,0,data);  ///<显示模式0，LCDRAM0，对应SEG0-3，LCD左边两数，千+百位
    data=(Dis[Display_4]<<16)|(Dis[Display_3]); 
    HAL_LCD_Write(&lcdhandle_GDC04212,1,data);  ///<显示模式0，LCDRAM1，对应SEG4-7，LCD右边两数，十+个位
 }

 

