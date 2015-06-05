/***************************** Description **************************
* File Name			: gpio.c
* Author			: Author
* Version			: V0.0.0
* Date				: 27/04/2015
* Description		: GPIO operation
********************************************************************/

// includes
#include "gpio.h"

// definitions
GPIO_InitTypeDef  GPIO_InitStructure;

/**************************** GPIO_Conf ******************************
* Function Name  : GPIO_Conf
* Description    : Configuration of GPIO
* Input          : None
* Output         : None
* Return         : None
********************************************************************/
void GPIO_Conf(void)
{

/*********************************************************
 ******************** Kanfiguracja Diod ******************
 *********************************************************/
	// configure Diodes
	GPIO_InitStructure.GPIO_Pin = _Diode_1 | _Diode_2 | _Diode_3 | _Diode_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_Diode_GPIO, &GPIO_InitStructure);

	// wejscia analogowe
	GPIO_InitStructure.GPIO_Pin =  _ADC1_IN14 |  _ADC1_IN15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(_ADC1_GPIO, &GPIO_InitStructure);

	// konfiguracja wywietlacza 7-seg
	GPIO_InitStructure.GPIO_Pin = _seg_a | _seg_b | _seg_c | _seg_d | _seg_e | _seg_f | _seg_g | _seg_dp;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_7seg_GPIO, &GPIO_InitStructure);

	// konfiguracja wywietlacza 4511
	GPIO_InitStructure.GPIO_Pin = out_A | out_B | out_C | out_D;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(out_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = _Button;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(_Button_GPIO, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	// configure PWM TIM8
	GPIO_InitStructure.GPIO_Pin = _PWM_1 | _PWM_2 | _PWM_3 | _PWM_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(_PWM_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(_PWM_GPIO, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_PinAFConfig(_PWM_GPIO, GPIO_PinSource7, GPIO_AF_TIM8);
	GPIO_PinAFConfig(_PWM_GPIO, GPIO_PinSource8, GPIO_AF_TIM8);
	GPIO_PinAFConfig(_PWM_GPIO, GPIO_PinSource9, GPIO_AF_TIM8);

}

void DisplayNumber7seg(u8 number, u8 dot)
{
	u16 port;
	if(number == 0)
	{
		port = _seg_a | _seg_b | _seg_c | _seg_d | _seg_e | _seg_f;
	}else if(number == 1)
	{
		port = _seg_b | _seg_c;
	}else if(number == 2)
	{
		port = _seg_a | _seg_b | _seg_g | _seg_e | _seg_d;
	}else if(number == 3)
	{
		port = _seg_a | _seg_b | _seg_g | _seg_c | _seg_d;
	}else if(number == 4)
	{
		port = _seg_f | _seg_g | _seg_b | _seg_c;
	}else if(number == 5)
	{
		port = _seg_a | _seg_f | _seg_g | _seg_c | _seg_d;
	}else if(number == 6)
	{
		port = _seg_a | _seg_f | _seg_e | _seg_d | _seg_c | _seg_g;
	}else if(number == 7)
	{
		port = _seg_a | _seg_b | _seg_c;
	}else if(number == 8)
	{
		port = _seg_a | _seg_b | _seg_c | _seg_d | _seg_e | _seg_f | _seg_g;
	}else if(number == 9)
	{
		port = _seg_a | _seg_b | _seg_c | _seg_d | _seg_f | _seg_g;
	}

	if(dot)port = port | _seg_dp;

	GPIO_ResetBits(_7seg_GPIO, _seg_a | _seg_b | _seg_c | _seg_d | _seg_e | _seg_f | _seg_g);GPIO_SetBits(_7seg_GPIO, port);
}
