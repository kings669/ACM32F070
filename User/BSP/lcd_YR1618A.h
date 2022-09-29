/***********************************************************************
 * All rights reserved.
 * Filename    : lcd_YR1618A.h
 * Description : lcd_YR1618A driver header file
 * Author(s)   : ZK      
 * version     : V1.0
 * Modify date : 2022-06-23
 ***********************************************************************/
#ifndef __LCD_YR1618A_H__

#define __LCD_YR1618A_H__

#include "ACM32Fxx_HAL.h"

/**
  @verbatim
================================================================================
                              YR1618A LCD 真值表
================================================================================
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

 A LCD character coding is based on the following matrix:
        5	6	7	8	9	10	11	12	13	14	NC	NC	NC	20	16	15	NC	NC	NC	19	NC	NC	17	18	23	21	22	24	NC	NC	NC	NC
YR	    SEG0	SEG1	SEG2	SEG3	SEG4	SEG5	SEG6	SEG7	SEG8	SEG9	NC	NC	NC	SEG15	SEG11	SEG10	NC	NC	NC	SEG14	NC	NC	SEG12	SEG13	SEG18	SEG16	SEG17	SEG19	NC	NC	NC	NC
MCU	    SEG0	SEG1	SEG2	SEG3	SEG4	SEG5	SEG6	SEG7	SEG8	SEG9	SEG10	SEG11	SEG12	SEG13	SEG14	SEG15	SEG16	SEG17	SEG18	SEG19	SEG20	SEG21	SEG22	SEG23	SEG24	SEG25	SEG26	SEG27	SEG28	SEG29	SEG30	SEG31
COM0	1A	1B	2A	2B	3A	3B	4A	4B	S9	S10	NC	NC	NC	7B	5B	5A	NC	NC	NC	7A	NC	NC	6A	6B	S1	8A	8B	S14	NC	NC	NC	NC
COM1	1F	1G	2F	2G	3F	3G	4F	4G	S8	S11	NC	NC	NC	7G	5G	5F	NC	NC	NC	7F	NC	NC	6F	6G	S2	8F	8G	S16	NC	NC	NC	NC
COM2	1E	1C	2E	2C	3E	3C	4E	4C	S7	S12	NC	NC	NC	7C	5C	5E	NC	NC	NC	7E	NC	NC	6E	6C	S3	8E	8C	S15	NC	NC	NC	NC
COM3	1D	1P	2D	2P	3P	3P	4D	L1	S6	S5	NC	NC	NC	7P	5P	5D	NC	NC	NC	7D	NC	NC	6D	6P	S4	8D	L2	S13	NC	NC	NC	NC
  
  
  如第一个位置需要显示‘0’，则需点亮以下位置
          SEG0    SEG1    SEG2    SEG3   SEG4   SEG5   SEG6    SEG7  
  COM0  { 1 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM1  { 0 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM2  { 1 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}
  COM3  { 0 ,     1 ,      0 ,    0 ,     0 ,    0 ,    0 ,     0 ,}


===>按照显示模式1，4个COM，需要配置4个LCDRAM
故，此LCD驱动利用显示模式1完成
//mode0格式;         RAM0:   xxxxxSEG3xxxxxxxxxxSEG2xxxxxxxxxxSEG1xxxxxxxxxxSEG0xxxxx  
//                   RAM1:   xxxxxSEG7xxxxxxxxxxSEG6xxxxxxxxxxSEG5xxxxxxxxxxSEG4xxxxx

//mode1格式;         RAM0:   SEG31xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxSEG0  
//                   RAM1:   SEG31xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxSEG0
//                   RAM2:   SEG31xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxSEG0  
//                   RAM3:   SEG31xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxSEG0
================================================================================
  @endverbatim
  */


extern uint16_t S_DATA[16];

