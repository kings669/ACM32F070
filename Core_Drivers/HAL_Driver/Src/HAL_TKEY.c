/*
  ******************************************************************************
  * @file    HAL_TKEY.c
  * @version V1.0.2
  * @date    2021
  * @brief   TKEY module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the TKEY peripheral:
  *           @ Initialization and de-initialization functions
  *           @ IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

__IO uint32_t u32Regbackup;

extern volatile uint32_t gu32_SystemCount;



/************************************************************************
 * function   : TKEY_IRQHandler
 * Description: tkey interrupt service routine. 
 * input : 
 *         none
 * return: none
 ************************************************************************/
void TKEY_IRQHandler(void)
{
    TKEY->ISR = 0xFFF;
}

/************************************************************************
 * function   : HAL_TKEY_MspInit
 * Description: Init the hardware, GPIO and clock, etc.
 * input      : htkey : TKEY handle
 * return     : none
 ************************************************************************/
void HAL_TKEY_MspInit(TKEY_HandleTypeDef* htkey)
{
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 
    uint8_t ucI;
    
    /* TKEY GPIO inition*/
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /*TKEY0-3 -> PA10-13*/
        if(htkey->ChannelData[ucI].ChannelId < 4)             
        {            
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 10));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_Handle);             
        }
        /*TKEY4-5 -> PD6-7*/
        else if((htkey->ChannelData[ucI].ChannelId >= 4)&&(htkey->ChannelData[ucI].ChannelId <= 5))          
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 2));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOD, &GPIO_Handle);             
        }
         /*TKEY6-7 -> PA14-15*/
        else if((htkey->ChannelData[ucI].ChannelId >= 6)&&(htkey->ChannelData[ucI].ChannelId <= 7))         
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 8));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_Handle);             
        }
        /*TKEY8-10 -> PC10-12*/
        else if((htkey->ChannelData[ucI].ChannelId >= 8)&&(htkey->ChannelData[ucI].ChannelId <= 10))          
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId + 2));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOC, &GPIO_Handle);             
        }
        /*TKEY11 -> PD2*/
        else if(htkey->ChannelData[ucI].ChannelId == 11)          
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId - 9));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOD, &GPIO_Handle);             
        }
        /*TKEY12-15 -> PB3-6*/
        else if((htkey->ChannelData[ucI].ChannelId >= 12)&&(htkey->ChannelData[ucI].ChannelId <= 15))          
        {
            GPIO_Handle.Pin            = (uint16_t)(0x0001 << (htkey->ChannelData[ucI].ChannelId - 9));
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOB, &GPIO_Handle);             
        }
    }
    /*TKEY_SHIELD -> PB7*/
    if(htkey->Init.ShieldEn == TKEY_CR_SCAN_ENABLE)  
    {
        GPIO_Handle.Pin            = GPIO_PIN_7;
        GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
        GPIO_Handle.Pull           = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_Handle);             
    }
    
    /*Set the Cs(PB9) and Creg(PB8) pin to analog*/    
    GPIO_Handle.Pin            = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
    GPIO_Handle.Pull           = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_Handle);             

#ifdef TKEY_SCAN_CLK_RC4M
    SCU->RCHCR |= ((15 << 17) | SCU_RCHCR_RC4M_EN); //RC4M TRIM and Enable.
    while((SCU->RCHCR & SCU_RCHCR_RC4MRDY) == 0x00);
    SCU->CCR2 |= SCU_CCR2_TKSCLK_SEL;  //TKEY use the RC4M as clock.
#endif

    System_Enable_RC32K(); //RC32K Enable.
    
    System_Module_Reset(RST_TKEY); 
    
    /* Enable TKEY Clock */
    System_Module_Enable(EN_TKEY);
    
    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);
}

