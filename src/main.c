/***************************** Description **************************
* File Name			: main.c
* Author			: Author
* Version			: V0.0.0
* Date				: 27/04/2015
* Description		: Main operation
********************************************************************/

// includes
#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "tim.h"

u8 licznik;

int main(void)
{
	RCC_Conf();
	GPIO_Conf();
	NVIC_Conf();
	//SysTick_Conf();
	TIM_Conf();
	DMA_Conf();
	ADC_Conf();
	TM_USB_VCP_Init();


	u8 c;

  while(1)
  {
	  if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED)
	  {
		  /* Turn on GREEN led */
		  GPIO_SetBits(_Diode_GPIO, _Diode_1);
		  /* If something arrived at VCP */
		  if (TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK) {
			  /* Return data back */
			  TM_USB_VCP_Putc(c);
		  }
	  }else
	  {
		  GPIO_ResetBits(_Diode_GPIO, _Diode_1);
	  }
  }
}