//1,2,3,4,6,8
#define NUM123468_SEG_A    0x00000001
#define NUM123468_SEG_B    0x00000002
#define NUM123468_SEG_C    0x00000002
#define NUM123468_SEG_D    0x00000001
#define NUM123468_SEG_E    0x00000001
#define NUM123468_SEG_F    0x00000001
#define NUM123468_SEG_G    0x00000002
//5
#define NUM5_SEG_A    0x00000002
#define NUM5_SEG_B    0x00000001
#define NUM5_SEG_C    0x00000001
#define NUM5_SEG_D    0x00000002
#define NUM5_SEG_E    0x00000002
#define NUM5_SEG_F    0x00000002
#define NUM5_SEG_G    0x00000001
//7
#define NUM7_SEG_A    0x00000040
#define NUM7_SEG_B    0x00000001
#define NUM7_SEG_C    0x00000001
#define NUM7_SEG_D    0x00000040
#define NUM7_SEG_E    0x00000040
#define NUM7_SEG_F    0x00000040
#define NUM7_SEG_G    0x00000001

//num & xP

#define NUM_1_OFFSET    0
#define NUM_2_OFFSET    2
#define NUM_3_OFFSET    4
#define NUM_4_OFFSET    6

#define NUM_6_OFFSET    22

#define NUM_8_OFFSET    25

#define NUM_5_OFFSET    14
#define NUM_7_OFFSET    13


//RAM3-xP
#define RAM3_SEG_1236P      0x00000002
#define RAM3_SEG_7P         0x00000001
#define RAM3_SEG_5P         0x00000001
//RAM3-COLx
#define RAM3_SEG_COL1         0x00000001
#define RAM3_SEG_COL2         0x00000001
#define COL1_OFFSET    7
#define COL2_OFFSET    26

//S
#define RAM0_OFFSET_S1_ID              24
#define RAM1_OFFSET_S2_C1              24
#define RAM2_OFFSET_S3_C2              24
#define RAM3_OFFSET_S4_RH              24
#define RAM3_OFFSET_S5_ILINE           9
#define RAM3_OFFSET_S6_WIFI1           8
#define RAM2_OFFSET_S7_WIFI2           8
#define RAM1_OFFSET_S8_WIFI3           8
#define RAM0_OFFSET_S9_WIFI4           8
#define RAM0_OFFSET_S10_UPLIM          9
#define RAM1_OFFSET_S11_DOWNLIM        9
#define RAM2_OFFSET_S12_BATSTATE       9
#define RAM3_OFFSET_S13_BATW           27
#define RAM0_OFFSET_S14_BAT1           27
#define RAM2_OFFSET_S15_BAT2           27
#define RAM1_OFFSET_S16_BAT3           27

//SET S
#define S1_ID              0x0001
#define S2_C1              0x0002
#define S3_C2              0x0004
#define S4_RH              0x0008
#define S5_ILINE           0x0010
#define S6_WIFI1           0x0020
#define S7_WIFI2           0x0040
#define S8_WIFI3           0x0080
#define S9_WIFI4           0x0100
#define S10_UPLIM          0x0200
#define S11_DOWNLIM        0x0400
#define S12_BATSTATE       0x0800
#define S13_BATW           0x1000
#define S14_BAT1           0x2000
#define S15_BAT2           0x4000
#define S16_BAT3           0x8000


//RAM0 AB
//RAM1 FG
//RAM2 EC
//RAM3 DP

#define RAM0   0
#define RAM1   1
#define RAM2   2
#define RAM3   3
//1,2,3,4,6,8
#define NUM123468_0_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_0_RAM1   (NUM123468_SEG_F)
#define NUM123468_0_RAM2   (NUM123468_SEG_C+NUM123468_SEG_E)
#define NUM123468_0_RAM3   (NUM123468_SEG_D)

#define NUM123468_1_RAM0   (NUM123468_SEG_B)
#define NUM123468_1_RAM1   (0)
#define NUM123468_1_RAM2   (NUM123468_SEG_C)
#define NUM123468_1_RAM3   (0)

#define NUM123468_2_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_2_RAM1   (NUM123468_SEG_G)
#define NUM123468_2_RAM2   (NUM123468_SEG_E)
#define NUM123468_2_RAM3   (NUM123468_SEG_D)

