/***********************************************************************
 * All rights reserved.
 * Filename    : lcd.h
 * Description : lcd driver header file
 * Author(s)   : CWT      
 * version     : V1.0
 * Modify date : 2021
 ***********************************************************************/

#ifndef __LCD_GDC04212_H__

#define __LCD_GDC04212_H__

#include "ACM32Fxx_HAL.h"

#define SEG_A   0x0100
#define SEG_B   0x0200
#define SEG_C   0x0400
#define SEG_D   0x0800
#define SEG_E   0x0004
#define SEG_F   0x0001
#define SEG_G   0x0002



#define NUM_0   SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F
#define NUM_1   SEG_B+SEG_C
#define NUM_2   SEG_A+SEG_B+SEG_D+SEG_E+SEG_G
#define NUM_3   SEG_A+SEG_B+SEG_C+SEG_D+SEG_G
#define NUM_4   SEG_B+SEG_C+SEG_F+SEG_G
#define NUM_5   SEG_A+SEG_C+SEG_D+SEG_F+SEG_G
#define NUM_6   SEG_A+SEG_C+SEG_D+SEG_F+SEG_G+SEG_E
#define NUM_7   SEG_A+SEG_B+SEG_C
#define NUM_8   SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G
#define NUM_9   SEG_A+SEG_B+SEG_C+SEG_D+SEG_F+SEG_G  


void LCD_DisplayNum_GDC04212(uint32_t Num);

void LCD_Init_GDC04212(void);

#endif

