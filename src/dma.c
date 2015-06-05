/************************* Description ******************************
* File Name			: dma.c
* Author			:
* Version			: V0.0.1
* Date				: 18/05/2015
* Description		: DMA operation
********************************************************************/

// includes
#include "dma.h"
#include "main.h"

// global variables
vu16 ADCVal[_ADC1_Size] = {0};

// declarations system
DMA_InitTypeDef DMA_InitStruct;


/*************************** DMA_Conf ******************************
* Function Name		: DMA_Conf
* Description		: Configuration of DMA,
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void DMA_Conf(void)
{
	////////////// DMA_ADC1 //////////////
	DMA_DeInit(DMA2_Stream0);													// Deinicjalizacja
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;									// Wybor kanalu
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)ADC_CDR_ADDRESS;			// Adres peryferium
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADCVal;						// Adres w pamieci
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;						// Kierunek przesylania danych peryferium->pamieci
	DMA_InitStruct.DMA_BufferSize = _ADC1_Size;									// Rozmiar bufora
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				// Inkrementacja peryferium wylaczona
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;						// Inkrementacja pamieci wlaczona
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// Rozmiar paczki danych w paryferium - bajt
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			// Rozmiar paczki danych w pamiêci - bajt
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;								// Tryb cykliczny
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;							// Priorytet wysoki
	DMA_Init(_DMA_ADC, &DMA_InitStruct);										// Inicjalizacja

	DMA_ITConfig(_DMA_ADC, DMA_IT_TC, ENABLE);									// Wlaczenie przerwania od Transfer Complete
	DMA_Cmd(_DMA_ADC, ENABLE);													// Wlaczenie przerwan
}
