/************************* Description ******************************
* File Name			: nvic.h
* Author			:
* Version			: V0.0.1
* Date				: 04/05/2015
* Description		: NVIC operation
********************************************************************/

// includes
#include "nvic.h"
#include "main.h"
#include "gpio.h"

// definitions
NVIC_InitTypeDef   NVIC_InitStructure;
EXTI_InitTypeDef   EXTI_InitStructure;

/**************************** NVIC_Conf ******************************
* Function Name  : NVIC_Conf
* Description    : Configurations of NVIC
* Input          : None
* Output         : None
* Return         : None
********************************************************************/
void NVIC_Conf(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

	// Wlaczenie EXTI
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

	// Wlacz przerwanie od DMA2_Stream0_IRQn		(ADC1)
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	// Wlaczenie przerwania od EXTI
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	// Wlaczenie przerwania od TIM3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	// Wlacz przerwanie od TIM8
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	NVIC_SetPriority(SysTick_IRQn, 0x0);

}
