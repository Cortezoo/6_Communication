/************************* Description ******************************
* File Name			: dma.h
* Author			:
* Version			: V0.0.1
* Date				: 18/05/2015
* Description		: DMA operation
********************************************************************/

#ifndef DMA_H_
#define DMA_H_

// includes
#include "stm32f4xx.h"
#include "main.h"
#include "adc.h"

// define
#define ADC1_DR_Address    		((uint32_t)0x4001204C)
#define ADC_CDR_ADDRESS    		((uint32_t)0x40012308)

#define _DMA_ADC 				DMA2_Stream0		//channel

// initialization
void DMA_Conf(void);

#endif /* DMA_H_ */
