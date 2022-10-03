/*
  ******************************************************************************
  * @file    SHT30.c
  * @author  ZK
  * @version V1.0.0
  * @date    2022
  * @brief   SHT30 driver header Source file.
  ******************************************************************************
*/
#ifndef __SHT30_H
#define __SHT30_H

#include "ACM32Fxx_HAL.h"

typedef enum
{
    /* 软件复位命令 */

    SOFT_RESET_CMD = 0x30A2,    
    CLEAR_STATES_CMD = 0x3041,    
    /*
    单次测量模式
    命名格式：Repeatability_CS_CMD
    CS：Clock stretching
    */
    HIGH_ENABLED_CMD    = 0x2C06,
    MEDIUM_ENABLED_CMD  = 0x2C0D,
    LOW_ENABLED_CMD     = 0x2C10,
    HIGH_DISABLED_CMD   = 0x2400,
    MEDIUM_DISABLED_CMD = 0x240B,
    LOW_DISABLED_CMD    = 0x2416,

    /*
    周期测量模式
    命名格式：Repeatability_MPS_CMD
    MPS：measurement per second
    */
    HIGH_0_5_CMD   = 0x2032,
    MEDIUM_0_5_CMD = 0x2024,
    LOW_0_5_CMD    = 0x202F,
    HIGH_1_CMD     = 0x2130,
    MEDIUM_1_CMD   = 0x2126,
    LOW_1_CMD      = 0x212D,
    HIGH_2_CMD     = 0x2236,
    MEDIUM_2_CMD   = 0x2220,
    LOW_2_CMD      = 0x222B,
    HIGH_4_CMD     = 0x2334,
    MEDIUM_4_CMD   = 0x2322,
    LOW_4_CMD      = 0x2329,
    HIGH_10_CMD    = 0x2737,
    MEDIUM_10_CMD  = 0x2721,
    LOW_10_CMD     = 0x272A,
    /* 周期测量模式读取数据命令 */
    READOUT_FOR_PERIODIC_MODE = 0xE000,
} SHT30_CMD;

//SHT30_I2C,I2C2
#define SHT30_I2C     I2C2 
//-----------------SHT30 IIC端口定义----------------
#define SHT30_SCL_PIN                 GPIOD6
#define SHT30_SCL_PIN_AF              GPIOD6_AF_I2C2_SCL
#define SHT30_SDA_PIN                 GPIOD7
#define SHT30_SDA_PIN_AF              GPIOD7_AF_I2C2_SDA

/* ADDR Pin Conect to VSS */
#define    SHT30_SLAVE_ADDRESS      (0x44<<1)
#define    SHT30_ADDR_WRITE         (0x44<<1)         
#define    SHT30_ADDR_READ          (0x44<<1)+1     


void SHT30_Init(void);
void SHT30_Read_Result(uint8_t *sht30_data,float *getTempHum);


uint8_t SHT30_Reset(I2C_HandleTypeDef I2C_Handle);
static uint8_t    SHT30_Send_Cmd(SHT30_CMD cmd);
//uint8_t SHT30_Read_Dat(uint8_t* dat);
uint8_t SHT30_Read_Dat(I2C_HandleTypeDef I2C_Handle,uint8_t* dat);
uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value);
uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float* temperature, float* humidity);


//void sht30_read_temp_humi(uint8_t *p);
//int  crc8_compute(uint8_t *check_data, uint8_t num_of_data);
//int sht30_crc8_check(uint8_t *p,uint8_t num_of_data,uint8_t CrcData);
//int sht30_data_process(void);



#endif