/************************************************************************
 * function   : HAL_TKEY_Start
 * Description: TKEY start to scan
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Start(TKEY_HandleTypeDef* htkey)
{
    /*Enable the Tkey scan*/
    SET_BIT(TKEY->CR , TKEY_CR_SCAN); 
    
    /*Start the Tkey scan*/    
    SET_BIT(TKEY->CR, TKEY_CR_START); 

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Stop
 * Description: TKEY stop the scan
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Stop(TKEY_HandleTypeDef* htkey)
{
    /*Check if the Tkey scan is busy*/
    while(READ_BIT(TKEY->ISR , TKEY_ISR_BUSY)){}
    
    /*disable the Tkey scan*/
    CLEAR_BIT(TKEY->CR, TKEY_CR_SCAN); 
    
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Suspend
 * Description: Set the sleep parameters. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Suspend(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    __IO uint32_t *gu32RegTemp;

    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);

    u32Regbackup = TKEY->SMPR;
    
        
    SET_BIT(TKEY->CR, TKEY_CR_SLEEP);      //Enable the wakeup.
    
    SET_BIT(TKEY->IER, TKEY_IER_WAKEUPIE); //Enable the wakeup interrupt.

    gu32RegTemp = &TKEY->CH0;
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        MODIFY_REG(TKEY->SMPR, TKEY_SMPR_SWT_MASK, TKEY_SMPR_SWT(TKEY_SLEEP_SCAN_SPEED));   //Slow down the scan speed. 
        /* Write the base data and the wakeup threshold.*/
        *(gu32RegTemp + htkey->ChannelData[ucI].ChannelId) = htkey->ChannelData[ucI].Tkey_Data->BaseLine;//htkey->ChannelData[ucI].Tkey_Data->RawData;
        *(gu32RegTemp - 16 + htkey->ChannelData[ucI].ChannelId) = htkey->ChannelData[ucI].Tkey_RefPara->WakeUpTh;
    }

    /* Enable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_EnableIRQ(TKEY_IRQn);
    
    /*Start the Tkey scan*/    
    SET_BIT(TKEY->CR, TKEY_CR_START); 
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_Resume
 * Description: Resume the wakeup parameters. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Resume(TKEY_HandleTypeDef* htkey)
{    
    /* Disable TKEY Interrupt */
    NVIC_ClearPendingIRQ(TKEY_IRQn);
    NVIC_DisableIRQ(TKEY_IRQn);
    
    CLEAR_BIT(TKEY->IER, TKEY_IER_WAKEUPIE); //Disable the wakeup interrupt.
    
    TKEY->SMPR = u32Regbackup;     //Use the backup scan value.
    CLEAR_BIT(TKEY->CR, TKEY_CR_SLEEP);      //Disable the wakeup.
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_ReadNr
 * Description: Read the count number of the Cr. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadNr(TKEY_HandleTypeDef* htkey)
{
    HAL_StatusTypeDef Status = HAL_OK;

    /*Check if the Tkey scan is busy*/
    while(READ_BIT(TKEY->ISR , TKEY_ISR_BUSY)){}
        
    /*Set the CREN, enabel the internal channel scan*/
    SET_BIT(TKEY->CR, TKEY_CR_CREN);
    
    /*Clear the SLEEP, use normal scan mode*/
    CLEAR_BIT(TKEY->CR, TKEY_CR_SLEEP);
            
    /* Clear all flag */
    TKEY->ISR = 0x07;
    HAL_TKEY_Start(htkey);
        
    while(!READ_BIT(TKEY->ISR, TKEY_ISR_EOC))
    {
        if(!READ_BIT(TKEY->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart. 
            SET_BIT(TKEY->CR, TKEY_CR_START); 
        
        if(READ_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
            Status = HAL_ERROR;
            break;
        }
    }
    
    TKEY->ISR = TKEY_ISR_EOC;
        
    return Status;
}

/************************************************************************
 * function   : HAL_TKEY_ReadChannelData
 * Description: Read the count number of the all channels. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadChannelData(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    __IO uint32_t *gu32RegTemp;
    
    TKEY->ISR = 0x07;
    if(!(TKEY->CR & TKEY_CR_CONT))
    {
        /*Start the Tkey scan*/    
        SET_BIT(TKEY->CR, TKEY_CR_START); 
    }
    while(!READ_BIT(TKEY->ISR, TKEY_ISR_EOC))
    {
        if(!READ_BIT(TKEY->ISR, TKEY_ISR_BUSY)) //Some times will stop.restart. 
            SET_BIT(TKEY->CR, TKEY_CR_START); 
        
        if(READ_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT))
        {
            SET_BIT(TKEY->ISR, TKEY_ISR_TIMEOUT); //Clear the timeout flag
            return HAL_ERROR;
        }
    }
    TKEY->ISR = TKEY_ISR_EOC;

    gu32RegTemp = &TKEY->CH0;
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* Read the data and calculate the delta.*/
        htkey->ChannelData[ucI].Tkey_Data->RawData = *(gu32RegTemp + htkey->ChannelData[ucI].ChannelId);
        htkey->ChannelData[ucI].Tkey_Data->Delta = (INT32)htkey->ChannelData[ucI].Tkey_Data->BaseLine - (INT32)htkey->ChannelData[ucI].Tkey_Data->RawData;
    }
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_ReadAllNx
 * Description: Read the count number of the all channels first time, and start the scan. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_ReadAllNx(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
        
    /*Clear the CREN, disable the internal channel scan*/
    CLEAR_BIT(TKEY->CR, TKEY_CR_CREN);
    
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /*Enable the channels*/
        TKEY->CXSELR |= (1<<htkey->ChannelData[ucI].ChannelId);
        /*If the channel need compensation*/
        if(TKEY_CR_CREN_SELECT)
        {       
            TKEY->CRSELR |= (1<<htkey->ChannelData[ucI].ChannelId);
        }
   
    }
    /*Clear the SLEEP, use normal scan mode*/
    CLEAR_BIT(TKEY->CR, TKEY_CR_SLEEP);
                
    HAL_TKEY_Start(htkey);
        
    HAL_TKEY_ReadChannelData(htkey); 
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_StartUpStateProcess
 * Description: Init the TKEY channel data. 
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_StartUpStateProcess(const TKEY_ChannelDataDef *ChannelData)
{
    ChannelData->Tkey_Data->DebIn = TKEY_DEBIN;
    ChannelData->Tkey_Data->DebOut = TKEY_DEBOUT;
    ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
}

