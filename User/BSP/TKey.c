#include "TKey.h"
#include "ac_fifo.h"
#include "stdlib.h"


/*��Ϣ���*/
#define TKEY_DEBUG_ON         0

#define TKEY_DEBUG(fmt,arg...)          do{\
                                            if(TKEY_DEBUG_ON)\
                                                printf("\r\n<<-TKey.c->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


#ifdef TKEY_WAVEFORM_OUTPUT
    extern UART_HandleTypeDef UART2_Handle;
#endif

extern volatile uint32_t gu32_SystemCount;
static uint8_t sgu8_TKEYScanTime;
static uint16_t sgu16_RawDataRangRatio;
#ifdef TKEY_FIFO_ENABLE
static uint8_t TKEY_FifoBuffer[TOTAL_CHANNELS];
static FIFO_TypeDef TKEY_Fifo;  
#endif  
static TKEY_HandleTypeDef TKEY_Handle;
static TKEY_DataDef TKey_Channel_Data[TOTAL_CHANNELS]={0};
static TKEY_CalibartData TKey_Calibart_Data[TOTAL_CHANNELS]={0};

/*****************************************************************
*   ����ÿ��ͨ����������
*   {DetectInTH[���·�ֵ], WakeUpTh[���ѷ�ֵ], }
******************************************************************/
TKEY_BaseParaDef TKey_Channel_BasePara[TOTAL_CHANNELS] = {   
#ifdef  TKEY_CHANNEL_0_ENABLE   //TKEY_CHANNEL_0 UART_RX  
    {TKEY_0_SENSITIVITY, TKEY_0_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_1_ENABLE   //TKEY_CHANNEL_1   
    {TKEY_1_SENSITIVITY, TKEY_1_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_2_ENABLE   //TKEY_CHANNEL_2   
    {TKEY_2_SENSITIVITY, TKEY_2_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_3_ENABLE   //TKEY_CHANNEL_3 SWDIO   
    {TKEY_3_SENSITIVITY, TKEY_3_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_4_ENABLE   //TKEY_CHANNEL_4   
    {TKEY_4_SENSITIVITY, TKEY_4_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_5_ENABLE   //TKEY_CHANNEL_5   
    {TKEY_5_SENSITIVITY, TKEY_5_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_6_ENABLE   //TKEY_CHANNEL_6 SWDCLK   
    {TKEY_6_SENSITIVITY, TKEY_6_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_7_ENABLE   //TKEY_CHANNEL_7   
    {TKEY_7_SENSITIVITY, TKEY_7_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_8_ENABLE   //TKEY_CHANNEL_8   
    {TKEY_8_SENSITIVITY, TKEY_8_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_9_ENABLE   //TKEY_CHANNEL_9   
    {TKEY_9_SENSITIVITY, TKEY_9_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_10_ENABLE  //TKEY_CHANNEL_10   
    {TKEY_10_SENSITIVITY, TKEY_10_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_11_ENABLE  //TKEY_CHANNEL_11   
    {TKEY_11_SENSITIVITY, TKEY_11_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_12_ENABLE  //TKEY_CHANNEL_12   
    {TKEY_12_SENSITIVITY, TKEY_12_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_13_ENABLE  //TKEY_CHANNEL_13   
    {TKEY_13_SENSITIVITY, TKEY_13_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_14_ENABLE  //TKEY_CHANNEL_14   
    {TKEY_14_SENSITIVITY, TKEY_14_SLEEP_SENSITIVITY}, 
#endif
#ifdef  TKEY_CHANNEL_15_ENABLE  //TKEY_CHANNEL_15   
    {TKEY_15_SENSITIVITY, TKEY_15_SLEEP_SENSITIVITY},
#endif
};


/*****************************************************************
*   TKeyͨ������
*   ChannelIdΪTKEY_CHANNEL_1-TKEY_CHANNEL_15
******************************************************************/
TKEY_ChannelDataDef TKey_Config[] = {	
#ifdef  TKEY_CHANNEL_0_ENABLE  
    {&TKey_Channel_BasePara[TK_0], &TKey_Channel_Data[TK_0], &TKey_Calibart_Data[TK_0], TKEY_CHANNEL_0 },
#endif
#ifdef  TKEY_CHANNEL_1_ENABLE     
    {&TKey_Channel_BasePara[TK_1], &TKey_Channel_Data[TK_1], &TKey_Calibart_Data[TK_1], TKEY_CHANNEL_1 },
#endif
#ifdef  TKEY_CHANNEL_2_ENABLE      
    {&TKey_Channel_BasePara[TK_2], &TKey_Channel_Data[TK_2], &TKey_Calibart_Data[TK_2], TKEY_CHANNEL_2 },
#endif
#ifdef  TKEY_CHANNEL_3_ENABLE     
    {&TKey_Channel_BasePara[TK_3], &TKey_Channel_Data[TK_3], &TKey_Calibart_Data[TK_3], TKEY_CHANNEL_3 },
#endif
#ifdef  TKEY_CHANNEL_4_ENABLE     
    {&TKey_Channel_BasePara[TK_4], &TKey_Channel_Data[TK_4], &TKey_Calibart_Data[TK_4], TKEY_CHANNEL_4 },
#endif
#ifdef  TKEY_CHANNEL_5_ENABLE      
    {&TKey_Channel_BasePara[TK_5], &TKey_Channel_Data[TK_5], &TKey_Calibart_Data[TK_5], TKEY_CHANNEL_5 },
#endif
#ifdef  TKEY_CHANNEL_6_ENABLE     
    {&TKey_Channel_BasePara[TK_6], &TKey_Channel_Data[TK_6], &TKey_Calibart_Data[TK_6], TKEY_CHANNEL_6 },
#endif
#ifdef  TKEY_CHANNEL_7_ENABLE      
    {&TKey_Channel_BasePara[TK_7], &TKey_Channel_Data[TK_7], &TKey_Calibart_Data[TK_7], TKEY_CHANNEL_7 },
#endif
#ifdef  TKEY_CHANNEL_8_ENABLE      
    {&TKey_Channel_BasePara[TK_8], &TKey_Channel_Data[TK_8], &TKey_Calibart_Data[TK_8], TKEY_CHANNEL_8 },
#endif
#ifdef  TKEY_CHANNEL_9_ENABLE      
    {&TKey_Channel_BasePara[TK_9], &TKey_Channel_Data[TK_9], &TKey_Calibart_Data[TK_9], TKEY_CHANNEL_9 },
#endif
#ifdef  TKEY_CHANNEL_10_ENABLE      
    {&TKey_Channel_BasePara[TK_10], &TKey_Channel_Data[TK_10], &TKey_Calibart_Data[TK_10], TKEY_CHANNEL_10},
#endif
#ifdef  TKEY_CHANNEL_11_ENABLE      
    {&TKey_Channel_BasePara[TK_11], &TKey_Channel_Data[TK_11], &TKey_Calibart_Data[TK_11], TKEY_CHANNEL_11},
#endif
#ifdef  TKEY_CHANNEL_12_ENABLE      
    {&TKey_Channel_BasePara[TK_12], &TKey_Channel_Data[TK_12], &TKey_Calibart_Data[TK_12], TKEY_CHANNEL_12},
#endif
#ifdef  TKEY_CHANNEL_13_ENABLE      
    {&TKey_Channel_BasePara[TK_13], &TKey_Channel_Data[TK_13], &TKey_Calibart_Data[TK_13], TKEY_CHANNEL_13},
#endif
#ifdef  TKEY_CHANNEL_14_ENABLE      
    {&TKey_Channel_BasePara[TK_14], &TKey_Channel_Data[TK_14], &TKey_Calibart_Data[TK_14], TKEY_CHANNEL_14},
#endif
#ifdef  TKEY_CHANNEL_15_ENABLE      
    {&TKey_Channel_BasePara[TK_15], &TKey_Channel_Data[TK_15], &TKey_Calibart_Data[TK_15], TKEY_CHANNEL_15},
#endif
   
    {0, 0, 0, TKEY_CHANNEL_NULL},
 
};
    

/*****************************************************************
@����	TKEY��ʱ�����á�
@����	�� 
@����	��
******************************************************************/
static void TKEY_SCAN_TIMX_Cfg(void)  
{
    uint32_t timer_clock;
    TIM_HandleTypeDef TIMx_Handler;  
    
    timer_clock = System_Get_APBClock(); 
    
    if (System_Get_SystemClock() != System_Get_APBClock())  // if hclk/pclk != 1, then timer clk = pclk * 2  
    {
       timer_clock =  System_Get_APBClock() << 1;    
    }
    
	TIMx_Handler.Instance = TKEY_SCAN_TIMX;
	TIMx_Handler.Init.ARRPreLoadEn = TIM_ARR_PRELOAD_ENABLE;    
	TIMx_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
	TIMx_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; 
	TIMx_Handler.Init.RepetitionCounter = 0;  
	TIMx_Handler.Init.Prescaler = (timer_clock/1000) - 1;  // count++ every 1ms 
	TIMx_Handler.Init.Period = TKEY_SCAN_TIM_PERIOD - 1;  //1ms * TKEY_SCAN_TIME   
	
    HAL_TIMER_MSP_Init(&TIMx_Handler);  
	HAL_TIMER_Base_Init(&TIMx_Handler);  
	HAL_TIM_ENABLE_IT(&TIMx_Handler, TIMER_INT_EN_UPD);
    NVIC_SetPriority(TKEY_SCAN_TIMX_IRQn, TKEY_SCAN_TIMX_IRQn_PRIORITY);      
}

/*****************************************************************
@����	TKEY��ʱ���жϴ�������
@����	�� 
@����	��
******************************************************************/
void TKEY_SCAN_TIMX_IRQHandler(void)
{
	if (TKEY_SCAN_TIMX->SR & TIMER_SR_UIF)
	{
		if(TKEY->ISR & TKEY_ISR_EOC)//����ͨ��ɨ�������Լ��Ҫ31ms
        {
            TKEY->ISR = TKEY_ISR_EOC;
            HAL_TKEY_ScanProcess(&TKEY_Handle);  //��ʱ1ms
            
            if(TKEY_Handle.ChannelDetectedNum)
            {
            #ifdef TKEY_FIFO_ENABLE
                if(TKEY_Handle.ChannelDetectedNum  == 1)
                {
                    FIFO_In(&TKEY_Fifo, TKEY_Handle.ChannelValue);
                }
            #endif     
                TKEY_Handle.ChannelDetectedNum = 0;
                TKEY_Handle.ChannelValue = 0;     
            }
            
        }
        else if(!READ_BIT(TKEY->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart. 
        {
            SET_BIT(TKEY->CR, TKEY_CR_START);
        }     
        
        else if(READ_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
        }
	}
	
	TKEY_SCAN_TIMX->SR = 0;   //write 0 to clear hardware flag  
}

/*****************************************************************
@����	TKEY��ʱɨ���ʼ����
@����	��
@����	��
******************************************************************/
void TKEY_Timer_ScanInit(void)
{
#ifdef TKEY_FIFO_ENABLE
    memset(TKEY_FifoBuffer, 0, sizeof(TKEY_FifoBuffer));
    FIFO_Create(&TKEY_Fifo, TKEY_FifoBuffer, sizeof(TKEY_FifoBuffer));
    FIFO_Clear(&TKEY_Fifo);
#endif
    TKEY_SCAN_TIMX_Cfg();                 
}

/*****************************************************************
@����	���TKEY��ʱɨ��FIFO��
@����	��
@����	��
******************************************************************/
void TKEY_Scan_FIFO_Clear(void)
{
#ifdef TKEY_FIFO_ENABLE
    memset(TKEY_FifoBuffer, 0, sizeof(TKEY_FifoBuffer));
    FIFO_Clear(&TKEY_Fifo);  
#endif    
}

/*****************************************************************
@����	����TKEY��ʱɨ�衣
@����	��
@����	��
******************************************************************/
void TKEY_Timer_Scan_Start(void)
{     
    HAL_TIMER_Base_Start(TKEY_SCAN_TIMX);        
    //HAL_TIM_ENABLE_IT_EX(TKEY_SCAN_TIMX,TIMER_INT_EN_UPD);
}

/*****************************************************************
@����	�ر�TKEY��ʱɨ�衣
@����	��
@����	��
******************************************************************/
void TKEY_Timer_Scan_Stop(void)
{
    HAL_TIMER_Base_Stop(TKEY_SCAN_TIMX);        	 
}

/*****************************************************************
@����	��ȡTKEY��ʱɨ���ֵ��
@����	pucKey[OUT] ��ֵ
@����	��
******************************************************************/
void TKEY_Timer_Scan_Result(uint8_t *pucKey)
{
    *pucKey = 0xFF;
#ifdef TKEY_FIFO_ENABLE
    if(FIFO_Query(&TKEY_Fifo))
    {
        FIFO_Out(&TKEY_Fifo, pucKey);
    }
#endif
}

/*****************************************************************
@����	TKey��ʼ����
@����	��
@����	��
******************************************************************/
void TKEY_Init(void)
{    
    sgu8_TKEYScanTime = TKEY_SCAN_WAIT_TIMES;
    sgu16_RawDataRangRatio = TKEY_RAWDATA_RANGE_RATIO;
    TKEY_Handle.Init.ShieldEn = TKEY_CR_SHIELDEN_DISABLE;
    TKEY_Handle.Init.ScanWaitTime = sgu8_TKEYScanTime;
    TKEY_Handle.TotalChannelNum = TOTAL_CHANNELS;
    TKEY_Handle.ChannelData = TKey_Config;
    HAL_TKEY_Init(&TKEY_Handle); 
}

/*****************************************************************
@����	TKeyУ�������ʼ����
@����	��
@����	��
******************************************************************/
void TKEY_Calibrate_ParaInit(void)
{
    uint8_t ucI;
    for(ucI = 0; TKEY_Handle.ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        TKEY_Handle.ChannelData[ucI].Tkey_CalData->pos = 0;
        TKEY_Handle.ChannelData[ucI].Tkey_CalData->ScanTimer = 0;
        TKEY_Handle.ChannelData[ucI].Tkey_CalData->DetectingTimer = 0;
        TKEY_Handle.ChannelData[ucI].Tkey_CalData->CalFlag = TKEY_CALIBRAT_IDLE;
    }
  
}
/*****************************************************************
@����	TKey��������У׼��
@����	��
@����	0-�ɹ�����0-ʧ�ܣ�1-ɨ��ȴ�ʱ���쳣��2-RawData������Χ�쳣
******************************************************************/
uint8_t TKEY_Quick_Calibrate(void)
{
    uint8_t ucI,ucJ = 0;
    static uint16_t RawData_Ref[TOTAL_CHANNELS] = {0};
    uint32_t RawData_Sum[TOTAL_CHANNELS] = {0};
    uint8_t count[TOTAL_CHANNELS] = {0};
    __IO uint32_t *gu32RegTemp;
    uint8_t Temp_Delta = 0;
    uint8_t Temp_timeout_cnt = 0;
    uint8_t Temp_outrange_cnt = 0;

QUICK_CALIBRATE:
    for(ucJ = 0; ucJ < TKEY_QUICK_QUICK_CALIBRATE_TIMES; ucJ++)
    {
        TKEY->ISR = 0x07;
        if(!(TKEY->CR & TKEY_CR_CONT))
        {
            /*Start the Tkey scan*/    
            SET_BIT(TKEY->CR, TKEY_CR_START); 
        }
        while(!READ_BIT(TKEY->ISR, TKEY_ISR_EOC))
        {
            if(!READ_BIT(TKEY->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart. 
                SET_BIT(TKEY->CR, TKEY_CR_START); 
            
            if(READ_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT))
            {
                SET_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
                Temp_timeout_cnt++;
                if(Temp_timeout_cnt == TKEY_QUICK_QUICK_CALIBRATE_TIMES)
                {
                    Temp_timeout_cnt = 0;                
                    //�Զ�����ɨ��ȴ�ʱ��:sgu8_TKEYScanTime��ÿ�����ӵ�ǰֵ��(1/TKEY_SCAN_WAIT_TIMES_RATIO)
                    sgu8_TKEYScanTime ++;//= (sgu8_TKEYScanTime / TKEY_SCAN_WAIT_TIMES_RATIO);
                    if(sgu8_TKEYScanTime > TKEY_SCAN_WAIT_MAX_TIMES)
                    {
                        TKEY_DEBUG("sgu8_TKEYScanTime more than TKEY_SCAN_WAIT_MAX_TIMES\n");
                        return 1;
                    } 
                    /*Config the Tkey TKEY_SMPR register*/
                    MODIFY_REG(TKEY->SMPR, TKEY_SMPR_SWT_MASK, TKEY_SMPR_SWT(sgu8_TKEYScanTime));  
                }
                goto QUICK_CALIBRATE;
            }
        }
        TKEY->ISR = TKEY_ISR_EOC;
        gu32RegTemp = &TKEY->CH0;

        for(ucI = 0; TKEY_Handle.ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
        {
            /* Read the data and calculate the delta.*/
            TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData = *(gu32RegTemp + TKEY_Handle.ChannelData[ucI].ChannelId);
            Temp_Delta = TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData / sgu16_RawDataRangRatio;        
            if((RawData_Ref[ucI])&&((RawData_Ref[ucI] > (INT32)(TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData + Temp_Delta)) \
            || (RawData_Ref[ucI] < ((INT32)(TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData - Temp_Delta)))))
            {
                for(uint8_t i=0;TKEY_Handle.ChannelData[i].ChannelId != 0xFFFF;i++)
                {
                    count[i] = 0;
                    RawData_Ref[i] = 0;
                    RawData_Sum[i] = 0;                 
                }
                Temp_outrange_cnt++; 
                if(Temp_outrange_cnt == TKEY_QUICK_QUICK_CALIBRATE_TIMES)
                {
                    Temp_outrange_cnt = 0;                
                    //�Զ���СRawData���²�����Χϵ��:sgu16_RawDataRangRatio,ÿ�μ�С��ǰֵ��(1/TKEY_RAWDATA_RANGE_DEC_RATIO)
                    sgu16_RawDataRangRatio -= (sgu16_RawDataRangRatio / TKEY_RAWDATA_RANGE_DEC_RATIO); 
                    if(sgu16_RawDataRangRatio < TKEY_RAWDATA_RANGE_MIN_RATIO)
                    {
                        TKEY_DEBUG("sgu16_RawDataRangRatio less than TKEY_RAWDATA_RANGE_MIN_RATIO\n");
                        return 2;
                    }                   
                }
                goto  QUICK_CALIBRATE;            
            }
            else
            {
                RawData_Sum[ucI] +=  TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData;             
                count[ucI]++;
                if(count[ucI] == TKEY_QUICK_QUICK_CALIBRATE_TIMES)
                {
                    TKEY_Handle.ChannelData[ucI].Tkey_Data->BaseLine =  RawData_Sum[ucI] / TKEY_QUICK_QUICK_CALIBRATE_TIMES;
                }
            }
            RawData_Ref[ucI] = (INT32)TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData;
        }
    } 
    return 0; 
}

/*****************************************************************
@����	TKey������У׼����
@����	��
@����	��
******************************************************************/
void TKEY_Calibrate_Process(void)
{
    uint8_t ucI;
    const TKEY_ChannelDataDef *ChannelData;
    uint16_t average, differ;
    for(ucI = 0; TKEY_Handle.ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        ChannelData = &TKEY_Handle.ChannelData[ucI];
        if(ChannelData->Tkey_CalData->CalFlag == TKEY_CALIBRAT_SELF)//����У׼
        {
            //����
            Bubble_Sort(ChannelData->Tkey_CalData->Caldata, TKEY_CALIBRATE_BUFF_MAX);
            //ȥ���������ֵ&��Сֵ������������ţ�����ƽ��ֵ
            average = Calculate_Sample_Average(&ChannelData->Tkey_CalData->Caldata[2], TKEY_CALIBRATE_BUFF_MAX-4);
            //���㻬��ƽ���˲�
            differ = Calculate_Sample_differ(&ChannelData->Tkey_CalData->Caldata[2], TKEY_CALIBRATE_BUFF_MAX-4, average);     
            
            if(differ <= TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData / sgu16_RawDataRangRatio)
            {
                ChannelData->Tkey_Data->BaseLine = average;
            }
            ChannelData->Tkey_CalData->CalFlag = TKEY_CALIBRAT_IDLE;
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
        }
        else if(ChannelData->Tkey_CalData->CalFlag == TKEY_CALIBRAT_QUICK)//����У׼
        {
            ChannelData->Tkey_CalData->CalFlag = TKEY_CALIBRAT_IDLE;
            TKEY_DEBUG("TK_%d:TKEY_Quick_Calibrate\n",TKEY_Handle.ChannelData[ucI].ChannelId);
            TKEY_DEBUG("TK_%d:Baseline[%d]-Rawdata[%d]\n", TKEY_Handle.ChannelData[ucI].ChannelId, \
            TKEY_Handle.ChannelData[ucI].Tkey_Data->BaseLine, TKEY_Handle.ChannelData[ucI].Tkey_Data->RawData);
            //HAL_TKEY_Quick_Calibrate_RefData(&TKEY_Handle,TKEY_QUICK_QUICK_CALIBRATE_TIMES);
            HAL_TKEY_Quick_Calibrate_RefData_OneChannel(&TKEY_Handle, TKEY_Handle.ChannelData[ucI].ChannelId, TKEY_QUICK_QUICK_CALIBRATE_TIMES);
            TKEY_DEBUG("TK_%d:TKEY_CALIBRAT_SELF BaseLine=%d\n",TKEY_Handle.ChannelData[ucI].ChannelId,TKEY_Handle.ChannelData[ucI].Tkey_Data->BaseLine);
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
        } 
    }
}

/*****************************************************************
@����	TKey����RTC��У׼����
@����	��
@����	��
******************************************************************/
void TKEY_RTC_Calibrate_Process(void)
{
    uint8_t ucI;
    __IO uint32_t *gu32RegTemp;
    uint16_t tempMax = 0, tempMin = 0;

    TKEY->ISR = 0x07;
    while(!READ_BIT(TKEY->ISR, TKEY_ISR_EOC))
    {
        if(!READ_BIT(TKEY->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart. 
            SET_BIT(TKEY->CR, TKEY_CR_START); 
        
        if(READ_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
            return;
        }
    }
    TKEY->ISR = TKEY_ISR_EOC;
    gu32RegTemp = &TKEY->CH0;
    for(ucI = 0; TKEY_Handle.ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        TKEY_Handle.ChannelData[ucI].Tkey_CalData->Caldata[TKEY_Handle.ChannelData[ucI].Tkey_CalData->pos] = *(gu32RegTemp + TKEY_Handle.ChannelData[ucI].ChannelId);
        if((TKEY_Handle.ChannelData[ucI].Tkey_CalData->ScanTimer)++ >= TKEY_CALIBRATE_TIMES)
        {
            TKEY_Handle.ChannelData[ucI].Tkey_CalData->ScanTimer = 0;
            Find_Max_Min(TKEY_Handle.ChannelData[ucI].Tkey_CalData->Caldata, TKEY_CALIBRATE_BUFF_MAX, &tempMax, &tempMin);
            //TKEY_DEBUG("TK_%d:max(%d)-min(%d)=%d,CalibratTH=%d,DetectInTH=%d\n", TKEY_Handle.ChannelData[ucI].ChannelId, tempMax, tempMin,tempMax-tempMin,TKEY_Handle.ChannelData[ucI].Tkey_Data->CalibratTH,TKEY_Handle.ChannelData[ucI].Tkey_RefPara->DetectInTH);
            if((tempMax) && ((tempMax - tempMin) <= TKEY_Handle.ChannelData[ucI].Tkey_Data->CalibratTH))
            {
                Bubble_Sort(TKEY_Handle.ChannelData[ucI].Tkey_CalData->Caldata, TKEY_CALIBRATE_BUFF_MAX);
                TKEY_Handle.ChannelData[ucI].Tkey_Data->BaseLine = (TKEY_Handle.ChannelData[ucI].Tkey_CalData->Caldata[TKEY_CALIBRATE_BUFF_MAX/2-1] + TKEY_Handle.ChannelData[ucI].Tkey_CalData->Caldata[TKEY_CALIBRATE_BUFF_MAX/2]) / 2;
                //TKEY_DEBUG("TK_%d:BaseLine=%d\n",TKEY_Handle.ChannelData[ucI].ChannelId,TKEY_Handle.ChannelData[ucI].Tkey_Data->BaseLine);
            }
        }
        if((TKEY_Handle.ChannelData[ucI].Tkey_CalData->pos)++ >= TKEY_CALIBRATE_BUFF_MAX)
        {
            TKEY_Handle.ChannelData[ucI].Tkey_CalData->pos = 0;
        }
    }
     
}

/*****************************************************************
@����	�������TKEY����,��ACTouchKeyTool V1.01.exe�������ʹ�á�
@����	�� 
@����   ��  
@����	��
******************************************************************/
static void TK_DebugDataOut(void)
{
    uint8_t ucI, i, tk_ch_h, tk_ch_l;
    uint8_t length = 0;
    unsigned short data_checksum = 0;
    
    unsigned short raw_data[16];
    unsigned short base_line[16];
    
    uint8_t gucSendBuff[128], ucSendLength;

    uint8_t opened_tk_amount = TOTAL_CHANNELS;

    for(i = 0; i < opened_tk_amount; i++)
    {
        raw_data[i] = TKEY_Handle.ChannelData[i].Tkey_Data->RawData;

        base_line[i] = TKEY_Handle.ChannelData[i].Tkey_Data->BaseLine;
    }

    tk_ch_h = 0;
    tk_ch_l = 0;
    for(ucI = 0; TKEY_Handle.ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        if(TKEY_Handle.ChannelData[ucI].ChannelId < 8)
        {
            tk_ch_l |= (1 << TKEY_Handle.ChannelData[ucI].ChannelId);
        }
        else
        {
            tk_ch_h |= (1 << (TKEY_Handle.ChannelData[ucI].ChannelId-8));
        }
    }

    ucSendLength = 0;
    memset(gucSendBuff, 0x00, sizeof(gucSendBuff));
    gucSendBuff[ucSendLength++] = 0x55;
    gucSendBuff[ucSendLength++] = 0xAA;
    gucSendBuff[ucSendLength++] = 0x55;
    gucSendBuff[ucSendLength++] = 0xAA;
    
    length = 1 + 2 + 4 + 1 + 16 + 4 * opened_tk_amount + 2;
    
    gucSendBuff[ucSendLength++] = length;
    gucSendBuff[ucSendLength++] = 0;
    gucSendBuff[ucSendLength++] = 0;
    gucSendBuff[ucSendLength++] = 0;
    gucSendBuff[ucSendLength++] = 0;

    data_checksum = length;

    gucSendBuff[ucSendLength++] = tk_ch_h;
    gucSendBuff[ucSendLength++] = tk_ch_l;

    //TK Channel H
    data_checksum += tk_ch_h;
    
    //TK Channel L
    data_checksum += tk_ch_l;

    gucSendBuff[ucSendLength++] = 16;
    //TK Channel MAX
    data_checksum += 16;

    for(i = 0; i < 16; i++)
    {
        gucSendBuff[ucSendLength++] = i;
        data_checksum += i;
    }
    
    for(i = 0; i < opened_tk_amount; i++)
    {
        gucSendBuff[ucSendLength++] = (uint8_t)(base_line[i] >> 8);
        gucSendBuff[ucSendLength++] = (uint8_t)base_line[i];
        data_checksum += (uint8_t)(base_line[i] >> 8);
        data_checksum += (uint8_t)base_line[i];
    }
    
    for(i = 0; i < opened_tk_amount; i++)
    {
        gucSendBuff[ucSendLength++] = (uint8_t)(raw_data[i] >> 8);
        gucSendBuff[ucSendLength++] = (uint8_t)raw_data[i];
        data_checksum += (uint8_t)(raw_data[i] >> 8);
        data_checksum += (uint8_t)raw_data[i];
    }

    data_checksum ^= 0x55AA;

    gucSendBuff[ucSendLength++] = (uint8_t)(data_checksum >> 8);
    gucSendBuff[ucSendLength++] = (uint8_t)data_checksum;
#ifdef TKEY_WAVEFORM_OUTPUT    
    HAL_UART_Transmit(&UART2_Handle, gucSendBuff, ucSendLength, 0);  
#endif    
}

/*****************************************************************
@����	TKey�������Բ������������
@����	��
@����	��
******************************************************************/
void TKEY_Waveform_Output_Process(void)
{
    while(1)
    {
        HAL_TKEY_ReadChannelData(&TKEY_Handle); 
        TK_DebugDataOut();  //Send the date to the PC tools
    }    
}

/*****************************************************************
@����	TKey˯�ߴ���
@����	��
@����	��
******************************************************************/
void TKEY_Suspend(void)
{
    HAL_TKEY_Suspend(&TKEY_Handle); //Set the sleep parameters. 
}

/*****************************************************************
@����	TKey���Ѵ���
@����	��
@����	��
******************************************************************/
void TKEY_Resume(void)
{
    HAL_TKEY_Resume(&TKEY_Handle);  //Resume the wakeup parameters.
}

///*****************************************************************
//@����	Tkey���ѻص�����
//@����	��
//@����	��
//******************************************************************/
//static void TKEY_Wakeup_Callback(void)
//{
//    TKEY_DEBUG("\r\n TKEY_Wakeup_Callback\r\n");
//}

///*****************************************************************
//@����	TKey��������
//@����	��
//@����	��
//******************************************************************/
//void TKEY_Wakeup(void)
//{
//    
//}
/*****************************************************************
@����	����˯��
@����	��
@����	��
******************************************************************/
void TouchKey_suspend(void)
{
    TKEY_Timer_Scan_Stop();
    TKEY_Suspend();
}

/*****************************************************************
@����	�������ѻָ�
@����	��
@����	��
******************************************************************/
void TouchKey_resume(void)
{
    TKEY_Resume();
    TKEY_Timer_ScanInit();
    TKEY_Timer_Scan_Start(); 
}

/*****************************************************************
@ԭ��	uint8_t TouchKey_Init(void)
@����	����ģ�������ʼ��
@����	��
@����	��
******************************************************************/
uint8_t TouchKey_Init(void)
{
    uint8_t ret = 0;
    TKEY_Init();
    TKEY_Calibrate_ParaInit();
    ret = TKEY_Quick_Calibrate(); //У׼�޴���ʱ�Ķ�ȡ���ݼĴ���ֵ 
    TKEY_Timer_ScanInit();
    TKEY_Timer_Scan_Start(); 
    TKEY_DEBUG("sgu16_RawDataRangRatio = %d\n", sgu16_RawDataRangRatio);
    TKEY_DEBUG("sgu8_TKEYScanTime = %d\n", sgu8_TKEYScanTime); 
    return ret;
}

/*****************************************************************
@����	TKeyɨ�貢��ȡ��ֵ��
@����	��
@����	TK_NULL,��ֵ
******************************************************************/
uint8_t TK_Sacn_GetKeyVal(void)
{
    uint8_t  ucKey = 0xFF; 
    HAL_TKEY_DetectProcess(&TKEY_Handle);        
            
    if(TKEY_Handle.ChannelDetectedNum  == 1)
    {
        ucKey = TKEY_Handle.ChannelValue;
    }
    TKEY_Handle.ChannelDetectedNum = 0;
    TKEY_Handle.ChannelValue = 0; 
    return ucKey;
}


/*****************************************************************
@����	TKey��ʱɨ�貢��ȡ��ֵ��
@����	��
@����	TK_NULL,��ֵ
******************************************************************/
uint8_t TK_TimerSacn_GetKeyVal(void)
{
	uint8_t  ucKey = 0xFF;
	TKEY_Timer_Scan_Result(&ucKey);
#ifdef TKEY_WAVEFORM_OUTPUT    
    TK_DebugDataOut();
#endif
    return ucKey;
}

/*****************************************************************
@����	��ȡTKey������ѹ���ͷű�־��
@����	��
@����	��ѹ���ͷű�־��bit0-15��ӦTK0-15��bitΪ1��ʾ�������£�Ϊ0��ʾ�ͷ�
******************************************************************/
uint16_t TK_GetPressRelaeseFlag(void)
{
#ifdef TKEY_WAVEFORM_OUTPUT    
    TK_DebugDataOut();
#endif
    return TKEY_Handle.PressRelaeseFlag;
}
/*****************************************************************
@����	���TKey������ѹ���ͷű�־��ע�⣺�����ͷ�ʱϵͳ���Զ���������ֶ�����ñ�־�����������ͷ�
@����	��
@����	��
******************************************************************/
void TK_ClearPressRelaeseFlag(void)
{
    TKEY_Handle.PressRelaeseFlag = 0;
}

/*****************************************************************
@����	��ȡTKey����������־
@����	��
@����	������־��bit0-15��ӦTK0-15��bitΪ1��ʾ����������Ϊ0��ʾ�ǳ���
******************************************************************/
uint16_t TK_GetLongPressFlag(void)
{
    return TKEY_Handle.LongPressFlag;
}

/*****************************************************************
@����	TKEYɨ��ʱ���л���RC4M
@����	��
@����	��
******************************************************************/
void TouchKey_Switch_Clock_RC4M(void)
{
    SCU->RCHCR |= ((15 << 17) | SCU_RCHCR_RC4M_EN); //RC4M TRIM and Enable.
    while((SCU->RCHCR & SCU_RCHCR_RC4MRDY) == 0x00);
    SCU->CCR2 |= SCU_CCR2_TKSCLK_SEL;  //TKEY use the RC4M as clock.
    TKEY_Quick_Calibrate();   
    TKEY_DEBUG("sgu16_RawDataRangRatio = %d\n", sgu16_RawDataRangRatio);
    TKEY_DEBUG("sgu8_TKEYScanTime = %d\n", sgu8_TKEYScanTime);
}

/*****************************************************************
@����	TKEYɨ��ʱ���л���PCLK
@����	��
@����	��
******************************************************************/
void TouchKey_Switch_Clock_PCLK(void)
{
    SCU->CCR2 &= (~SCU_CCR2_TKSCLK_SEL);  //TKEY use the RC4M as clock.
    TKEY_Quick_Calibrate(); 
    TKEY_DEBUG("sgu16_RawDataRangRatio = %d\n", sgu16_RawDataRangRatio);
    TKEY_DEBUG("sgu8_TKEYScanTime = %d\n", sgu8_TKEYScanTime); 
}

/*****************************************************************
@����	ð�������㷨: �Ƚ����ڵ������������ǰ�߱Ⱥ��ߴ�����н�����
        ÿһ�����������ѡ��һ��δ�������������ŵ�������档
@����	arr: ָ��Ҫת��������
@����   n[IN]:Ҫת�������ݳ���
@����	��	
******************************************************************/
void Bubble_Sort(uint16_t *arr, uint16_t n) 
{
    uint16_t i, j, temp;
    for (i = 0; i<n - 1; i++)
	{
        for (j = 0; j < n - i - 1; j++)
        {
            //���ǰ������Ⱥ���󣬽��н���
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j]; 
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp;
            }
        }
	}
}

/*****************************************************************
@����	�������ֵ����Сֵ
@����	arr: ָ��Ҫ���ҵ�����
@����   max: ָ�����ֵ
@����   min: ָ����Сֵ
@����	��	
******************************************************************/
void Find_Max_Min(uint16_t *arr, uint16_t n, uint16_t *max, uint16_t *min)
{
    uint16_t i, tempMax, tempMin;
    tempMax = arr[0];            // �ٶ���һ����Ϊ���ֵ
    tempMin = arr[0];            // ͬʱ�ٶ�Ҳ��һ����Ϊ���ֵ

    /* �ӵڶ�������ʼ�Ƚϲ�����ֵ */
    for (i = 1; i < n; i++)
    {
        if (arr[i] > tempMax)    // ���ֵ
    	{
    	    tempMax = arr[i];
    	}

    	if (arr[i] < tempMin)   // ��Сֵ������ʹ��else if������������Ƚ�
    	{
    	    tempMin = arr[i];
    	}
    }
    *max = tempMax;
    *min = tempMin;
}


/*****************************************************************
@����	����ƽ��ֵ
@����	arr[IN]: ָ��Ҫ���������
@����   n[IN]:Ҫ��������ݳ���
@����	ƽ��ֵ	
******************************************************************/
uint16_t Calculate_Sample_Average(uint16_t *arr, uint16_t n)
{
    uint16_t average = 0;
    for(uint16_t i = 0; i < n; i++)
    {
        average += arr[i];
        average >>= 1;
    }
    //TKEY_DEBUG("average = %d\r\n", average);
    return average;
}


/*****************************************************************
@����	�������ֵ�Ĳ���ֵ
@����	arr[IN]: ָ��Ҫ���������
@����   n[IN]:Ҫ��������ݳ���
@����   average[IN]:ƽ��ֵ
@����	����ֵ	
******************************************************************/
uint16_t Calculate_Sample_differ(uint16_t *arr, uint16_t n, uint16_t average)
{
    uint32_t sum = 0;
    uint16_t differ;
    for(uint16_t i = 0; i < n; i++)
    {
        sum += abs(arr[i] - average);
    }
    differ = sum/n;
    //TKEY_DEBUG("differ = %d\r\n", differ);
    return differ;
}



