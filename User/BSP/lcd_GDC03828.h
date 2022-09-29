/***********************************************************************
 * All rights reserved.
 * Filename    : lcd.h
 * Description : lcd driver header file
 * Author(s)   : CWT      
 * version     : V1.0
 * Modify date : 2021
 ***********************************************************************/

#ifndef __LCD_GDC03828_H__

#define __LCD_GDC03828_H__

#include "ACM32Fxx_HAL.h"


#define  A       0x01
#define  B       0x02
#define  C       0x04
#define  D       0x08
#define  E       0x10
#define  F       0x20
#define  G       0x40
#define  P_COL   0x80


#define Number0    A+ B+ C+ D+ E+ F
#define Number1    B+ C
#define Number2    A+ B+ D+ E+ G
#define Number3    A+ B+ C+ D+ G
#define Number4    B+ C+ F+ G
#define Number5    A+ C+ D+ F+ G
#define Number6    A+ C+ D+ F+ G+ E
#define Number7    A+ B+ C
#define Number8    A+ B+ C+ D+ E+ F+ G
#define Number9    A+ B+ C+ D+ F+ G  


void LCD_DisplayNum_GDC003828(uint32_t Num);

void LCD_Init_GDC03828(void);

#endif
