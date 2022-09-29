/*
  ******************************************************************************
  * @file    lcd_YR1618A.c
  * @author  ZK
  * @version V1.0.0
  * @date    2022
  * @brief   lcd for YR1618A demo source code.
  *******************************************************************************/
  
  
#include "lcd_YR1618A.h"

LCD_SegComInitTypeDef LCD_SegComInitStructure2;

LCD_HandleTypeDef         lcdhandle_YR1618A;
  
 GPIO_InitTypeDef GPIO_Init_YR1618A; 

/**
  @verbatim
================================================================================
                              YR1618A LCD 真值表
================================================================================
屏幕参数：运行电压：3V   占空比:1/4   偏压:1/3   引脚：C0M0-COM3   SEG0-SEG19，共24个
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

将LCD_YR1618A的SEG与芯片SEG连接，即:
LCD_YR1618A     F030
COM0-COM0,-----,COM3-COM3
YR1618A	MCU	    PIN
SEG0	SEG0	PA8
SEG1	SEG1	PC9
SEG2	SEG2	PC8
SEG3	SEG3	PC7
SEG4	SEG4	PC6
SEG5	SEG5	PB15
SEG6	SEG6	PB14
SEG7	SEG7	PB13
SEG8	SEG8	PB12
SEG9	SEG9	PB11
SEG10	SEG15	PC4
SEG11	SEG14	PC5
SEG12	SEG22	PD5
SEG13	SEG23	PA0
SEG14	SEG19	PA4
SEG15	SEG13	PB0
SEG16	SEG25	PC2
SEG17	SEG26	PC1
SEG18	SEG24	PC3
SEG19	SEG27	PC0
  

        5	6	7	8	9	10	11	12	13	14	NC	NC	NC	20	16	15	NC	NC	NC	19	NC	NC	17	18	23	21	22	24	NC	NC	NC	NC
YR	    SEG0	SEG1	SEG2	SEG3	SEG4	SEG5	SEG6	SEG7	SEG8	SEG9	NC	NC	NC	SEG15	SEG11	SEG10	NC	NC	NC	SEG14	NC	NC	SEG12	SEG13	SEG18	SEG16	SEG17	SEG19	NC	NC	NC	NC
MCU	    SEG0	SEG1	SEG2	SEG3	SEG4	SEG5	SEG6	SEG7	SEG8	SEG9	SEG10	SEG11	SEG12	SEG13	SEG14	SEG15	SEG16	SEG17	SEG18	SEG19	SEG20	SEG21	SEG22	SEG23	SEG24	SEG25	SEG26	SEG27	SEG28	SEG29	SEG30	SEG31
COM0	1A	1B	2A	2B	3A	3B	4A	4B	S9	S10	NC	NC	NC	7B	5B	5A	NC	NC	NC	7A	NC	NC	6A	6B	S1	8A	8B	S14	NC	NC	NC	NC
COM1	1F	1G	2F	2G	3F	3G	4F	4G	S8	S11	NC	NC	NC	7G	5G	5F	NC	NC	NC	7F	NC	NC	6F	6G	S2	8F	8G	S16	NC	NC	NC	NC
COM2	1E	1C	2E	2C	3E	3C	4E	4C	S7	S12	NC	NC	NC	7C	5C	5E	NC	NC	NC	7E	NC	NC	6E	6C	S3	8E	8C	S15	NC	NC	NC	NC
COM3	1D	1P	2D	2P	3P	3P	4D	L1	S6	S5	NC	NC	NC	7P	5P	5D	NC	NC	NC	7D	NC	NC	6D	6P	S4	8D	L2	S13	NC	NC	NC	NC
  
===>按照显示模式1，4个COM，需要配置4个LCDRAM

================================================================================
  @endverbatim
  */
  
