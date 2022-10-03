#include "usart.h"


UART_HandleTypeDef UART2_Handle;


/************************************************************************
 * function   : Uart_Init
 * Description: Uart Initiation. 
 ************************************************************************/ 
void Uart_Init(uint32_t fu32_Baudrate)
{
    UART2_Handle.Instance = UART2;
    UART2_Handle.Init.BaudRate   = fu32_Baudrate;
    UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    UART2_Handle.Init.StopBits   = UART_STOPBITS_1;
    UART2_Handle.Init.Parity     = UART_PARITY_NONE;
    UART2_Handle.Init.Mode       = UART_MODE_TX_RX_DEBUG;
    UART2_Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;

    HAL_UART_Init(&UART2_Handle);
	
    /* UART_DEBUG_ENABLE control printfS */   
    printfS("MCU is running, HCLK=%dHz, PCLK=%dHz\n", System_Get_SystemClock(), System_Get_APBClock());
}