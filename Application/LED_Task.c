#include "LED_Task.h"
#include "led_usr.h"
#include <rtthread.h>
#include "ACM32Fxx_HAL.h"

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       128
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

void LED_entry(void* paramenter)
{
	LED_USR_Init();
	while(1)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
    rt_thread_mdelay(1000);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_CLEAR);
    rt_thread_mdelay(1000);
	}
}


int led_example(void)
{
    tid1 = rt_thread_create("led",
                            LED_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    if(tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }

    return 0;
}

INIT_APP_EXPORT(led_example);