//uint16_t Dis[11]={NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,0};
uint16_t NUM123468_RAM0_DIS[11]={NUM123468_0_RAM0,NUM123468_1_RAM0,NUM123468_2_RAM0,NUM123468_3_RAM0,NUM123468_4_RAM0,NUM123468_5_RAM0,NUM123468_6_RAM0,NUM123468_7_RAM0,NUM123468_8_RAM0,NUM123468_9_RAM0,0};
uint16_t NUM123468_RAM1_DIS[11]={NUM123468_0_RAM1,NUM123468_1_RAM1,NUM123468_2_RAM1,NUM123468_3_RAM1,NUM123468_4_RAM1,NUM123468_5_RAM1,NUM123468_6_RAM1,NUM123468_7_RAM1,NUM123468_8_RAM1,NUM123468_9_RAM1,0};
uint16_t NUM123468_RAM2_DIS[11]={NUM123468_0_RAM2,NUM123468_1_RAM2,NUM123468_2_RAM2,NUM123468_3_RAM2,NUM123468_4_RAM2,NUM123468_5_RAM2,NUM123468_6_RAM2,NUM123468_7_RAM2,NUM123468_8_RAM2,NUM123468_9_RAM2,0};
uint16_t NUM123468_RAM3_DIS[11]={NUM123468_0_RAM3,NUM123468_1_RAM3,NUM123468_2_RAM3,NUM123468_3_RAM3,NUM123468_4_RAM3,NUM123468_5_RAM3,NUM123468_6_RAM3,NUM123468_7_RAM3,NUM123468_8_RAM3,NUM123468_9_RAM3,0};

uint16_t NUM5_RAM0_DIS[11]={NUM5_0_RAM0,NUM5_1_RAM0,NUM5_2_RAM0,NUM5_3_RAM0,NUM5_4_RAM0,NUM5_5_RAM0,NUM5_6_RAM0,NUM5_7_RAM0,NUM5_8_RAM0,NUM5_9_RAM0,0};
uint16_t NUM5_RAM1_DIS[11]={NUM5_0_RAM1,NUM5_1_RAM1,NUM5_2_RAM1,NUM5_3_RAM1,NUM5_4_RAM1,NUM5_5_RAM1,NUM5_6_RAM1,NUM5_7_RAM1,NUM5_8_RAM1,NUM5_9_RAM1,0};
uint16_t NUM5_RAM2_DIS[11]={NUM5_0_RAM2,NUM5_1_RAM2,NUM5_2_RAM2,NUM5_3_RAM2,NUM5_4_RAM2,NUM5_5_RAM2,NUM5_6_RAM2,NUM5_7_RAM2,NUM5_8_RAM2,NUM5_9_RAM2,0};
uint16_t NUM5_RAM3_DIS[11]={NUM5_0_RAM3,NUM5_1_RAM3,NUM5_2_RAM3,NUM5_3_RAM3,NUM5_4_RAM3,NUM5_5_RAM3,NUM5_6_RAM3,NUM5_7_RAM3,NUM5_8_RAM3,NUM5_9_RAM3,0};

uint16_t NUM7_RAM0_DIS[11]={NUM7_0_RAM0,NUM7_1_RAM0,NUM7_2_RAM0,NUM7_3_RAM0,NUM7_4_RAM0,NUM7_5_RAM0,NUM7_6_RAM0,NUM7_7_RAM0,NUM7_8_RAM0,NUM7_9_RAM0,0};
uint16_t NUM7_RAM1_DIS[11]={NUM7_0_RAM1,NUM7_1_RAM1,NUM7_2_RAM1,NUM7_3_RAM1,NUM7_4_RAM1,NUM7_5_RAM1,NUM7_6_RAM1,NUM7_7_RAM1,NUM7_8_RAM1,NUM7_9_RAM1,0};
uint16_t NUM7_RAM2_DIS[11]={NUM7_0_RAM2,NUM7_1_RAM2,NUM7_2_RAM2,NUM7_3_RAM2,NUM7_4_RAM2,NUM7_5_RAM2,NUM7_6_RAM2,NUM7_7_RAM2,NUM7_8_RAM2,NUM7_9_RAM2,0};
uint16_t NUM7_RAM3_DIS[11]={NUM7_0_RAM3,NUM7_1_RAM3,NUM7_2_RAM3,NUM7_3_RAM3,NUM7_4_RAM3,NUM7_5_RAM3,NUM7_6_RAM3,NUM7_7_RAM3,NUM7_8_RAM3,NUM7_9_RAM3,0};

