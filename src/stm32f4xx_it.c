/************************* Description ******************************
* File Name			: stm32f4xx_it.c
* Author			: Author
* Version			: V0.0.0
* Date				: 27/04/2015
* Description		: Interrupt hendlers
********************************************************************/

// includes
#include "stm32f4xx_it.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include "dma.h"

typ_TransferStructure TransStruct;

extern u8 licznik;
extern vu16 ADCVal[_ADC1_Size];

char komunikat[20];

u8 wypelnienie = 0;

float voltage1, voltage2, temp;

char buf[sizeof(typ_TransferStructure)];

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{

}

/******************************************************************************
*                 STM32F4xx Peripherals Interrupt Handlers
*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the
*  available peripheral interrupt handler's name please refer to the startup
*  file (startup_stm32f4xx.s).
******************************************************************************/

/*********************** TIM3_IRQHandler ****************************
* Function Name		: TIM3_IRQHandler
* Description		: None
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		static u16 Diode1_Counter = 0;
		if((Diode1_Counter++)%10 == 0)										// Miganie dioda co 100 razy
		{
			GPIO_ToggleBits(_Diode_GPIO, _Diode_2);
		}
		ADC_SoftwareStartConv(ADC1);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

/******************* DMA2_Stream0_IRQHandler ************************
* Function Name		: DMA2_Stream0_IRQHandler
* Description		: None
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus(_DMA_ADC, DMA_IT_TCIF0) != RESET)
	{
		voltage1 = ADCVal[0] * _ADC_Calibr_Divider_12bit;
		voltage2 = ADCVal[1] * _ADC_Calibr_Divider_12bit;
		temp = (ADCVal[2]*_ADC_Calibr_Divider_12bit*1000 - 760)/2.5 + 25;		// odczyt * (Vmax / 4096) * (3.3 / 2.5)

		TransStruct.Pack_Designator = _Designator;
		TransStruct.Voltage1 = voltage1;
		TransStruct.Voltage2 = voltage2;
		TransStruct.Temperature = temp;
		TransStruct.Pack_End = _Closing;

		memcpy(buf, &TransStruct, sizeof(typ_TransferStructure));

		TM_USB_VCP_Puts(buf);

		DMA_ClearFlag(_DMA_ADC, DMA_FLAG_TCIF0);												// czyszczenie flagi
	}
}

/*************************** EXTI0_IRQHandler **********************
* Function Name		: EXTI0_IRQHandler
* Description		: None
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		//sprintf(komunikat, "%0.3f - %0.3f - %0.2f\n", voltage1, voltage2, temp);
		//TM_USB_VCP_Puts(buf);
		GPIO_ToggleBits(_Diode_GPIO, _Diode_4);
		wypelnienie+=10;
		if(wypelnienie>100)wypelnienie=0;
		Delay(200,ms);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}


/*********************** TIM8_UP_TIM13_IRQHandler ******************
* Function Name		: TIM8_UP_TIM13_IRQHandler
* Description		: None
* Input				: None
* Output			: None
* Return			: None
********************************************************************/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)
	{
		TIM_SetCompare1(TIM8, wypelnienie*599.99);
		TIM_SetCompare2(TIM8, wypelnienie*599.99);
		TIM_SetCompare3(TIM8, wypelnienie*599.99);
		TIM_SetCompare4(TIM8, wypelnienie*599.99);
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
	}
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
