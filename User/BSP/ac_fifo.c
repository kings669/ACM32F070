/*****************************************************************
Copyright(C) 2008 - 2021, Shanghai AisinoChip Co.,Ltd.
@�ļ�����:	ac_fifo.c
@��������:	FIFOģ�麯����
@������Ա:	bobzhang 
@�������:	2021.1.18
@��ǰ�汾:	1.0
@�޸ļ�¼:	
�޸�����		�޸���   		�޸�˵��

******************************************************************/

#include "ac_fifo.h"
#include "string.h"

/*****************************************************************
@����	FIFO���������64KB����ģ�����к����������룬���Ǽӽ�ֹ�ж�
@����	pfifo-FIFO�ṹָ��
@����	buff-FIFO�����ݻ���
@����	len-FIFO�ĳ���
@����	��
******************************************************************/
void FIFO_Create(FIFO_TypeDef *pfifo, uint8_t *buff, uint16_t len)
{
    pfifo->tt_len = len;
    pfifo->size = 0;
    pfifo->in = pfifo->out = 0;
    pfifo->buff = buff;
}


/*****************************************************************
@����	��һ�����ݳ�ʼ��FIFO������Ҫ�ȴ���FIFO�����ܳ�ʼ����
@����	pfifo-FIFO�ṹָ��
@����	pdata[in]-���ݵ�ַ
@����	len-���ݳ���
@����	0-success,1-fail
******************************************************************/
uint8_t FIFO_InitData(FIFO_TypeDef *pfifo, const char *pdata, unsigned int len)
{
    if(pfifo == NULL)
    {
        return 1;
    }    
    if(pdata == NULL)
    {
        FIFO_Clear(pfifo);
        return 1;
    }
    
    if(len>pfifo->tt_len)
    {
        return 1;
    } 
    
    pfifo->in = len;
    pfifo->out = 0;
    memcpy((void *)pfifo->buff, pdata, len);
    pfifo->size = len;
    return 0;
}

/*****************************************************************
@����	���FIFO 
@����	pfifo-FIFO�ṹָ��
@����	��
******************************************************************/
void FIFO_Clear(FIFO_TypeDef *pfifo)
{   
    pfifo->size = 0;
    pfifo->in = pfifo->out = 0;
}

/*****************************************************************
@����	FIFO��ջ��
@����	pfifo-FIFO�ṹָ��
@����	data-�ֽ�����
@����	0-success,1-fail
******************************************************************/
uint8_t FIFO_In(FIFO_TypeDef *pfifo, uint8_t data)
{   
    if(pfifo->size >= pfifo->tt_len)
    {
        return 1;
    }
    
    *(pfifo->buff + pfifo->in) = data; 
	pfifo->in++;
    
    if(pfifo->in >= pfifo->tt_len)
    {
        pfifo->in = 0;
    }
    pfifo->size++;
    return 0;
}


/*****************************************************************
@����	FIFO���ֽ���ջ�������������룬���Ǽӽ�ֹ�ж�
@����	pfifo-FIFO�ṹָ��
@����	pdata-���ݵ�ַ
@����	len-���ݳ���
@����	ʵ����ջ�����ݳ���
******************************************************************/
uint16_t FIFO_InMulti(FIFO_TypeDef *pfifo, uint8_t *pdata, uint16_t len)
{
    uint16_t i=0;
    while(len--)
    {
        if(pfifo->size >= pfifo->tt_len)
        {
            //printf("<%d,%d>",pfifo->size,pfifo->tt_len-1);
            return i;
        }
        
        *(pfifo->buff + pfifo->in) = *pdata++; 
        pfifo->in++;
        if(pfifo->in >= pfifo->tt_len)
        {
            pfifo->in = 0;
        }
        pfifo->size++;
        i++;
    }
    return i;
    
}


/*****************************************************************
@����	FIFO��ջ�������������룬���Ǽӽ�ֹ�ж�
@����	pfifo-FIFO�ṹָ��
@����	pdata-�ֽ����ݵ�ַ
@����	0-success,1-fail
******************************************************************/
uint8_t FIFO_Out(FIFO_TypeDef *pfifo, uint8_t *pdata)
{
    if(!(pfifo->size))
        return 1;
    
    *pdata = *(pfifo->buff + pfifo->out);
	pfifo->out++;    
    if(pfifo->out >= pfifo->tt_len)
    {
        pfifo->out = 0;
    }
    
    pfifo->size--;
    return 0;
}

/*****************************************************************
@����	FIFO���ֽڳ�ջ�������������룬���Ǽӽ�ֹ�ж�
@����	pfifo-FIFO�ṹָ��
@����	pdata-���ݵ�ַ
@����	len-���ݳ���
@����	ʵ�ʳ�ջ�����ݳ���
******************************************************************/
uint16_t FIFO_OutMulti(FIFO_TypeDef *pfifo, uint8_t *pdata, uint16_t len)
{
    uint16_t i=0;
    while(len--)
    {
        if(!(pfifo->size))
            return i;
        
        *pdata++ = *(pfifo->buff + pfifo->out);  
        pfifo->out++;  
        if(pfifo->out >= pfifo->tt_len)
        {
            pfifo->out = 0;
        }
        pfifo->size--;
        i++;
    }
    return i;   
}

/*****************************************************************
@����	��ѯFIFO���ݳ���
@����	pfifo-FIFO�ṹָ��
@����	FIFO����
******************************************************************/
uint16_t FIFO_Query(FIFO_TypeDef *pfifo)
{
    return pfifo->size;
}