uint16_t NUM_RAM_OFFSET[8]={NUM_1_OFFSET,NUM_2_OFFSET,NUM_3_OFFSET,NUM_4_OFFSET,NUM_5_OFFSET,NUM_6_OFFSET,NUM_7_OFFSET,NUM_8_OFFSET};

uint16_t NUM1236P_RAM3[2]={0,RAM3_SEG_1236P};
uint16_t NUM5P_RAM3[2]={0,RAM3_SEG_5P};
uint16_t NUM7P_RAM3[2]={0,RAM3_SEG_7P};

uint16_t COL1_RAM3[2]={0,RAM3_SEG_COL1};
uint16_t COL2_RAM3[2]={0,RAM3_SEG_COL2};

uint16_t RAM0_OFFSET_S1_9_10_14[4]={RAM0_OFFSET_S1_ID,RAM0_OFFSET_S9_WIFI4,RAM0_OFFSET_S10_UPLIM,RAM0_OFFSET_S14_BAT1};
uint16_t RAM1_OFFSET_S2_8_11_16[4]={RAM1_OFFSET_S2_C1,RAM1_OFFSET_S8_WIFI3,RAM1_OFFSET_S11_DOWNLIM,RAM1_OFFSET_S16_BAT3};
uint16_t RAM2_OFFSET_S3_7_12_15[4]={RAM2_OFFSET_S3_C2,RAM2_OFFSET_S7_WIFI2,RAM2_OFFSET_S12_BATSTATE,RAM2_OFFSET_S15_BAT2};
uint16_t RAM3_OFFSET_S4_5_6_13[4]={RAM3_OFFSET_S4_RH,RAM3_OFFSET_S5_ILINE,RAM3_OFFSET_S6_WIFI1,RAM3_OFFSET_S13_BATW};
uint16_t RAM_DATA_S[2]={0,1};

uint16_t S_DATA[16]={S1_ID,S2_C1,S3_C2,S4_RH,S5_ILINE,S6_WIFI1,S7_WIFI2,S8_WIFI3,S9_WIFI4,S10_UPLIM,S11_DOWNLIM,S12_BATSTATE,S13_BATW,S16_BAT3, S15_BAT2, S14_BAT1};

/*********************************************************************************
* Function    : LCD_GPIO_Config
* Description : Config the GPIO of LCD use.
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_GPIO_Config_YR1618A(void)//配置LCD所需的GPIO
{
    memset(&GPIO_Init_YR1618A,0,sizeof(GPIO_Init_YR1618A));//初始化清零GPIO_Init_YR1618A
    /* COM0-COM3:PA9-PA12  SEG0:PA8  */
    GPIO_Init_YR1618A.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_0;	
    GPIO_Init_YR1618A.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_YR1618A);//
    
    
    /* SEG1-4:PC9-6 */
    GPIO_Init_YR1618A.Pin = GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;	
    GPIO_Init_YR1618A.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_YR1618A);    
    
    /* SEG5-7:PB15-13 */
    GPIO_Init_YR1618A.Pin = GPIO_PIN_0|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13;	
    GPIO_Init_YR1618A.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_Init_YR1618A);  
    /* SEG5-7:PD5, =1*/
    GPIO_Init_YR1618A.Pin = GPIO_PIN_5;	
    GPIO_Init_YR1618A.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOD, &GPIO_Init_YR1618A);      
}