/************************************************************************
 * function   : HAL_TKEY_DebDetectStateProcess
 * Description: The TKEY detect action state process. 
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_DebDetectStateProcess(const TKEY_ChannelDataDef *ChannelData)
{  
    if (ChannelData->Tkey_Data->Delta >= ChannelData->Tkey_RefPara->DetectInTH)
    {
        if (ChannelData->Tkey_Data->DebIn > 0) 
        {
            ChannelData->Tkey_Data->DebIn--;
        }
        if (ChannelData->Tkey_Data->DebIn == 0)
        {
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECT; 
            ChannelData->Tkey_Data->DebOut = TKEY_DEBOUT;
        }
      // else stay in Debounce Detect
    }
    else
    {
        ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
        ChannelData->Tkey_Data->DebIn = TKEY_DEBIN;
    }
}

/************************************************************************
 * function   : HAL_TKEY_DebReleaseDetectStateProcess
 * Description: The TKEY detect to release state process. 
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : None
 ************************************************************************/
void HAL_TKEY_DebReleaseDetectStateProcess(const TKEY_ChannelDataDef *ChannelData)
{    
    if (ChannelData->Tkey_Data->Delta >= ChannelData->Tkey_Data->DetectOutTH)
    {
        ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECTING;
        ChannelData->Tkey_Data->DebOut = TKEY_DEBOUT;
    }
    else
    {
        if (ChannelData->Tkey_Data->DebOut > 0)
        {
            ChannelData->Tkey_Data->DebOut--;
        }
        if (ChannelData->Tkey_Data->DebOut == 0)
        {
            ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
            ChannelData->Tkey_Data->DebIn = TKEY_DEBIN;
        }
    }
}

/************************************************************************
 * function   : HAL_TKEY_Calculate_Calibrate_Th
 * Description: Calculate Calibrate Threshold. 
 * input      : ChannelData : TKEY channel data handle point to TKEY_ChannelDataDef.
 * return     : none
 ************************************************************************/
