#include "rtc.h"
#include "ACM32Fxx_HAL.h"
#include <rtthread.h>

void RTC_Config(void)
{
	RTC_ConfigTypeDef RTC_Handle;
	RTC_TimeTypeDef  gstr_Time_Set;
	RTC_DateTypeDef  gstr_Date_Set;
	
	RTC_Handle.u32_ClockSource       = RTC_CLOCK_XTL;
  RTC_Handle.u32_Compensation      = COMPENSATION_INCREASE;    // 开始时钟补偿，如不需补偿设置补偿值为0
  RTC_Handle.u32_CompensationValue = 0x05;                     // 开始时钟补偿，如不需补偿设置补偿值为0

	HAL_RTC_Config(&RTC_Handle);
	
	/* Set RTC Time、Date */
  gstr_Time_Set.u8_Hours   = 0x12;
	gstr_Time_Set.u8_Minutes = 0x30;
	gstr_Time_Set.u8_Seconds = 0x00;
	
	HAL_RTC_SetTime(&gstr_Time_Set);
	
	gstr_Date_Set.u8_Year    = 0x22;    // 2021  
  gstr_Date_Set.u8_Month   = RTC_MONTH_MARCH;  
  gstr_Date_Set.u8_Date    = 0x20; 
  gstr_Date_Set.u8_WeekDay = RTC_WEEKDAY_FRIDAY;
  HAL_RTC_SetDate(&gstr_Date_Set);
}
