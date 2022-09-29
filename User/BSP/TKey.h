
#ifndef __TKEY_H__
#define __TKEY_H__

#include "ACM32Fxx_HAL.h"

//#define TKEY_WAVEFORM_OUTPUT              //TKEY������ε�ACTouchKeyTool.exe���Թ���

#define TKEY_FIFO_ENABLE   //��ֵװ��fifoʹ��
 
/****************  TKEY��ʱɨ���������  *****************/
#define TKEY_SCAN_TIMX                      TIM17 
#define TKEY_SCAN_TIMX_IRQn                 TIM17_IRQn 
#define TKEY_SCAN_TIMX_IRQHandler           TIM17_IRQHandler  
#define TKEY_SCAN_TIMX_IRQn_PRIORITY        1      //�ж����ȼ�
#define TKEY_SCAN_TIM_PERIOD                5      //TKEYɨ�趨ʱ������(ms)

/*******************************************************/


#define TKEY_QUICK_QUICK_CALIBRATE_TIMES    5    //����У׼����

/******************************************************************************
*  ɨ��ȴ�ʱ��:ֵԽ��,������Ӧ�ٶȱ��������ΪTKEY_SCAN_WAIT_MAX_TIMES; ֵ��С�ᵼ�»�ȡ����RawDataֵ��
*******************************************************************************/
#define TKEY_SCAN_WAIT_TIMES              20 
#define TKEY_SCAN_WAIT_MAX_TIMES          100  
/******************************************************************************
*  ɨ��ȴ�ʱ����Լ�ϵ��:ֵԽ��,�Լ�ԽС,�Լ��ٶ�Խ��,У׼ʱ������;
*  ֵԽС,�Լ�ֵԽ��,�Լ��ٶ�Խ�죬У׼ʱ���С;
*******************************************************************************/
#define TKEY_SCAN_WAIT_TIMES_RATIO        10  //20% 

/******************************************************************************
*  RawData���²�����Χϵ��:ֵԽ��,������ΧԽС,BsaeLineֵԽ�ӽ�RawData,У׼Խ׼ȷ;
*  ֵ����ᵼ�»�ȡ����BsaeLineֵ,У׼��������СֵΪTKEY_RAWDATA_RANGE_MIN_RATIO
*  ������Χ[-RawData/TKEY_DELTA_DIVISOR, +RawData/TKEY_DELTA_DIVISOR] 
*******************************************************************************/
#define TKEY_RAWDATA_RANGE_RATIO          300
#define TKEY_RAWDATA_RANGE_MIN_RATIO      200  
/******************************************************************************
*  RawData���²�����Χϵ�����Լ�ϵ��:ֵԽ��,�Լ�ԽС,�Լ��ٶ�Խ��,У׼ʱ������;
*  ֵԽС,�Լ�ֵԽ��,�Լ��ٶ�Խ�죬У׼ʱ���С;
*******************************************************************************/
#define TKEY_RAWDATA_RANGE_DEC_RATIO      10  //10% 


/******************************************************************************
*  TKey 16ͨ��ʹ�ܺ궨��
*  ��Ҫʹ����·������ʹ�ܸ�ͨ��;δʹ�õİ���ͨ����Ҫʹ��,��ȻУ׼��ʧ��
*******************************************************************************/
//#define TKEY_CHANNEL_0_ENABLE        //--��ӦоƬ�ܽ�TVCX0, ��λ������TK_0               
//#define TKEY_CHANNEL_1_ENABLE           //--��ӦоƬ�ܽ�TVCX1, ��λ������TK_1	               
//#define TKEY_CHANNEL_2_ENABLE           //--��ӦоƬ�ܽ�TVCX2, ��λ������TK_2                
//#define TKEY_CHANNEL_3_ENABLE        //--��ӦоƬ�ܽ�TVCX3, ��λ������TK_3                  
//#define TKEY_CHANNEL_4_ENABLE           //--��ӦоƬ�ܽ�TVCX4, ��λ������TK_4                
//#define TKEY_CHANNEL_5_ENABLE           //--��ӦоƬ�ܽ�TVCX5, ��λ������TK_5              
//#define TKEY_CHANNEL_6_ENABLE        //--��ӦоƬ�ܽ�TVCX6, ��λ������TK_6                 
#define TKEY_CHANNEL_7_ENABLE        //--��ӦоƬ�ܽ�TVCX7, ��λ������TK_7                 
#define TKEY_CHANNEL_8_ENABLE           //--��ӦоƬ�ܽ�TVCX8, ��λ������TK_8                
#define TKEY_CHANNEL_9_ENABLE           //--��ӦоƬ�ܽ�TVCX9, ��λ������TK_9               
#define TKEY_CHANNEL_10_ENABLE          //--��ӦоƬ�ܽ�TVCX10, ��λ������TK_10             
#define TKEY_CHANNEL_11_ENABLE          //--��ӦоƬ�ܽ�TVCX11, ��λ������TK_11            
//#define TKEY_CHANNEL_12_ENABLE          //--��ӦоƬ�ܽ�TVCX12, ��λ������TK_12               
//#define TKEY_CHANNEL_13_ENABLE          //--��ӦоƬ�ܽ�TVCX13, ��λ������TK_13              
//#define TKEY_CHANNEL_14_ENABLE          //--��ӦоƬ�ܽ�TVCX14, ��λ������TK_14 
//OK               
#define TKEY_CHANNEL_15_ENABLE          //--��ӦоƬ�ܽ�TVCX15, ��λ������TK_15            