void HAL_TKEY_Calculate_Calibrate_Th(const TKEY_ChannelDataDef *ChannelData)
{
    uint8_t ratio;
    uint16_t result;
    uint16_t  data = ChannelData->Tkey_RefPara->DetectInTH;
    if(data < 25)//<13
    {
        ratio = TKEY_CALIBRATE_RATIO3;
    }
    else if((data >= 25) && (data < 40))//10-14
    {
        ratio = TKEY_CALIBRATE_RATIO2;
    }
    else //>10
    {
        ratio = TKEY_CALIBRATE_RATIO1;
    }


    result = data * ratio / 100;

    if(result < TKEY_CALIBRATE_THMIN)
    {
        result = TKEY_CALIBRATE_THMIN;
    }
    else if(result > TKEY_CALIBRATE_THMAX)
    {
        result = TKEY_CALIBRATE_THMAX;
    }
    ChannelData->Tkey_Data->CalibratTH = result;  
}

/************************************************************************
 * function   : HAL_TKEY_Init
 * Description: Init the TKEY. 
 * input      : htkey : TKEY handle
 * return     : HAL_OK: success; HAL_ERROR: failed.
 ************************************************************************/
HAL_StatusTypeDef HAL_TKEY_Init(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    uint32_t u32RegTemp;
    
    /* Check the TKEY handle allocation */
    if (htkey == NULL)
    {
        return HAL_ERROR;
    }
    
    /* Check the parameters */
    if(!IS_TKEY_ALL_SCANWAITTIME(htkey->Init.ScanWaitTime)) return HAL_ERROR;
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC, DMA */
    HAL_TKEY_MspInit(htkey);
         
    /*Check if the Tkey scan is busy*/
    while(READ_BIT(TKEY->ISR , TKEY_ISR_BUSY)){}
    
    HAL_TKEY_Stop(htkey);
    
    /*Config the Tkey control register*/    
    u32RegTemp =  ((TKEY_CR_CHARGESEL_LDO << 11)& TKEY_CR_CHARGESEL)            | \
                  (TKEY_CR_VKEYSEL(TKEY_CR_VKEY_SELECT) & TKEY_CR_VKEYSEL_MASK) | \
                  (TKEY_CR_VREFSEL(TKEY_CR_VREF_SELECT) & TKEY_CR_VREFSEL_MASK) | \
                  ((TKEY_CR_CONT_ENABLE << 4)& TKEY_CR_CONT)                    | \
                  ((htkey->Init.ShieldEn << 3)& TKEY_CR_SHIELDEN);  
                  
    if(TKEY_CR_SPREAD_SELECT)
    {
        u32RegTemp |= ((TKEY_CR_SPREAD_SELECT << 5)& TKEY_CR_SPREAD) | (TKEY_CR_RANDM(TKEY_CR_RANDM_SELECT));
    }               
    
    WRITE_REG(TKEY->CR,u32RegTemp);
    
     /*Config the Tkey TKEY_SMPR register*/
    u32RegTemp = (TKEY_SMPR_SWT(htkey->Init.ScanWaitTime) & TKEY_SMPR_SWT_MASK) | \
                 (TKEY_SMPR_CST(TKEY_CSDISCHARGETIME) & TKEY_SMPR_CST_MASK);

    WRITE_REG(TKEY->SMPR,u32RegTemp);
    
     /*Config the Tkey TKEY_SOFR register*/
    u32RegTemp = (TKEY_SOFR_SW1H(TKEY_SW1H) & TKEY_SOFR_SW1H_MASK) | \
                 (TKEY_SOFR_SW1L(TKEY_SW1L) & TKEY_SOFR_SW1L_MASK);

    WRITE_REG(TKEY->SOFR,u32RegTemp);
    
    HAL_TKEY_ReadNr(htkey);
    
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* if need calibrate , read the data to the reference data.*/
        htkey->ChannelData[ucI].Tkey_Data->StateId = TKEY_STATEID_RELEASE;//TKEY_STATEID_STARTUP;
        htkey->ChannelData[ucI].Tkey_Data->DetectOutTH =  htkey->ChannelData[ucI].Tkey_RefPara->DetectInTH * TKEY_RELAESE_THRATIO / 100;
        HAL_TKEY_Calculate_Calibrate_Th(&htkey->ChannelData[ucI]);
    }
    
    HAL_TKEY_ReadAllNx(htkey);
    /* Clear all keys*/
    htkey->PressRelaeseFlag  = 0;
    htkey->ChannelDetectedNum  = 0;
    htkey->LongPressFlag = 0;
    htkey->DetectingFlag = 0;
    return  HAL_OK;
}

