#include "led_usr.h"
#include "ACM32Fxx_HAL.h"

void LED_USR_Init(void)
{
	GPIO_InitTypeDef GPIOD_Handle; 
	
  GPIOD_Handle.Pin       = GPIO_PIN_3;
  GPIOD_Handle.Mode      = GPIO_MODE_OUTPUT_PP;
  GPIOD_Handle.Pull      = GPIO_PULLUP;
  GPIOD_Handle.Alternate = GPIO_FUNCTION_0;

  HAL_GPIO_Init(GPIOD, &GPIOD_Handle);
}
