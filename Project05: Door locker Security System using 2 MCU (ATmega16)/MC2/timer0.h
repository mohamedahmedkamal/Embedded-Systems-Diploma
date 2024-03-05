/************************************************************************************************
 *
 * Module     : TIMER0
 *
 * File name  : timer0.h
 *
 * Description: Header file for TIMER0 driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	Normal,PWM,CTC,FastPWM
}Timer_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_FALLING,EXTERNAL_RISING
}Timer_Prescaler;

typedef struct
{
	Timer_Prescaler Prescale;
	Timer_Mode mode;
	uint8 Timer_Compare_value;
	uint8 Timer_init_value;
}Timer_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer_Init(const Timer_ConfigType * Config_Ptr);

void Timer_setCallBack(void(*a_ptr)(void));

void Timer_DeInit(void);

#endif /* TIMER0_H_ */