#define NUM123468_3_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_3_RAM1   (NUM123468_SEG_G)
#define NUM123468_3_RAM2   (NUM123468_SEG_C)
#define NUM123468_3_RAM3   (NUM123468_SEG_D)

#define NUM123468_4_RAM0   (NUM123468_SEG_B)
#define NUM123468_4_RAM1   (NUM123468_SEG_F+NUM123468_SEG_G)
#define NUM123468_4_RAM2   (NUM123468_SEG_C)
#define NUM123468_4_RAM3   (0)

#define NUM123468_5_RAM0   (NUM123468_SEG_A)
#define NUM123468_5_RAM1   (NUM123468_SEG_F+NUM123468_SEG_G)
#define NUM123468_5_RAM2   (NUM123468_SEG_C)
#define NUM123468_5_RAM3   (NUM123468_SEG_D)

#define NUM123468_6_RAM0   (NUM123468_SEG_A)
#define NUM123468_6_RAM1   (NUM123468_SEG_F+NUM123468_SEG_G)
#define NUM123468_6_RAM2   (NUM123468_SEG_C+NUM123468_SEG_E)
#define NUM123468_6_RAM3   (NUM123468_SEG_D)

#define NUM123468_7_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_7_RAM1   (0)
#define NUM123468_7_RAM2   (NUM123468_SEG_C)
#define NUM123468_7_RAM3   (0)

#define NUM123468_8_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_8_RAM1   (NUM123468_SEG_F+NUM123468_SEG_G)
#define NUM123468_8_RAM2   (NUM123468_SEG_C+NUM123468_SEG_E)
#define NUM123468_8_RAM3   (NUM123468_SEG_D)

#define NUM123468_9_RAM0   (NUM123468_SEG_A+NUM123468_SEG_B)
#define NUM123468_9_RAM1   (NUM123468_SEG_F+NUM123468_SEG_G)
#define NUM123468_9_RAM2   (NUM123468_SEG_C)
#define NUM123468_9_RAM3   (NUM123468_SEG_D)
//5
#define NUM5_0_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_0_RAM1   (NUM5_SEG_F)
#define NUM5_0_RAM2   (NUM5_SEG_C+NUM5_SEG_E)
#define NUM5_0_RAM3   (NUM5_SEG_D)

#define NUM5_1_RAM0   (NUM5_SEG_B)
#define NUM5_1_RAM1   (0)
#define NUM5_1_RAM2   (NUM5_SEG_C)
#define NUM5_1_RAM3   (0)

#define NUM5_2_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_2_RAM1   (NUM5_SEG_G)
#define NUM5_2_RAM2   (NUM5_SEG_E)
#define NUM5_2_RAM3   (NUM5_SEG_D)

#define NUM5_3_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_3_RAM1   (NUM5_SEG_G)
#define NUM5_3_RAM2   (NUM5_SEG_C)
#define NUM5_3_RAM3   (NUM5_SEG_D)

#define NUM5_4_RAM0   (NUM5_SEG_B)
#define NUM5_4_RAM1   (NUM5_SEG_F+NUM5_SEG_G)
#define NUM5_4_RAM2   (NUM5_SEG_C)
#define NUM5_4_RAM3   (0)

#define NUM5_5_RAM0   (NUM5_SEG_A)
#define NUM5_5_RAM1   (NUM5_SEG_F+NUM5_SEG_G)
#define NUM5_5_RAM2   (NUM5_SEG_C)
#define NUM5_5_RAM3   (NUM5_SEG_D)

#define NUM5_6_RAM0   (NUM5_SEG_A)
#define NUM5_6_RAM1   (NUM5_SEG_F+NUM5_SEG_G)
#define NUM5_6_RAM2   (NUM5_SEG_C+NUM5_SEG_E)
#define NUM5_6_RAM3   (NUM5_SEG_D)

#define NUM5_7_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_7_RAM1   (0)
#define NUM5_7_RAM2   (NUM5_SEG_C)
#define NUM5_7_RAM3   (0)

