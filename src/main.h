/************************* Description ******************************
* File Name			: main.h
* Author			: Author
* Version			: V0.0.0
* Date				: 27/04/2015
* Description		: Main operation
********************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

// includes
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "tm_stm32f4_usb_vcp.h"

// defines
#define _Output_Designator		0xFAFAFAFA
#define _Input_Designator		0xFBFBFBFB
#define _Closing				0x6F6F6F6F

// structure
typedef struct typ_TransferStructure
{
	u32 Pack_Designator;
	u32 Control_Register;
	float Voltage1;
	float Voltage2;
	float Temperature;
	u32 Pack_End;
}typ_TransferStructure;


// declarations

#endif /* MAIN_H_ */