/************************************************************************
 * function   : HAL_TKEY_DetectProcess
 * Description: TKEY detect main process. 
 * input      : htkey : TKEY handle
 * return     : None.
 ************************************************************************/
void HAL_TKEY_DetectProcess(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    const TKEY_ChannelDataDef *ChannelData;
    
    HAL_TKEY_ReadChannelData(htkey); 
    
    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        ChannelData = &htkey->ChannelData[ucI];
        switch(ChannelData->Tkey_Data->StateId)
        {
            case TKEY_STATEID_STARTUP :
                HAL_TKEY_StartUpStateProcess(ChannelData);
                break;
            case TKEY_STATEID_RELEASE :           
                HAL_TKEY_DebDetectStateProcess(ChannelData);
                break;
            case TKEY_STATEID_DETECT : 
                htkey->PressRelaeseFlag  |= (1 << ChannelData->ChannelId);
                htkey->ChannelValue = ChannelData->ChannelId;
                htkey->ChannelDetectedNum++;
                ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECTING;//????????????????????????????????
                
                HAL_TKEY_DebReleaseDetectStateProcess(ChannelData);
                break;
            case TKEY_STATEID_DETECTING : 
                HAL_TKEY_DebReleaseDetectStateProcess(ChannelData);
                break;                
            default :
                break;            
        }
    }
}



/************************************************************************
 * function   : HAL_TKEY_Quick_Calibrate_RefData
 * Description: TKEY quick calibrate the base Reference Data. 
 * input      : htkey : TKEY handle
                CalTimes: The calibrat times.
 * return     : None
 ************************************************************************/
void HAL_TKEY_Quick_Calibrate_RefData(TKEY_HandleTypeDef* htkey, uint8_t CalTimes)
{
    uint8_t ucI,ucJ;
    uint32_t sum[16];
    
    memset(sum,0,sizeof(sum));
    for(ucJ=0; ucJ < CalTimes; ucJ++)
    {
        HAL_TKEY_ReadChannelData(htkey); 
        for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
        {
            if(htkey->ChannelData[ucI].Tkey_Data->RawData)
            {
                sum[ucI] +=  htkey->ChannelData[ucI].Tkey_Data->RawData;
            }
            if(ucJ == (CalTimes-1))
            {
                htkey->ChannelData[ucI].Tkey_Data->BaseLine =  sum[ucI]/CalTimes;
            }
        }
    }    
}

/************************************************************************
 * function   : HAL_TKEY_Quick_Calibrate_RefData_OneChannel
 * Description: TKEY Quick Calibration Single Channel Basic Reference Data. 
 * input      : htkey : TKEY handle
                CalTimes: The calibrat times.
                ChannelId: the TKEY channel
 * return     : None
 ************************************************************************/
void HAL_TKEY_Quick_Calibrate_RefData_OneChannel(TKEY_HandleTypeDef* htkey, uint16_t ChannelId, uint8_t CalTimes)
{
    uint8_t ucI,ucJ;
    uint32_t sum[16];
    
    memset(sum,0,sizeof(sum));
 
    for(ucJ=0; ucJ < CalTimes; ucJ++)
    {
        HAL_TKEY_ReadChannelData(htkey); 
        for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
        {
            if(htkey->ChannelData[ucI].ChannelId == ChannelId)
            {
                if(htkey->ChannelData[ucI].Tkey_Data->RawData)
                {
                    sum[ucI] +=  htkey->ChannelData[ucI].Tkey_Data->RawData;
                }
                if(ucJ == (CalTimes-1))
                {
                    htkey->ChannelData[ucI].Tkey_Data->BaseLine =  sum[ucI]/CalTimes;
                }
            }

        }
    }    
}

/************************************************************************
 * function   : HAL_TKEY_ScanProcess
 * Description: TKEY Scan Result main process. 
 * input      : htkey : TKEY handle
 * return     : None.
 ************************************************************************/
