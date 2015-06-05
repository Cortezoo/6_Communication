/***************************** Description **************************
* File Name			: rcc.c
* Author			: Author
* Version			: V0.0.0
* Date				: 27/04/2015
* Description		: RCC operation
********************************************************************/

// includes
#include "rcc.h"
#include "main.h"

/**************************** RCC_Conf ******************************
* Function Name  : RCC_Conf
* Description    : None
* Input          : None
* Output         : None
* Return         : None
********************************************************************/
void RCC_Conf(void)
{
	// AHB1
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);		//w³¹czanie takowania GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	// AHB2

	// APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// APB2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}
