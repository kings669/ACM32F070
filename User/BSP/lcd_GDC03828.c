/*
  ******************************************************************************
  * @file    lcd_GDC03828.c
  * @author  CWT
  * @version V1.0.0
  * @date    2021
  * @brief   lcd for GDC04212 demo source code.
  *******************************************************************************/
  
  
#include "lcd_GDC03828.h"

LCD_SegComInitTypeDef   LCD_SegComInitStructure1;

LCD_HandleTypeDef       lcdhandle_GDC03828;

 GPIO_InitTypeDef GPIO_Init_GDC03828; 

/**
  @verbatim
============================================================================================================================================================
                              GDC03828 LCD 真值表
============================================================================================================================================================
屏幕参数：运行电压：5V   占空比:1/1   偏压:1/1(静态)   引脚：C0M0   SEG0-SEG39，共41个
真值表如下：
             
 
                                   A
                               ----------
                              |         |
                             F|         |B
                              |         |
                              ---- G-----          共5个
                              |         |
                             E|         |C
                              |         |   _ 
                              -----------  |_|P  
                                   D

LCD_GDC03828的PIN脚与芯片SEG COM连接关系如下：
          SEG0    SEG1    SEG2    SEG3     SEG4    SEG5    SEG6     SEG7   SEG8    SEG9    SEG10    SEG11     SEG12    SEG13    SEG14     SEG15  
  COM0  { 1A ,     1B ,    1C ,    1D ,     1E ,    1F ,    1G,     1P ,    2A ,     2B ,    2C ,    2D ,     2E ,       2F ,    2G,       2P  ........}

  
  
  如第一个位置需要显示‘0’，则需点亮以下位置
          SEG0    SEG1    SEG2    SEG3   SEG4   SEG5   SEG6    SEG7  SEG8    SEG9    SEG10    SEG11     SEG12    SEG13    SEG14     SEG15 
 COM0  {    1 ,     1 ,    1 ,    1 ,     1 ,    1 ,    0,     0 ,    0 ,     0 ,      0 ,       0 ,      0,       0 ,       0,       0  ........}


===>按照显示模式0，则需要配置LCDRAM0-15,共16个LCDRAM，且代码不易实现
===>按照显示模式1，仅需配置LCDRAM0和LCDRAM8，对应SEG0-SEG39，即LCDRAM0=0x3F;
故，此LCD驱动利用显示模式1完成
=========================================================================================================================================================
  @endverbatim
  */

uint8_t Disdata[10]={Number0,Number1,Number2,Number3,Number4,Number5,Number6,Number7,Number8,Number9};


/*********************************************************************************
* Function    : LCD_GPIO_Config
* Description : Config the GPIO of LCD use.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_GPIO_Config_GDC03828(void)//配置LCD所需的GPIO
{
    memset(&GPIO_Init_GDC03828,0,sizeof(GPIO_Init_GDC03828));//初始化清零Handle	
    GPIO_Init_GDC03828.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;	
    GPIO_Init_GDC03828.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_GDC03828);

    GPIO_Init_GDC03828.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9\
                             |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;	
    GPIO_Init_GDC03828.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_Init_GDC03828);    


    GPIO_Init_GDC03828.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_10\
                             |GPIO_PIN_11|GPIO_PIN_12;	
    GPIO_Init_GDC03828.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_GDC03828);  


    GPIO_Init_GDC03828.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_9;	
    GPIO_Init_GDC03828.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOD, &GPIO_Init_GDC03828);       
}



/*********************************************************************************
* Function    : LCD_SegCom_Config
* Description : Config the SEG and COM  of LCD use.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_SegCom_Config_GDC03828(void)//配置LCD所需的COM和SEG口
{
    /*GDC03828为静态:COM0+40个SEG:SEG0-SEG39        */
    LCD_SegComInitStructure1.SEG0_31=0x0;//开启SEG0-SEG31
    
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEG32_39_COM0_8=0xFFFFFFFF;//初始化LCD_POEN1寄存器 关闭全部输出
    
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.COM0_3=0xe;//开启COM0,关闭C0M1-COM3
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG32_35=0x0;//开启SEG32_35
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG36_COM7=0;//关闭C0M4-COM7
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG37_COM6=0;
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG38_COM5=0;
    LCD_SegComInitStructure1.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG39_COM4=0;
    
    HAL_LCD_SegComConfig(&lcdhandle_GDC03828,&LCD_SegComInitStructure1);
}


