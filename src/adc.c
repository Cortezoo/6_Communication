/************************* Description ******************************
* File Name			: adc.c
* Author			: Przemyslaw Gasior
* Version			: V1.0.0
* Date				: 03/07/2014
* Description		: ADC operation
********************************************************************/

// includes
#include "adc.h"
#include "gpio.h"

// declarations system
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

/*************************** ADC_Conf ******************************
* Function Name		: ADC_Conf
* Description		: Configuration of ADC,
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void ADC_Conf(void)
{
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;							// Niezalezny przetwornik
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;						// Ustawienie preskalera
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;					// Wlaczenie DMA
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;		// Ustawienie probkowania
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;								// Rozdzielczosc 12-bitowa
	ADC_InitStruct.ADC_ScanConvMode = ENABLE;										// Wlaczenie opcji skanowania
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;								// Wylaczenie pomiarow w trybie ciaglym
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;		// Nie bedzie wyzwalania zewnetrznego
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;								// Dane wyrownane do prawej - znaczacych bedzie 12 mlodszych bitow
	ADC_InitStruct.ADC_NbrOfConversion = _ADC1_Size;								// Liczba konwersji
	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_14 , 1, ADC_SampleTime_112Cycles);	// Uruchomienie kanalow do przetwarzania
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15 , 2, ADC_SampleTime_112Cycles);	// Uruchomienie kanalow do przetwarzania
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16 , 3, ADC_SampleTime_480Cycles);	// Uruchomienie kanalow do przetwarzania

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);								// DMA po kazdym pomiarze

	ADC_TempSensorVrefintCmd(ENABLE);												// Wlaczenie czujnika temperatury

	ADC_DMACmd(ADC1, ENABLE);														// Wlaczenie DMA

	ADC_Cmd(ADC1, ENABLE);															// Wlacz ADC1
}
