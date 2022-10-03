#include "ACM32Fxx_HAL.h"
#include <rtthread.h>
#include "TKey.h"
#include "buzzer.h"
#include "usart.h"

int main(void)
{
		uint8_t  ret = 0;
		uint8_t  fu8_Tkey_state = 0xff;
		BUZZER_Init();
		Uart_Init(115200);
		ret = TouchKey_Init();
		if(ret)
    {
        printfS("TouchKey_Init is Fail!\r\n");
    }
    else
    {
        printfS("TouchKey_Init is Success!\r\n");      
    }
    while (1) 
    {
			fu8_Tkey_state = TK_TimerSacn_GetKeyVal();
			if(fu8_Tkey_state != 0xFF)
      {
            Beep_On(5);
        #ifndef TKEY_WAVEFORM_OUTPUT 
            printfS("TK_%d\r\n", fu8_Tkey_state);
        #endif
      }
      TKEY_Calibrate_Process();
			rt_thread_mdelay(100);
    }
}

