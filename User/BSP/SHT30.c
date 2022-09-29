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
