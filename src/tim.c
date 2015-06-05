/************************* Description ******************************
* File Name			: tim.c
* Author			:
* Version			: V0.0.1
* Date				: 11/05/2015
* Description		: Timer operation
********************************************************************/

// includes
#include "tim.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "gpio.h"

// definitions
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;

/**************************** TIM_Conf ******************************
* Function Name  : TIM_Conf
* Description    : Timers configuration
* Input          : None
* Output         : None
* Return         : None
********************************************************************/
void TIM_Conf(void)
{
/******************************************************
 ****************** TIM3 - main timer *****************
 ******************************************************/
	// konfiguracja TIM3 - okres pomiarów
	TIM_TimeBaseInitStructure.TIM_Period = _TIM3_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM3_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE);

/******************************************************
 ***************** konfiguracja TIM8 ******************
 ******************************************************/
	TIM_TimeBaseInitStructure.TIM_Period = _TIM8_Period;
	TIM_TimeBaseInitStructure.TIM_Prescaler = _TIM8_Scal;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);

	// konfiguracja CH1, CH2, CH3, CH4 w TIM8
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 30000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);

	TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM8, ENABLE);
}

/****************************** SysTick_Conf *******************************
* Function Name  : SysTick_Conf
* Description    : SysTick_Conf.
* Input          : None
* Output         : None
* Return         : None
********************************************************************/
void SysTick_Conf(void)
{
	//Zegar SysTick bedzie wynosil 168MHz
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);


	if(SysTick_Config(1680000))	//przerwanie co 1ms - 168MHz/1680000=100Hz => T=10ms
	{
		while(1);
	}

}

/****************************** Delay *******************************
* Function Name  : Delay
* Description    : Delay.
* Input          : delay - time delay
					state - unit
* Output         : None
* Return         : None
********************************************************************/
void Delay(u32 delay, float state)
{
	u32 TimeDelay =  delay * state;									// minimum time of 825ns at the state equal 0
    for(u32 TimeCount = 0; TimeCount < TimeDelay; TimeCount++);
}




