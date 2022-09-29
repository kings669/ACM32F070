
#ifndef __TKEY_H__
#define __TKEY_H__

#include "ACM32Fxx_HAL.h"

//#define TKEY_WAVEFORM_OUTPUT              //TKEY输出波形到ACTouchKeyTool.exe调试工具

#define TKEY_FIFO_ENABLE   //键值装入fifo使能
 
/****************  TKEY定时扫描相关配置  *****************/
#define TKEY_SCAN_TIMX                      TIM17 
#define TKEY_SCAN_TIMX_IRQn                 TIM17_IRQn 
#define TKEY_SCAN_TIMX_IRQHandler           TIM17_IRQHandler  
#define TKEY_SCAN_TIMX_IRQn_PRIORITY        1      //中断优先级
#define TKEY_SCAN_TIM_PERIOD                5      //TKEY扫描定时器周期(ms)

/*******************************************************/


#define TKEY_QUICK_QUICK_CALIBRATE_TIMES    5    //快速校准次数

/******************************************************************************
*  扫描等待时间:值越大,按键响应速度变慢，最大为TKEY_SCAN_WAIT_MAX_TIMES; 值过小会导致获取不到RawData值。
*******************************************************************************/
#define TKEY_SCAN_WAIT_TIMES              20 
#define TKEY_SCAN_WAIT_MAX_TIMES          100  
/******************************************************************************
*  扫描等待时间的自加系数:值越大,自加越小,自加速度越慢,校准时间增加;
*  值越小,自加值越大,自加速度越快，校准时间减小;
*******************************************************************************/
#define TKEY_SCAN_WAIT_TIMES_RATIO        10  //20% 

/******************************************************************************
*  RawData上下波动范围系数:值越大,波动范围越小,BsaeLine值越接近RawData,校准越准确;
*  值过大会导致获取不到BsaeLine值,校准不过。最小值为TKEY_RAWDATA_RANGE_MIN_RATIO
*  波动范围[-RawData/TKEY_DELTA_DIVISOR, +RawData/TKEY_DELTA_DIVISOR] 
*******************************************************************************/
#define TKEY_RAWDATA_RANGE_RATIO          300
#define TKEY_RAWDATA_RANGE_MIN_RATIO      200  
/******************************************************************************
*  RawData上下波动范围系数的自减系数:值越大,自减越小,自减速度越慢,校准时间增加;
*  值越小,自减值越大,自减速度越快，校准时间减小;
*******************************************************************************/
#define TKEY_RAWDATA_RANGE_DEC_RATIO      10  //10% 


/******************************************************************************
*  TKey 16通道使能宏定义
*  需要使用哪路按键就使能该通道;未使用的按键通道不要使能,不然校准会失败
*******************************************************************************/
//#define TKEY_CHANNEL_0_ENABLE        //--对应芯片管脚TVCX0, 上位机工具TK_0               
//#define TKEY_CHANNEL_1_ENABLE           //--对应芯片管脚TVCX1, 上位机工具TK_1	               
//#define TKEY_CHANNEL_2_ENABLE           //--对应芯片管脚TVCX2, 上位机工具TK_2                
//#define TKEY_CHANNEL_3_ENABLE        //--对应芯片管脚TVCX3, 上位机工具TK_3                  
//#define TKEY_CHANNEL_4_ENABLE           //--对应芯片管脚TVCX4, 上位机工具TK_4                
//#define TKEY_CHANNEL_5_ENABLE           //--对应芯片管脚TVCX5, 上位机工具TK_5              
//#define TKEY_CHANNEL_6_ENABLE        //--对应芯片管脚TVCX6, 上位机工具TK_6                 
#define TKEY_CHANNEL_7_ENABLE        //--对应芯片管脚TVCX7, 上位机工具TK_7                 
#define TKEY_CHANNEL_8_ENABLE           //--对应芯片管脚TVCX8, 上位机工具TK_8                
#define TKEY_CHANNEL_9_ENABLE           //--对应芯片管脚TVCX9, 上位机工具TK_9               
#define TKEY_CHANNEL_10_ENABLE          //--对应芯片管脚TVCX10, 上位机工具TK_10             
#define TKEY_CHANNEL_11_ENABLE          //--对应芯片管脚TVCX11, 上位机工具TK_11            
//#define TKEY_CHANNEL_12_ENABLE          //--对应芯片管脚TVCX12, 上位机工具TK_12               
//#define TKEY_CHANNEL_13_ENABLE          //--对应芯片管脚TVCX13, 上位机工具TK_13              
//#define TKEY_CHANNEL_14_ENABLE          //--对应芯片管脚TVCX14, 上位机工具TK_14 
//OK               
#define TKEY_CHANNEL_15_ENABLE          //--对应芯片管脚TVCX15, 上位机工具TK_15            