void HAL_TKEY_ScanProcess(TKEY_HandleTypeDef* htkey)
{
    uint8_t ucI;
    int32_t Time_Differ = 0;
    uint16_t delat_per = 0, per_max = 0;


    TKEY_ChannelDataDef *ChannelData;
    __IO uint32_t *gu32RegTemp;

    gu32RegTemp = &TKEY->CH0;

    for(ucI = 0; htkey->ChannelData[ucI].ChannelId != 0xFFFF; ucI++)
    {
        /* Read the data and calculate the delta.*/
        htkey->ChannelData[ucI].Tkey_Data->RawData = *(gu32RegTemp + htkey->ChannelData[ucI].ChannelId);
        htkey->ChannelData[ucI].Tkey_Data->Delta = (INT32)htkey->ChannelData[ucI].Tkey_Data->BaseLine - (INT32)htkey->ChannelData[ucI].Tkey_Data->RawData;
        ChannelData = &htkey->ChannelData[ucI];
        switch(ChannelData->Tkey_Data->StateId)
        {
            case TKEY_STATEID_RELEASE : 
                htkey->PressRelaeseFlag &= ~(1 << ChannelData->ChannelId);
                htkey->LongPressFlag &= ~(1 << ChannelData->ChannelId);
                htkey->DetectingFlag &= ~(1 << ChannelData->ChannelId);//add by sam 20220617
                ChannelData->Tkey_CalData->DetectingTimer = 0;
                if(ChannelData->Tkey_Data->Delta > ChannelData->Tkey_RefPara->DetectInTH)
                {
                    if(ChannelData->Tkey_Data->Delta < ChannelData->Tkey_RefPara->DetectInTH * 5)
                    {
                        if (ChannelData->Tkey_Data->DebIn == 0)
                        {
                            if(htkey->DetectingFlag == 0)//add by sam 20220617
                            {
                                //????Differ(Delta)????????????DetectInTH??????????
                                delat_per = (ChannelData->Tkey_Data->Delta - ChannelData->Tkey_RefPara->DetectInTH)*100/ChannelData->Tkey_RefPara->DetectInTH;
                                //HAL_TKEY_DEBUG("TK_%d:{Delta=%d,DetectInTH=%d,delat_per=%d,per_max=%d}\r\n",ChannelData->ChannelId,ChannelData->Tkey_Data->Delta, ChannelData->Tkey_RefPara->DetectInTH,delat_per,per_max);
                                if(delat_per > per_max)//????????????????????TKey
                                {
                                    per_max = delat_per;                      
                                    htkey->PressRelaeseFlag = (1 << ChannelData->ChannelId);
                                    htkey->ChannelValue = ChannelData->ChannelId;
                                    htkey->ChannelDetectedNum = 1;
                                    ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECTING;
                                    ChannelData->Tkey_CalData->DetectingTimer = gu32_SystemCount;
                                    ChannelData->Tkey_Data->DebOut = TKEY_DEBOUT;                                  
                                }
                            } 
                            else if(htkey->DetectingFlag >> ChannelData->ChannelId)
                            {
                                // HAL_TKEY_DEBUG("The previous trigger key is after the current trigger key\r\n");
                                htkey->PressRelaeseFlag |= (1 << ChannelData->ChannelId);
                                htkey->ChannelValue = ChannelData->ChannelId;
                                htkey->ChannelDetectedNum = 1; 
                                ChannelData->Tkey_Data->StateId = TKEY_STATEID_DETECTING;
                                ChannelData->Tkey_CalData->DetectingTimer = gu32_SystemCount;
                                ChannelData->Tkey_Data->DebOut = TKEY_DEBOUT;  
                            }

                            ChannelData->Tkey_CalData->Caldata[ChannelData->Tkey_CalData->pos] = ChannelData->Tkey_Data->RawData;
                        } 
                        else
                        {
                            ChannelData->Tkey_Data->DebIn--;
                        }  
                    }                    
                }
                else
                {
                    ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
                    ChannelData->Tkey_Data->DebIn = TKEY_DEBIN;
                    if(ChannelData->Tkey_Data->Delta < (-ChannelData->Tkey_RefPara->DetectInTH))//baseline??rawdata??DetectInTH, Differ(Delta)??????????DetectInTH????????????????????
                    {
                        //HAL_TKEY_DEBUG("TK_%d:Delta=%d, rawdata=%d, baseline=%d\r\n",ChannelData->ChannelId,ChannelData->Tkey_Data->Delta,ChannelData->Tkey_Data->RawData,ChannelData->Tkey_Data->BaseLine);
                        ChannelData->Tkey_CalData->CalFlag = TKEY_CALIBRAT_QUICK;//need quick calibrate
                        //ChannelData->Tkey_Data->BaseLine =  ChannelData->Tkey_Data->RawData;                       
                    }
                    if(ChannelData->Tkey_CalData->ScanTimer++ >= TKEY_CALIBRATE_TIMES)
                    {
                        ChannelData->Tkey_CalData->ScanTimer = 0;
                        ChannelData->Tkey_CalData->Caldata[ChannelData->Tkey_CalData->pos++] = ChannelData->Tkey_Data->RawData;
                        if(ChannelData->Tkey_CalData->pos >= TKEY_CALIBRATE_BUFF_MAX)
                        {
                            ChannelData->Tkey_CalData->pos = 0;
                            ChannelData->Tkey_CalData->CalFlag = TKEY_CALIBRAT_SELF; //need self calibrate
                            
                        }
                    }
                }
                break;
 
            case TKEY_STATEID_DETECTING :
                htkey->DetectingFlag |= (1 << ChannelData->ChannelId);//add by sam 20220617
                if (ChannelData->Tkey_Data->Delta < ChannelData->Tkey_Data->DetectOutTH)
                {
                    if (ChannelData->Tkey_Data->DebOut == 0)
                    {
                        ChannelData->Tkey_Data->StateId = TKEY_STATEID_RELEASE;
                        ChannelData->Tkey_Data->DebIn = TKEY_DEBIN;
                        ChannelData->Tkey_CalData->DetectingTimer = 0;
                        //HAL_TKEY_DEBUG("TK_%d: Relaese, PressRelaeseFlag = 0x%04x,",ChannelData->ChannelId,htkey->PressRelaeseFlag);
                        htkey->PressRelaeseFlag &= ~(1 << ChannelData->ChannelId);
                        htkey->LongPressFlag &= ~(1 << ChannelData->ChannelId);
                        htkey->DetectingFlag &= ~(1 << ChannelData->ChannelId);
                        //HAL_TKEY_DEBUG("PressRelaeseFlag = 0x%04x\r\n",htkey->PressRelaeseFlag);
                    }                    
                    else
                    {
                        ChannelData->Tkey_Data->DebOut--;
                    }
                }
                else
                {
                    if(htkey->PressRelaeseFlag & (~htkey->DetectingFlag))
                    {                   
                        htkey->PressRelaeseFlag = htkey->DetectingFlag;
                        htkey->ChannelValue = 0;
                        htkey->ChannelDetectedNum = 0; 
                    }                    
                    Time_Differ = gu32_SystemCount - ChannelData->Tkey_CalData->DetectingTimer;
                    if(Time_Differ > TKEY_DETECTING_CALIBRATE_TIME)//??????????????????????????????????
                    {
                        //HAL_TKEY_DEBUG("TK_%d DetectingTimer = %d, Time_Differ = %dTKEY_CALIBRAT_QUICK\r\n",ChannelData->ChannelId,ChannelData->Tkey_CalData->DetectingTimer,Time_Differ);
                        ChannelData->Tkey_CalData->CalFlag = TKEY_CALIBRAT_QUICK;//need quick calibrate
                        ChannelData->Tkey_CalData->DetectingTimer = 0;
                    }
                    else if(Time_Differ > TKEY_LONG_DETECTING_TIME)
                    {
                        if((htkey->PressRelaeseFlag) & (1 << ChannelData->ChannelId))//add by sam 20220617
                        {
                            htkey->LongPressFlag |= (1 << ChannelData->ChannelId);
                        }
                    }
                }
                break;                
            default :
                break;            
        }
    }        
}
