/*
  ******************************************************************************
  * @file    SHT30.c
  * @author  ZK
  * @version V1.0.0
  * @date    2022
  * @brief   SHT30 driver Source file.
  ******************************************************************************
*/
#include "SHT30.h"
#include "ACM32Fxx_HAL.h"

I2C_HandleTypeDef I2C_Handle;   //I2C Handle指针


/************************************************************************
 * function   : HAL_I2C_MspInit
 * Description: 
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    
    /* I2C1 */

    /* I2C2 */
    if (hi2c->Instance == I2C2) 
    {
        System_Module_Enable(EN_I2C2);  
        System_Module_Enable(EN_GPIOCD);   

        /* I2C2 SDA  PortD Pin7 */
        /* I2C2 SCL  PortD Pin6 */
        GPIO_Handle.Pin            = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull           = GPIO_PULLUP;
        GPIO_Handle.Alternate      = GPIO_FUNCTION_1;
        HAL_GPIO_Init(GPIOD, &GPIO_Handle);
        
        /* Clear Pending Interrupt */
        NVIC_ClearPendingIRQ(I2C2_IRQn);
        
        /* Enable External Interrupt */
        NVIC_EnableIRQ(I2C2_IRQn);
    }
}

/************************************************************************
 * function   : I2C_Init
 * Description: I2C Initiation. 
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
 ************************************************************************/ 
void I2C_Init(void)
{
    I2C_Handle.Instance         = I2C2;
    I2C_Handle.Init.I2C_Mode    = I2C_MODE_MASTER;
    I2C_Handle.Init.Tx_Auto_En  = TX_AUTO_EN_ENABLE;
    I2C_Handle.Init.Clock_Speed = CLOCK_SPEED_STANDARD;  
    I2C_Handle.Init.No_Stretch_Mode = NO_STRETCH_MODE_NOSTRETCH;   
    
    HAL_I2C_Init(&I2C_Handle);
}


///**
// * @brief    从SHT30读取一次数据
// * @param    dat —— 存储读取数据的地址（6个字节数组）
// * @retval    成功 —— 返回HAL_OK
//*/
uint8_t SHT30_Read_Dat(I2C_HandleTypeDef I2C_Handle,uint8_t* dat)
{
    uint8_t cmd_buffer[2];
    cmd_buffer[0] = HIGH_ENABLED_CMD >> 8;
    cmd_buffer[1] = HIGH_ENABLED_CMD & 0XFF;   
    HAL_I2C_Master_Transmit(&I2C_Handle, SHT30_SLAVE_ADDRESS, cmd_buffer, 2,100);
    System_Delay_MS(100);
    return HAL_I2C_Master_Receive(&I2C_Handle, SHT30_SLAVE_ADDRESS, dat, 6,100);
}


/************************************************************************
 * function   : SHT30_Read_Result
 * Description: get SHT30 result 
* Input       : 
* Outpu       : 
* Author      : ZK                         Data : 2022年
 ************************************************************************/ 
void SHT30_Read_Result(uint8_t *sht30_data,float *getTempHum)
{
	uint16_t tem,hum;
	float Temperature=0;
	float Humidity=0;
    tem = ((sht30_data[0]<<8) | sht30_data[1]);//温度拼接
    hum = ((sht30_data[3]<<8) | sht30_data[4]);//湿度拼接
    
    /*转换实际温度*/
    Temperature= (175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)
    Humidity= (100.0*(float)hum/65535.0);// RH = hum*100 / (2^16-1)
    
//    if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//过滤错误数据
//    {
//        printfS("%6.2f*C %6.2f%%",Temperature,Humidity);//111.01*C 100.01%（保留2位小数）
//    }
    getTempHum[0]=Temperature;
    getTempHum[1]=Humidity;
}

uint8_t SHT30_Reset(I2C_HandleTypeDef I2C_Handle)
{
    HAL_StatusTypeDef Status;
    uint8_t cmd_buffer[2];
    cmd_buffer[0] = SOFT_RESET_CMD >> 8;
    cmd_buffer[1] = SOFT_RESET_CMD & 0XFF;   
    Status=HAL_I2C_Master_Transmit(&I2C_Handle, SHT30_SLAVE_ADDRESS, cmd_buffer, 2,100);    
    System_Delay_MS(500); 

    cmd_buffer[0] = CLEAR_STATES_CMD >> 8;
    cmd_buffer[1] = CLEAR_STATES_CMD & 0XFF;   
    Status=HAL_I2C_Master_Transmit(&I2C_Handle, SHT30_SLAVE_ADDRESS, cmd_buffer, 2,100);    
    System_Delay_MS(200); 
    return Status;
}

void SHT30_Init(void)
{
	I2C_Init();
	SHT30_Reset(I2C_Handle);
}
