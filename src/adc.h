/************************* Description ******************************
* File Name			: adc.h
* Author			:
* Version			: V0.0.1
* Date				: 18/05/2015
* Description		: DMA operation
********************************************************************/

#ifndef ADC_H_
#define ADC_H_

// includes
#include "stm32f4xx.h"
#include "main.h"

//define
#define _ADC1_Size 									3										// Liczba konwersji

#define _ADC_Calibr_Divider_12bit					0.0007213134765625							// Wartosc przepelnienia przetwornika ( Vmax / 4096 ) 12 bitowego (zmierzone->) 2.9545 / 4096 = 0.0007213134765625

// initialization
void ADC_Conf(void);

#endif /* ADC_H_ */