/******************************************************************************
*  TKey 16ͨ������ģʽ������
*  ֵԽС,����������Խ��;ֵԽ��,����������Խ��.δʹ�ܵİ���ͨ����������Ϊ4095.
*******************************************************************************/
#define TKEY_0_SENSITIVITY            4095    //--��ӦоƬ�ܽ�TVCX0, ��λ������TK_0
#define TKEY_1_SENSITIVITY            4095	  //--��ӦоƬ�ܽ�TVCX1, ��λ������TK_1		
#define TKEY_2_SENSITIVITY            4095      //--��ӦоƬ�ܽ�TVCX2, ��λ������TK_2 
#define TKEY_3_SENSITIVITY            4095    //--��ӦоƬ�ܽ�TVCX3, ��λ������TK_3 
#define TKEY_4_SENSITIVITY            4095      //--��ӦоƬ�ܽ�TVCX4, ��λ������TK_4  
#define TKEY_5_SENSITIVITY            4095      //--��ӦоƬ�ܽ�TVCX5, ��λ������TK_5
#define TKEY_6_SENSITIVITY            4095    //--��ӦоƬ�ܽ�TVCX6, ��λ������TK_6 
#define TKEY_7_SENSITIVITY            60    //--��ӦоƬ�ܽ�TVCX7, ��λ������TK_7
#define TKEY_8_SENSITIVITY            60      //--��ӦоƬ�ܽ�TVCX8, ��λ������TK_8 
#define TKEY_9_SENSITIVITY            60      //--��ӦоƬ�ܽ�TVCX9, ��λ������TK_9
#define TKEY_10_SENSITIVITY           60      //--��ӦоƬ�ܽ�TVCX10, ��λ������TK_10 
#define TKEY_11_SENSITIVITY           60      //--��ӦоƬ�ܽ�TVCX11, ��λ������TK_11
#define TKEY_12_SENSITIVITY           4095      //--��ӦоƬ�ܽ�TVCX12, ��λ������TK_12
#define TKEY_13_SENSITIVITY           4095      //--��ӦоƬ�ܽ�TVCX13, ��λ������TK_13
#define TKEY_14_SENSITIVITY           4095      //--��ӦоƬ�ܽ�TVCX14, ��λ������TK_14
#define TKEY_15_SENSITIVITY           60      //--��ӦоƬ�ܽ�TVCX15, ��λ������TK_15 

