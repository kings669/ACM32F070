#include "LCD_Task.h"
#include "ACM32Fxx_HAL.h"
#include "rtc.h"
#include <rtthread.h>

#define THREAD_PRIORITY         5
#define THREAD_STACK_SIZE       1024
#define THREAD_TIMESLICE        5

static rt_thread_t tid2 = RT_NULL;

RTC_TimeTypeDef  gstr_Time_Get;
RTC_DateTypeDef  gstr_Date_Get;

LCD_HandleTypeDef         *lcdhandle;  //LCD Handle指针
extern LCD_HandleTypeDef         lcdhandle_GDC04212;
extern LCD_HandleTypeDef         lcdhandle_GDC03828;
extern LCD_HandleTypeDef         lcdhandle_YR1618A;

void(*LCD_DisplayNum)(uint32_t);//LCD显示函数指针

void(*LCD_Init)(void);//LCD初始化函数指针

void LCD_Config(void);

void LCD_up_display(int num);
void LCD_time_display(void);

uint32_t fu32_Displayup[4]={0},fu32_Displaydown[4]={0},fu32_num_123567p[7]={0},fu32_num_col[2]={1,0},fu32_num_s=0;

void LCD_entry(void* paramenter)
{
	LCD_Config();
	LCD_YR1618A_SelfDisplay();
	RTC_Config();
	while(1)
	{
		LCD_time_display();
		LCD_YR1618A_VIEW(fu32_Displayup,fu32_Displaydown,fu32_num_123567p,fu32_num_col,fu32_num_s);
		rt_thread_mdelay(50);
	}
}

void LCD_time_display(void)
{
	HAL_RTC_GetTime(&gstr_Time_Get);
  HAL_RTC_GetDate(&gstr_Date_Get);  
	
	fu32_Displayup[0]=(gstr_Time_Get.u8_Hours & 0xF0)>>4;
	fu32_Displayup[1]=(gstr_Time_Get.u8_Hours & 0x0F);
	fu32_Displayup[2]=(gstr_Time_Get.u8_Minutes & 0xF0)>>4;
	fu32_Displayup[3]=(gstr_Time_Get.u8_Minutes & 0x0F);
	
	fu32_Displaydown[2]=(gstr_Time_Get.u8_Seconds & 0xF0)>>4;
	fu32_Displaydown[3]=(gstr_Time_Get.u8_Seconds & 0x0F);
}

void LCD_up_display(int num)
{
	if(num>9999) num=9999;//4位数，最大显示9999
	fu32_Displayup[0]=num/1000%10;//千位,LCD第1个位置(从左到右)--5
	fu32_Displayup[1]=num/100%10;//白位,LCD第2个位置(从左到右)---6
	fu32_Displayup[2]=num/10%10;//十位,LCD第3个位置(从左到右)----7
	fu32_Displayup[3]=num/1%10;//个位,LCD第4个位置(从左到右)-----8
}

int lcd_example(void)
{
    tid2 = rt_thread_create("lcd",
                            LCD_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    if(tid2 != RT_NULL)
    {
        rt_thread_startup(tid2);
    }

    return 0;
}

INIT_APP_EXPORT(lcd_example);

/*********************************************************************************
* Function    : LCD_Config
* Description : Config LCD
* Input       : 
* Outpu       : 
* Author      : CWT                         Data : 2021年
**********************************************************************************/
void LCD_Config(void)
{   
    
    #if defined LCD_GDC04212
        LCD_DisplayNum=LCD_DisplayNum_GDC04212;
        LCD_Init=LCD_Init_GDC04212; 
        lcdhandle=&lcdhandle_GDC04212;

    #elif defined LCD_GDC03828
        LCD_DisplayNum=LCD_DisplayNum_GDC003828;
        LCD_Init=LCD_Init_GDC03828;
        lcdhandle=&lcdhandle_GDC03828;

    #else 
        LCD_DisplayNum=LCD_DisplayNum_YR1618A;
        LCD_Init=LCD_Init_YR1618A; 
        lcdhandle=&lcdhandle_YR1618A;
        

    #endif  
        LCD_Init();
        LCD_BACK_LED();
}

/*********************************************************************************
* Function    : LCD_IRQHandler
* Description : LCD Interrupt handler
* Input       : 
* Outpu       : 
* Author      : CWT                         Data : 2021年
**********************************************************************************/
void LCD_IRQHandler(void) 
{
    HAL_LCD_IRQHandler(lcdhandle);
  
}