#define NUM5_8_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_8_RAM1   (NUM5_SEG_F+NUM5_SEG_G)
#define NUM5_8_RAM2   (NUM5_SEG_C+NUM5_SEG_E)
#define NUM5_8_RAM3   (NUM5_SEG_D)

#define NUM5_9_RAM0   (NUM5_SEG_A+NUM5_SEG_B)
#define NUM5_9_RAM1   (NUM5_SEG_F+NUM5_SEG_G)
#define NUM5_9_RAM2   (NUM5_SEG_C)
#define NUM5_9_RAM3   (NUM5_SEG_D)
//7
#define NUM7_0_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_0_RAM1   (NUM7_SEG_F)
#define NUM7_0_RAM2   (NUM7_SEG_C+NUM7_SEG_E)
#define NUM7_0_RAM3   (NUM7_SEG_D)

#define NUM7_1_RAM0   (NUM7_SEG_B)
#define NUM7_1_RAM1   (0)
#define NUM7_1_RAM2   (NUM7_SEG_C)
#define NUM7_1_RAM3   (0)

#define NUM7_2_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_2_RAM1   (NUM7_SEG_G)
#define NUM7_2_RAM2   (NUM7_SEG_E)
#define NUM7_2_RAM3   (NUM7_SEG_D)

#define NUM7_3_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_3_RAM1   (NUM7_SEG_G)
#define NUM7_3_RAM2   (NUM7_SEG_C)
#define NUM7_3_RAM3   (NUM7_SEG_D)

#define NUM7_4_RAM0   (NUM7_SEG_B)
#define NUM7_4_RAM1   (NUM7_SEG_F+NUM7_SEG_G)
#define NUM7_4_RAM2   (NUM7_SEG_C)
#define NUM7_4_RAM3   (0)

#define NUM7_5_RAM0   (NUM7_SEG_A)
#define NUM7_5_RAM1   (NUM7_SEG_F+NUM7_SEG_G)
#define NUM7_5_RAM2   (NUM7_SEG_C)
#define NUM7_5_RAM3   (NUM7_SEG_D)

#define NUM7_6_RAM0   (NUM7_SEG_A)
#define NUM7_6_RAM1   (NUM7_SEG_F+NUM7_SEG_G)
#define NUM7_6_RAM2   (NUM7_SEG_C+NUM7_SEG_E)
#define NUM7_6_RAM3   (NUM7_SEG_D)

#define NUM7_7_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_7_RAM1   (0)
#define NUM7_7_RAM2   (NUM7_SEG_C)
#define NUM7_7_RAM3   (0)

#define NUM7_8_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_8_RAM1   (NUM7_SEG_F+NUM7_SEG_G)
#define NUM7_8_RAM2   (NUM7_SEG_C+NUM7_SEG_E)
#define NUM7_8_RAM3   (NUM7_SEG_D)

#define NUM7_9_RAM0   (NUM7_SEG_A+NUM7_SEG_B)
#define NUM7_9_RAM1   (NUM7_SEG_F+NUM7_SEG_G)
#define NUM7_9_RAM2   (NUM7_SEG_C)
#define NUM7_9_RAM3   (NUM7_SEG_D)


#define LCD_BACK_LED_ON HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
#define LCD_BACK_LED_OFF HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_CLEAR);

#define GetLCDBackKey() HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)
#define LCD_BACK_LED_EN GPIO_PIN_CLEAR

void LCD_BACK_LED(void);

void LCD_DisplayNum_YR1618A(uint32_t Numup);
void LCD_Init_YR1618A(void);

void Get_RAM_NUM_DATA(uint32_t *ram_updata,uint16_t num_up,uint16_t num_down);
uint32_t Get_RAM_xP_DATA(uint8_t ram_num,uint16_t num_xp);
void LCD_DisplayNum_YR1618A_INIT(void);
void LCD_YR1618A_VIEW(uint32_t *Displayup,uint32_t *Displaydown,uint32_t *num_p,uint32_t *num_col,uint32_t num_s);
void LCD_YR1618A_THDisplay(float *getTempHum);
void LCD_YR1618A_SelfDisplay(void);
#endif