/******************************************************************************
*  TKey 16ͨ��˯��ģʽ������
*  ֵԽС,����������Խ��;ֵԽ��,����������Խ��.δʹ�ܵİ���ͨ����������Ϊ4095.
*******************************************************************************/
#define TKEY_0_SLEEP_SENSITIVITY           (TKEY_0_SENSITIVITY)    //--��ӦоƬ�ܽ�TVCX0, ��λ������TK_0
#define TKEY_1_SLEEP_SENSITIVITY           (TKEY_1_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX1, ��λ������TK_1
#define TKEY_2_SLEEP_SENSITIVITY           (TKEY_2_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX2, ��λ������TK_2 
#define TKEY_3_SLEEP_SENSITIVITY           (TKEY_3_SENSITIVITY)     //--��ӦоƬ�ܽ�TVCX3, ��λ������TK_3  
#define TKEY_4_SLEEP_SENSITIVITY           (TKEY_4_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX4, ��λ������TK_4 
#define TKEY_5_SLEEP_SENSITIVITY           (TKEY_5_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX5, ��λ������TK_5  
#define TKEY_6_SLEEP_SENSITIVITY           (TKEY_6_SENSITIVITY)     //--��ӦоƬ�ܽ�TVCX6, ��λ������TK_6  
#define TKEY_7_SLEEP_SENSITIVITY           (TKEY_7_SENSITIVITY)     //--��ӦоƬ�ܽ�TVCX7, ��λ������TK_7  
#define TKEY_8_SLEEP_SENSITIVITY           (TKEY_8_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX8, ��λ������TK_8  
#define TKEY_9_SLEEP_SENSITIVITY           (TKEY_9_SENSITIVITY)      //--��ӦоƬ�ܽ�TVCX9, ��λ������TK_9  
#define TKEY_10_SLEEP_SENSITIVITY          (TKEY_10_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX10, ��λ������TK_10 
#define TKEY_11_SLEEP_SENSITIVITY          (TKEY_11_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX11, ��λ������TK_11  
#define TKEY_12_SLEEP_SENSITIVITY          (TKEY_12_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX12, ��λ������TK_12  
#define TKEY_13_SLEEP_SENSITIVITY          (TKEY_13_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX13, ��λ������TK_13  
#define TKEY_14_SLEEP_SENSITIVITY          (TKEY_14_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX14, ��λ������TK_14  
#define TKEY_15_SLEEP_SENSITIVITY          (TKEY_15_SENSITIVITY)       //--��ӦоƬ�ܽ�TVCX15, ��λ������TK_15 


typedef enum{
#ifdef  TKEY_CHANNEL_0_ENABLE 
  TK_0,   //0
#endif
#ifdef  TKEY_CHANNEL_1_ENABLE   
  TK_1,   //1
#endif
#ifdef  TKEY_CHANNEL_2_ENABLE 
  TK_2,   //2
#endif
#ifdef  TKEY_CHANNEL_3_ENABLE   
  TK_3,   //3
#endif
#ifdef  TKEY_CHANNEL_4_ENABLE   
  TK_4,   //4
#endif
#ifdef  TKEY_CHANNEL_5_ENABLE   
  TK_5,   //5
#endif
#ifdef  TKEY_CHANNEL_6_ENABLE   
  TK_6,   //6
#endif
#ifdef  TKEY_CHANNEL_7_ENABLE   
  TK_7,   //7
#endif
#ifdef  TKEY_CHANNEL_8_ENABLE   
  TK_8,   //8
#endif
#ifdef  TKEY_CHANNEL_9_ENABLE   
  TK_9,   //9
#endif
#ifdef  TKEY_CHANNEL_10_ENABLE   
  TK_10,  //10
#endif  
#ifdef  TKEY_CHANNEL_11_ENABLE   
  TK_11,  //11
#endif
#ifdef  TKEY_CHANNEL_12_ENABLE  
  TK_12,  //12
#endif
#ifdef  TKEY_CHANNEL_13_ENABLE   
  TK_13,  //13
#endif
#ifdef  TKEY_CHANNEL_14_ENABLE   
  TK_14,  //14
#endif
#ifdef  TKEY_CHANNEL_15_ENABLE   
  TK_15,   //15
#endif  
  TOTAL_CHANNELS
}TK_Index_enum_T;

void TKEY_Calibrate_ParaInit(void);

void TKEY_Timer_ScanInit(void);

void TKEY_Scan_FIFO_Clear(void);

void TKEY_Timer_Scan_Start(void);

void TKEY_Timer_Scan_Stop(void);

void TKEY_Timer_Scan_Result(uint8_t *pucKey);

void TKEY_Init(void);

void TKEY_Suspend(void);

void TKEY_Resume(void);

void TKEY_Wakeup(void);

uint8_t TKEY_Quick_Calibrate(void);

void TKEY_Waveform_Output_Process(void);

uint8_t TK_Sacn_GetKeyVal(void);

void TKEY_Calibrate_Process(void);

void TKEY_RTC_Calibrate_Process(void);

void TouchKey_suspend(void);

void TouchKey_resume(void);

uint8_t TouchKey_Init(void);

uint8_t TK_TimerSacn_GetKeyVal(void);

void Bubble_Sort(uint16_t *arr, uint16_t n);

void Find_Max_Min(uint16_t *arr, uint16_t n, uint16_t *max, uint16_t *min);

uint16_t Calculate_Sample_Average(uint16_t *arr, uint16_t n);

uint16_t Calculate_Sample_differ(uint16_t *arr, uint16_t n, uint16_t average);

uint16_t TK_GetPressRelaeseFlag(void);

void TK_ClearPressRelaeseFlag(void);

uint16_t TK_GetLongPressFlag(void);

void TouchKey_Switch_Clock_RC4M(void);

void TouchKey_Switch_Clock_PCLK(void);

#endif
