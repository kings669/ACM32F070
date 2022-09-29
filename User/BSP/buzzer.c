
#include "buzzer.h"


#define BUZZER_GPIO_PORT GPIOD
#define BUZZER_GPIO_PIN  GPIO_PIN_1

/*****************************************************************
@原型	void BUZZER_Init(void)
@功能	蜂鸣器初始化
@参数	无	 
@返回	无
******************************************************************/
void BUZZER_Init(void)
{
    GPIO_InitTypeDef GPIOx_Handle;    
    GPIOx_Handle.Pin       = BUZZER_GPIO_PIN;
    GPIOx_Handle.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIOx_Handle.Pull      = GPIO_NOPULL;
    GPIOx_Handle.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIOx_Handle);  
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_CLEAR);
}

/*****************************************************************
@功能	蜂鸣器鸣叫(阻塞式)
@参数	ms - 持续时间	 
@返回	无
******************************************************************/
void Beep_On(int ms)
{
    GPIOCD->SET = (BUZZER_GPIO_PIN<<16);
    System_Delay_MS(ms);
    GPIOCD->CLR = (BUZZER_GPIO_PIN<<16);
}





