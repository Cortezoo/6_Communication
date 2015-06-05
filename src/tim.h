/************************* Description ******************************
* File Name			: tim.h
* Author			:
* Version			: V0.0.1
* Date				: 11/05/2015
* Description		: Timer operation
********************************************************************/

#ifndef TIM_H_
#define TIM_H_

// includes
#include "stm32f4xx.h"
#include "main.h"

// defines
#define s			12949343
#define ms			12949.343
#define us			12.94934

// TIM3 - main timer
#define _TIM3_Scal			167						// prescaler: 84000000/(83+1) = 1MHz
#define _TIM3_Period		49999 					// period: 1MHz/(9999+1) = 100Hz, 10ms

// TIM8 - PWM
#define _TIM8_Scal			6						// prescaler: 168MHz/(6+1) = 24MHz
#define _TIM8_Period		59999 					// period: 24MHz/(59999+1) = 400Hz, 2.5ms

// declarations
void TIM_Conf(void);
void SysTick_Conf(void);
void Delay(u32 delay, float state);

#endif /* TIM_H_ */