/******************************************************************************
*  TKey 16通道工作模式灵敏度
*  值越小,按键灵敏度越高;值越大,按键灵敏度越低.未使能的按键通道灵敏度设为4095.
*******************************************************************************/
#define TKEY_0_SENSITIVITY            4095    //--对应芯片管脚TVCX0, 上位机工具TK_0
#define TKEY_1_SENSITIVITY            4095	  //--对应芯片管脚TVCX1, 上位机工具TK_1		
#define TKEY_2_SENSITIVITY            4095      //--对应芯片管脚TVCX2, 上位机工具TK_2 
#define TKEY_3_SENSITIVITY            4095    //--对应芯片管脚TVCX3, 上位机工具TK_3 
#define TKEY_4_SENSITIVITY            4095      //--对应芯片管脚TVCX4, 上位机工具TK_4  
#define TKEY_5_SENSITIVITY            4095      //--对应芯片管脚TVCX5, 上位机工具TK_5
#define TKEY_6_SENSITIVITY            4095    //--对应芯片管脚TVCX6, 上位机工具TK_6 
#define TKEY_7_SENSITIVITY            60    //--对应芯片管脚TVCX7, 上位机工具TK_7
#define TKEY_8_SENSITIVITY            60      //--对应芯片管脚TVCX8, 上位机工具TK_8 
#define TKEY_9_SENSITIVITY            60      //--对应芯片管脚TVCX9, 上位机工具TK_9
#define TKEY_10_SENSITIVITY           60      //--对应芯片管脚TVCX10, 上位机工具TK_10 
#define TKEY_11_SENSITIVITY           60      //--对应芯片管脚TVCX11, 上位机工具TK_11
#define TKEY_12_SENSITIVITY           4095      //--对应芯片管脚TVCX12, 上位机工具TK_12
#define TKEY_13_SENSITIVITY           4095      //--对应芯片管脚TVCX13, 上位机工具TK_13
#define TKEY_14_SENSITIVITY           4095      //--对应芯片管脚TVCX14, 上位机工具TK_14
#define TKEY_15_SENSITIVITY           60      //--对应芯片管脚TVCX15, 上位机工具TK_15 

/******************************************************************************
*  TKey 16通道睡眠模式灵敏度
*  值越小,按键灵敏度越高;值越大,按键灵敏度越低.未使能的按键通道灵敏度设为4095.
*******************************************************************************/
#define TKEY_0_SLEEP_SENSITIVITY           (TKEY_0_SENSITIVITY)    //--对应芯片管脚TVCX0, 上位机工具TK_0
#define TKEY_1_SLEEP_SENSITIVITY           (TKEY_1_SENSITIVITY)       //--对应芯片管脚TVCX1, 上位机工具TK_1
#define TKEY_2_SLEEP_SENSITIVITY           (TKEY_2_SENSITIVITY)       //--对应芯片管脚TVCX2, 上位机工具TK_2 
#define TKEY_3_SLEEP_SENSITIVITY           (TKEY_3_SENSITIVITY)     //--对应芯片管脚TVCX3, 上位机工具TK_3  
#define TKEY_4_SLEEP_SENSITIVITY           (TKEY_4_SENSITIVITY)       //--对应芯片管脚TVCX4, 上位机工具TK_4 
#define TKEY_5_SLEEP_SENSITIVITY           (TKEY_5_SENSITIVITY)       //--对应芯片管脚TVCX5, 上位机工具TK_5  
#define TKEY_6_SLEEP_SENSITIVITY           (TKEY_6_SENSITIVITY)     //--对应芯片管脚TVCX6, 上位机工具TK_6  
#define TKEY_7_SLEEP_SENSITIVITY           (TKEY_7_SENSITIVITY)     //--对应芯片管脚TVCX7, 上位机工具TK_7  
#define TKEY_8_SLEEP_SENSITIVITY           (TKEY_8_SENSITIVITY)       //--对应芯片管脚TVCX8, 上位机工具TK_8  
#define TKEY_9_SLEEP_SENSITIVITY           (TKEY_9_SENSITIVITY)      //--对应芯片管脚TVCX9, 上位机工具TK_9  
#define TKEY_10_SLEEP_SENSITIVITY          (TKEY_10_SENSITIVITY)       //--对应芯片管脚TVCX10, 上位机工具TK_10 
#define TKEY_11_SLEEP_SENSITIVITY          (TKEY_11_SENSITIVITY)       //--对应芯片管脚TVCX11, 上位机工具TK_11  
#define TKEY_12_SLEEP_SENSITIVITY          (TKEY_12_SENSITIVITY)       //--对应芯片管脚TVCX12, 上位机工具TK_12  
#define TKEY_13_SLEEP_SENSITIVITY          (TKEY_13_SENSITIVITY)       //--对应芯片管脚TVCX13, 上位机工具TK_13  
#define TKEY_14_SLEEP_SENSITIVITY          (TKEY_14_SENSITIVITY)       //--对应芯片管脚TVCX14, 上位机工具TK_14  
#define TKEY_15_SLEEP_SENSITIVITY          (TKEY_15_SENSITIVITY)       //--对应芯片管脚TVCX15, 上位机工具TK_15 


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