/*********************************************************************************
* Function    : LCD_SegCom_Config
* Description : Config the SEG and COM  of LCD use.
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_SegCom_Config_YR1618A(void)//配置LCD所需的COM和SEG口
{
    LCD_SegComInitStructure2.SEG0_31=0xF0371C00;//开启SEG0-SEG70xF0371C00
    
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEG32_39_COM0_8=0xFFFFFFFF;//初始化LCD_POEN1寄存器 关闭全部输出
    
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.COM0_3=0;//开启COM0-COM3
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG32_35=0xf;//关闭SEG32_35和COM4-7
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG36_COM7=1;
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG37_COM6=1;
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG38_COM5=1;
    LCD_SegComInitStructure2.Stc_SEG32_39_COM0_8.SEGCOM_bit.SEG39_COM4=1;
    
    HAL_LCD_SegComConfig(&lcdhandle_YR1618A,&LCD_SegComInitStructure2);
}
/*********************************************************************************
* Function    : LCD_Init_Config
* Description : LCD  Init Config
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_Init_YR1618A(void)
{  
    memset(&lcdhandle_YR1618A,0,sizeof(lcdhandle_YR1618A));//初始化清零Handle
    lcdhandle_YR1618A.Instance=LCD;
    lcdhandle_YR1618A.Init.Bias=LCD_BIAS_1_3;
    lcdhandle_YR1618A.Init.Duty=LCD_DUTY_1_4;
    lcdhandle_YR1618A.Init.DisplayMode=LCD_DisplayMode_1;
    lcdhandle_YR1618A.Init.LCDFrequency=LCD_LCDFrequency_512HZ;
    lcdhandle_YR1618A.Init.Driving_Waveform=LCD_Driving_Waveform_B;
    lcdhandle_YR1618A.Init.BiasSrc=LCD_BiasSrc_InRes_Seg31_35_Normal;//内部电阻模式
    //   lcdhandle_YR1618A.Init.BlinkEN=LCD_BlinkEN_Enable;//闪频使能
    lcdhandle_YR1618A.Init.BlinkFrequency =0x3;//帧间隔时间，影响帧中断时间和LCD DMA请求时间 以及闪烁时间
    HAL_LCD_Init(&lcdhandle_YR1618A);
    
    LCD_InResInitTypeDef  Resstrcut;
    memset(&Resstrcut,0,sizeof(Resstrcut));//初始化清零Handle
    Resstrcut.Contrast=LCD_Contrast_903VDD;
    Resstrcut.BiasRes=LCD_BiasRes_240k;//LCD_BiasRes_240k  LCD_BiasRes_4M
    Resstrcut.FastCharge=LCD_FastCharge_Enable;//快速充电配置
    Resstrcut.PONTime=0x3f;
    Resstrcut.DriveMod=LCD_DriveMod_FC;//LCD_DriveMod_FC
    HAL_LCD_InResConfig(&lcdhandle_YR1618A,&Resstrcut);
    
    
    LCD_GPIO_Config_YR1618A();
    LCD_SegCom_Config_YR1618A(); 

}

/*********************************************************************************
* Function    : LCD_DisplayNum
* Description : Display function,use to display the number.
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_DisplayNum_YR1618A(uint32_t Num)
 {
    
    uint32_t ram_buff[4];
    ram_buff[0]=0;
    ram_buff[1]=0;
    ram_buff[2]=0;
    ram_buff[3]=0;

    if(Num>9999) Num=9999;//4位数，最大显示9999
    Get_RAM_NUM_DATA(ram_buff,Num,Num);
    HAL_LCD_Write(&lcdhandle_YR1618A,0,ram_buff[0]);
    HAL_LCD_Write(&lcdhandle_YR1618A,1,ram_buff[1]);
    HAL_LCD_Write(&lcdhandle_YR1618A,2,ram_buff[2]);
    HAL_LCD_Write(&lcdhandle_YR1618A,3,ram_buff[3]);
 }
/*********************************************************************************
* Function    : LCD_DisplayNum
* Description : Display function,use to display the number.
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_DisplayNum_YR1618A_INIT()
{
    uint16_t i=0; 
    uint32_t ram_buff[4];
    uint16_t numi=6;//5
    
    for(numi=0;numi<8;numi++)
    {
        
        for(i=0;i<10;i++)
        {
            ram_buff[0]=0;
            ram_buff[1]=0;
            ram_buff[2]=0;
            ram_buff[3]=0;
            if(numi==4)
            {
            ram_buff[0]=NUM5_RAM0_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[1]=NUM5_RAM1_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[2]=NUM5_RAM2_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[3]=NUM5_RAM3_DIS[i]<<NUM_RAM_OFFSET[numi];
            }
            else if(numi==6)
            {
            ram_buff[0]=NUM7_RAM0_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[1]=NUM7_RAM1_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[2]=NUM7_RAM2_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[3]=NUM7_RAM3_DIS[i]<<NUM_RAM_OFFSET[numi];
            }
            else
            {
            ram_buff[0]=NUM123468_RAM0_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[1]=NUM123468_RAM1_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[2]=NUM123468_RAM2_DIS[i]<<NUM_RAM_OFFSET[numi];
            ram_buff[3]=NUM123468_RAM3_DIS[i]<<NUM_RAM_OFFSET[numi];
            }
            HAL_LCD_Write(&lcdhandle_YR1618A,0,ram_buff[0]);
            HAL_LCD_Write(&lcdhandle_YR1618A,1,ram_buff[1]);
            HAL_LCD_Write(&lcdhandle_YR1618A,2,ram_buff[2]);
            HAL_LCD_Write(&lcdhandle_YR1618A,3,ram_buff[3]);
            System_Delay_MS(100);//初始化时每个项显示时间，方便检测每一段显示状态
        }
    }
}
  /*********************************************************************************
* Function    : Get_RAM_NUM_DATA
* Description : Get_RAM_NUM_DATA.
* Input       : ram_num:RAM0-RAM3;num_up:0000-9999.num_down:0000-9999
* Outpu       : 
* Author      : ZK                             Data : 2022年
**********************************************************************************/
void Get_RAM_NUM_DATA(uint32_t *ram_updata,uint16_t num_up,uint16_t num_down)
{
	if(num_up>9999) num_up=9999;//4位数，最大显示9999
	int Displayup_1=num_up/1000%10;//千位,LCD第1个位置(从左到右)------1
	int Displayup_2=num_up/100%10;//白位,LCD第2个位置(从左到右)-------2
	int Displayup_3=num_up/10%10;//十位,LCD第3个位置(从左到右)--------3
	int Displayup_4=num_up/1%10;//个位,LCD第4个位置(从左到右)---------4
    
    if(num_down>9999) num_down=9999;//4位数，最大显示9999
	int Displaydown_1=num_down/1000%10;//千位,LCD第1个位置(从左到右)--5
	int Displaydown_2=num_down/100%10;//白位,LCD第2个位置(从左到右)---6
	int Displaydown_3=num_down/10%10;//十位,LCD第3个位置(从左到右)----7
	int Displaydown_4=num_down/1%10;//个位,LCD第4个位置(从左到右)-----8
    //ram0
    ram_updata[0] =(NUM123468_RAM0_DIS[Displayup_1]<<NUM_1_OFFSET)+(NUM123468_RAM0_DIS[Displayup_2]<<NUM_2_OFFSET)+(NUM123468_RAM0_DIS[Displayup_3]<<NUM_3_OFFSET)+(NUM123468_RAM0_DIS[Displayup_4]<<NUM_4_OFFSET);
    ram_updata[0] +=(NUM5_RAM0_DIS[Displaydown_1]<<NUM_5_OFFSET)+(NUM123468_RAM0_DIS[Displaydown_2]<<NUM_6_OFFSET)+(NUM7_RAM0_DIS[Displaydown_3]<<NUM_7_OFFSET)+(NUM123468_RAM0_DIS[Displaydown_4]<<NUM_8_OFFSET);
    //ram1
    ram_updata[1] =(NUM123468_RAM1_DIS[Displayup_1]<<NUM_1_OFFSET)+(NUM123468_RAM1_DIS[Displayup_2]<<NUM_2_OFFSET)+(NUM123468_RAM1_DIS[Displayup_3]<<NUM_3_OFFSET)+(NUM123468_RAM1_DIS[Displayup_4]<<NUM_4_OFFSET);
    ram_updata[1] +=(NUM5_RAM1_DIS[Displaydown_1]<<NUM_5_OFFSET)+(NUM123468_RAM1_DIS[Displaydown_2]<<NUM_6_OFFSET)+(NUM7_RAM1_DIS[Displaydown_3]<<NUM_7_OFFSET)+(NUM123468_RAM1_DIS[Displaydown_4]<<NUM_8_OFFSET);
    //ram2
    ram_updata[2] =(NUM123468_RAM2_DIS[Displayup_1]<<NUM_1_OFFSET)+(NUM123468_RAM2_DIS[Displayup_2]<<NUM_2_OFFSET)+(NUM123468_RAM2_DIS[Displayup_3]<<NUM_3_OFFSET)+(NUM123468_RAM2_DIS[Displayup_4]<<NUM_4_OFFSET);
    ram_updata[2] +=(NUM5_RAM2_DIS[Displaydown_1]<<NUM_5_OFFSET)+(NUM123468_RAM2_DIS[Displaydown_2]<<NUM_6_OFFSET)+(NUM7_RAM2_DIS[Displaydown_3]<<NUM_7_OFFSET)+(NUM123468_RAM2_DIS[Displaydown_4]<<NUM_8_OFFSET);
    //ram3
    ram_updata[3] =(NUM123468_RAM3_DIS[Displayup_1]<<NUM_1_OFFSET)+(NUM123468_RAM3_DIS[Displayup_2]<<NUM_2_OFFSET)+(NUM123468_RAM3_DIS[Displayup_3]<<NUM_3_OFFSET)+(NUM123468_RAM3_DIS[Displayup_4]<<NUM_4_OFFSET);
    ram_updata[3] +=(NUM5_RAM3_DIS[Displaydown_1]<<NUM_5_OFFSET)+(NUM123468_RAM3_DIS[Displaydown_2]<<NUM_6_OFFSET)+(NUM7_RAM3_DIS[Displaydown_3]<<NUM_7_OFFSET)+(NUM123468_RAM3_DIS[Displaydown_4]<<NUM_8_OFFSET);    
}

  /*********************************************************************************
* Function    : LCD_YR1618A_VIEW
* Description : LCD_YR1618A_VIEW.
* Input       : Displayup/Displaydown:[0]-[3]=1-4/5-8(0-9=显示,10=不显示);num_123567p:[0]-[5]=1,2,3,5,6,7(1=显示,0=不显示);num_col:[0]-[1]=COL1-COL2(1=显示,0=不显示);
              : num_s:BIT[0]-[15]=S1-S16(1=显示,0=不显示)
* Output      : 
* Author      : ZK                             Data : 2022年
**********************************************************************************/
void LCD_YR1618A_VIEW(uint32_t *Displayup,uint32_t *Displaydown,uint32_t *num_123567p,uint32_t *num_col,uint32_t num_s)
{
    uint32_t ram_updata[4];
    //num
    ram_updata[0] =(NUM123468_RAM0_DIS[Displayup[0]]<<NUM_1_OFFSET)|(NUM123468_RAM0_DIS[Displayup[1]]<<NUM_2_OFFSET)|(NUM123468_RAM0_DIS[Displayup[2]]<<NUM_3_OFFSET)|(NUM123468_RAM0_DIS[Displayup[3]]<<NUM_4_OFFSET);
    ram_updata[0] |=(NUM5_RAM0_DIS[Displaydown[0]]<<NUM_5_OFFSET)|(NUM123468_RAM0_DIS[Displaydown[1]]<<NUM_6_OFFSET)|(NUM7_RAM0_DIS[Displaydown[2]]<<NUM_7_OFFSET)|(NUM123468_RAM0_DIS[Displaydown[3]]<<NUM_8_OFFSET);
    //ram1
    ram_updata[1] =(NUM123468_RAM1_DIS[Displayup[0]]<<NUM_1_OFFSET)|(NUM123468_RAM1_DIS[Displayup[1]]<<NUM_2_OFFSET)|(NUM123468_RAM1_DIS[Displayup[2]]<<NUM_3_OFFSET)|(NUM123468_RAM1_DIS[Displayup[3]]<<NUM_4_OFFSET);
    ram_updata[1] |=(NUM5_RAM1_DIS[Displaydown[0]]<<NUM_5_OFFSET)|(NUM123468_RAM1_DIS[Displaydown[1]]<<NUM_6_OFFSET)|(NUM7_RAM1_DIS[Displaydown[2]]<<NUM_7_OFFSET)|(NUM123468_RAM1_DIS[Displaydown[3]]<<NUM_8_OFFSET);
    //ram2
    ram_updata[2] =(NUM123468_RAM2_DIS[Displayup[0]]<<NUM_1_OFFSET)|(NUM123468_RAM2_DIS[Displayup[1]]<<NUM_2_OFFSET)|(NUM123468_RAM2_DIS[Displayup[2]]<<NUM_3_OFFSET)|(NUM123468_RAM2_DIS[Displayup[3]]<<NUM_4_OFFSET);
    ram_updata[2] |=(NUM5_RAM2_DIS[Displaydown[0]]<<NUM_5_OFFSET)|(NUM123468_RAM2_DIS[Displaydown[1]]<<NUM_6_OFFSET)|(NUM7_RAM2_DIS[Displaydown[2]]<<NUM_7_OFFSET)|(NUM123468_RAM2_DIS[Displaydown[3]]<<NUM_8_OFFSET);
    //ram3
    ram_updata[3] =(NUM123468_RAM3_DIS[Displayup[0]]<<NUM_1_OFFSET)|(NUM123468_RAM3_DIS[Displayup[1]]<<NUM_2_OFFSET)|(NUM123468_RAM3_DIS[Displayup[2]]<<NUM_3_OFFSET)|(NUM123468_RAM3_DIS[Displayup[3]]<<NUM_4_OFFSET);
    ram_updata[3] |=(NUM5_RAM3_DIS[Displaydown[0]]<<NUM_5_OFFSET)|(NUM123468_RAM3_DIS[Displaydown[1]]<<NUM_6_OFFSET)|(NUM7_RAM3_DIS[Displaydown[2]]<<NUM_7_OFFSET)|(NUM123468_RAM3_DIS[Displaydown[3]]<<NUM_8_OFFSET);    
    //num_123567p    
    ram_updata[3] |=(NUM1236P_RAM3[num_123567p[0]]<<NUM_1_OFFSET)|(NUM1236P_RAM3[num_123567p[1]]<<NUM_2_OFFSET)|(NUM1236P_RAM3[num_123567p[2]]<<NUM_3_OFFSET)|(NUM1236P_RAM3[num_123567p[4]]<<NUM_6_OFFSET);
    ram_updata[3] |=(NUM5P_RAM3[num_123567p[3]]<<NUM_5_OFFSET)|(NUM7P_RAM3[num_123567p[5]]<<NUM_7_OFFSET);
    //num_col   
    ram_updata[3] |=(COL1_RAM3[num_col[0]]<<COL1_OFFSET)|(COL2_RAM3[num_col[1]]<<COL2_OFFSET);
    //num_s
    ram_updata[0] |=(RAM_DATA_S[num_s&0X01]<<RAM0_OFFSET_S1_9_10_14[0])|(RAM_DATA_S[(num_s>>8)&0X01]<<RAM0_OFFSET_S1_9_10_14[1])|(RAM_DATA_S[(num_s>>9)&0X01]<<RAM0_OFFSET_S1_9_10_14[2])|(RAM_DATA_S[(num_s>>13)&0X01]<<RAM0_OFFSET_S1_9_10_14[3]);
    ram_updata[1] |=(RAM_DATA_S[(num_s>>1)&0X01]<<RAM1_OFFSET_S2_8_11_16[0])|(RAM_DATA_S[(num_s>>7)&0X01]<<RAM1_OFFSET_S2_8_11_16[1])|(RAM_DATA_S[(num_s>>10)&0X01]<<RAM1_OFFSET_S2_8_11_16[2])|(RAM_DATA_S[(num_s>>15)&0X01]<<RAM1_OFFSET_S2_8_11_16[3]);
    ram_updata[2] |=(RAM_DATA_S[(num_s>>2)&0X01]<<RAM2_OFFSET_S3_7_12_15[0])|(RAM_DATA_S[(num_s>>6)&0X01]<<RAM2_OFFSET_S3_7_12_15[1])|(RAM_DATA_S[(num_s>>11)&0X01]<<RAM2_OFFSET_S3_7_12_15[2])|(RAM_DATA_S[(num_s>>14)&0X01]<<RAM2_OFFSET_S3_7_12_15[3]);
    ram_updata[3] |=(RAM_DATA_S[(num_s>>3)&0X01]<<RAM3_OFFSET_S4_5_6_13[0])|(RAM_DATA_S[(num_s>>4)&0X01]<<RAM3_OFFSET_S4_5_6_13[1])|(RAM_DATA_S[(num_s>>5)&0X01]<<RAM3_OFFSET_S4_5_6_13[2])|(RAM_DATA_S[(num_s>>12)&0X01]<<RAM3_OFFSET_S4_5_6_13[3]);
    //RAM0_OFFSET_S1_9_10_14
    HAL_LCD_Write(&lcdhandle_YR1618A,0,ram_updata[0]);
    HAL_LCD_Write(&lcdhandle_YR1618A,1,ram_updata[1]);
    HAL_LCD_Write(&lcdhandle_YR1618A,2,ram_updata[2]);
    HAL_LCD_Write(&lcdhandle_YR1618A,3,ram_updata[3]);
}
/*********************************************************************************
* Function    : LCD_YR1618A_SelfDisplay
* Description : LCD_YR1618A_SelfDisplay
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_YR1618A_SelfDisplay()
{
    uint16_t i=0,ip=0,j=0, num=0;
    uint32_t Displayup[4],Displaydown[4],num_123567p[7],num_col[2],num_s=0;
    memset(num_123567p,0,sizeof(num_123567p));//初始化清零
    memset(Displayup,0,sizeof(Displayup));//初始化清零
    memset(Displaydown,0,sizeof(Displaydown));//初始化清零
    
    //LCD_DisplayNum_YR1618A_INIT();
    for(i=0;i<16;i++)
    {
		num = (i > 10) ? (i - 10) : i;
        Displayup[0]=Displayup[1]=Displayup[2]=Displayup[3]=num;
        Displaydown[0]=Displaydown[1]=Displaydown[2]=Displaydown[3]=num;

        num_123567p[ip]=0x01;
        num_col[0]=i&0x01;
        num_col[1]=(~i)&0x01;
		num_s |=S_DATA[j];
        LCD_YR1618A_VIEW(Displayup,Displaydown,num_123567p,num_col,num_s);
        System_Delay_MS(400);
        num_s= (i<12) ? 0 : num_s;
        num_123567p[ip]=0;
        if(ip>=5)ip=0;
        else ip++;
        if(j>=16)j=0;
        else j++;
    }
   
}
/*********************************************************************************
* Function    : LCD_YR1618A_THDisplay
* Description : LCD_YR1618A_THDisplay
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
**********************************************************************************/
void LCD_YR1618A_THDisplay(float *getTempHum)
{


}
/*********************************************************************************
* Function    : LCD_BACK_LED
* Description : LCD_BACK_LED
* Input       : 
* Outpu       : 
* Author      : ZK                         Date : 2022年
**********************************************************************************/
void LCD_BACK_LED(void)
{   
    GPIO_InitTypeDef    GPIO_LCD_BACK_LED;
    
    GPIO_LCD_BACK_LED.Pin       = GPIO_PIN_5;
    GPIO_LCD_BACK_LED.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_LCD_BACK_LED.Pull      = GPIO_NOPULL;
    GPIO_LCD_BACK_LED.Alternate = GPIO_FUNCTION_0;
    
    HAL_GPIO_Init(GPIOA, &GPIO_LCD_BACK_LED);
    
    GPIO_LCD_BACK_LED.Pin       = GPIO_PIN_15;
    GPIO_LCD_BACK_LED.Mode      = GPIO_MODE_INPUT;
    GPIO_LCD_BACK_LED.Pull      = GPIO_PULLUP;
    GPIO_LCD_BACK_LED.Alternate = GPIO_FUNCTION_0;
    
    HAL_GPIO_Init(GPIOC, &GPIO_LCD_BACK_LED);

    LCD_BACK_LED_ON;
    System_Delay_MS(500);
}

