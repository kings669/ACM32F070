#include "ACM32Fxx_HAL.h"
#include <rtthread.h>

int main(void)
{
    System_Init();
	
    GPIO_InitTypeDef GPIOD_Handle; 
	
		GPIOD_Handle.Pin       = GPIO_PIN_3;
    GPIOD_Handle.Mode      = GPIO_MODE_OUTPUT_PP;
    GPIOD_Handle.Pull      = GPIO_PULLUP;
    GPIOD_Handle.Alternate = GPIO_FUNCTION_0;

    HAL_GPIO_Init(GPIOD, &GPIOD_Handle);

    while (1) 
    {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
      rt_thread_mdelay(500);
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_CLEAR);
      rt_thread_mdelay(500);
    }
}