/*********************************************************************************
* Function    : LCD_Init_Config
* Description : LCD  Init Config
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_Init_GDC03828(void)
{
    memset(&lcdhandle_GDC03828,0,sizeof(lcdhandle_GDC03828));//初始化清零Handle
    lcdhandle_GDC03828.Instance=LCD;
    //lcdhandle_GDC03828.Init.Bias=LCD_BIAS_1_3;//静态模式下偏压无效，无需设置
    lcdhandle_GDC03828.Init.Duty=LCD_DUTY_STATIC;
    lcdhandle_GDC03828.Init.DisplayMode=LCD_DisplayMode_1;
    lcdhandle_GDC03828.Init.LCDFrequency=LCD_LCDFrequency_128HZ;
    lcdhandle_GDC03828.Init.BiasSrc=LCD_BiasSrc_InRes_Seg31_35_Normal;//内部电阻模式
    // lcdhandle_GDC03828.Init.Driving_Waveform=LCD_Driving_Waveform_A;//静态模式下波形类型无效，无需设置
    //lcdhandle_GDC03828.Init.BlinkEN=LCD_BlinkEN_Enable;//闪频使能
    lcdhandle_GDC03828.Init.BlinkFrequency =0x3;//帧间隔时间，影响帧中断时间和LCD DMA请求时间 以及闪烁时间
    HAL_LCD_Init(&lcdhandle_GDC03828);
    
      LCD_InResInitTypeDef  Resstrcut;
    memset(&Resstrcut,0,sizeof(Resstrcut));//初始化清零Handle
    Resstrcut.Contrast=LCD_Contrast_1000VDD;
    Resstrcut.BiasRes=LCD_BiasRes_240k;//LCD_BiasRes_240k  LCD_BiasRes_4M
    Resstrcut.FastCharge=LCD_FastCharge_Enable;//快速充电配置
    Resstrcut.PONTime=0x3f;
    Resstrcut.DriveMod=LCD_DriveMod_FC;
    HAL_LCD_InResConfig(&lcdhandle_GDC03828,&Resstrcut);
    
    LCD_GPIO_Config_GDC03828();
    LCD_SegCom_Config_GDC03828();
}


/*********************************************************************************
* Function    : LCD_DisplayNum
* Description : Display function,use to display the number.
* Input       : 
* Outpu       : 
* Author      : Chris_Kyle                         Data : 2021年
**********************************************************************************/
void LCD_DisplayNum_GDC003828(uint32_t Num)
 {
    if(Number0>99999) Num=99999;//5位数，最大显示99999
     
    int Display_1=Num/10000%10;//万位,LCD第1个位置(从左到右)
    int Display_2=Num/1000%10;//千位,LCD第2个位置(从左到右)
    int Display_3=Num/100%10;//白位,LCD第3个位置(从左到右)
    int Display_4=Num/10%10;//十位,LCD第4个位置(从左到右)
    int Display_5=Num/1%10;//个位,LCD第5个位置(从左到右)
    uint32_t data=0;
    data=(Disdata[Display_4]<<24)|(Disdata[Display_3]<<16)|(Disdata[Display_2]<<8)|(Disdata[Display_1]);
    HAL_LCD_Write(&lcdhandle_GDC03828,0,data);  ///< 显示模式1，LCDRAM0，对应SEG0-31，LCD左边4数，万+千+百+十位
    data=(Disdata[Display_5]);
    HAL_LCD_Write(&lcdhandle_GDC03828,8,data);  ///< 显示模式1， LCDRAM1，对应SEG32-39 ，LCD右边1数，个位
 }

 

