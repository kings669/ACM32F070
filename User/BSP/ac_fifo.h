#ifndef _AC_FIFO_H_
#define _AC_FIFO_H_

#include "stdint.h"

typedef struct{
    uint16_t tt_len;  
    volatile uint16_t size;
    volatile uint16_t in;
    volatile uint16_t out;
    volatile uint8_t *buff;
} FIFO_TypeDef;

void FIFO_Create(FIFO_TypeDef *fifo_struct,uint8_t *buff,uint16_t len);

uint8_t FIFO_InitData(FIFO_TypeDef *fifo_struct,const char *pdata,unsigned int len);

void FIFO_Clear(FIFO_TypeDef *fifo_struct);

uint8_t FIFO_In(FIFO_TypeDef *,uint8_t);

uint16_t FIFO_InMulti(FIFO_TypeDef *pfifo, uint8_t *pdata, uint16_t len);

uint8_t FIFO_Out(FIFO_TypeDef *fifo_struct,uint8_t *pdata);

uint16_t FIFO_OutMulti(FIFO_TypeDef *pfifo, uint8_t *pdata, uint16_t len);

uint16_t FIFO_Query(FIFO_TypeDef *fifo_struct);

#endif
