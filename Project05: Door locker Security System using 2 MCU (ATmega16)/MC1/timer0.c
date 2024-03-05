/************************************************************************************************
 *
 * Module     : TIMER0
 *
 * File name  : timer0.c
 *
 * Description: Source file for TIMER0 driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
volatile uint16 tick = 0 ;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	tick++;

	if(tick == 458)
	{
		(*g_callBackPtr)();

	}
	else if(tick == 550){ //92+458

		(*g_callBackPtr)();
	}
	else if(tick == 1008){ //92+458+458
		(*g_callBackPtr)();
	}
	else if(tick == 1875){
		(*g_callBackPtr)();
		tick =0;
	}

}
ISR(TIMER0_COMP_vect)
{
	tick++;
		if(tick == 458)
		{
			(*g_callBackPtr)();

		}
		else if(tick == 550){ //92+458

			(*g_callBackPtr)();
		}
		else if(tick == 1008){ //92+458+458
			(*g_callBackPtr)();
		}
		else if(tick == 1875){
			(*g_callBackPtr)();

		}

}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer_Init(const Timer_ConfigType * Config_Ptr){

	TCNT0 = Config_Ptr->Timer_init_value;
	TCCR0 = (TCCR0 & 0x7F) | ~(((Config_Ptr->mode)&0x01)<<7);
	TCCR0 = (TCCR0 & 0xB7) | (((Config_Ptr->mode)&0x02)<<2) | (((Config_Ptr->mode)&0x01)<<6);
	TCCR0 = (TCCR0&0xF8) | (Config_Ptr->Prescale);
	OCR0  = Config_Ptr->Timer_Compare_value;
	TIMSK |= (1<<TOIE0); //ENABLE TIMER0 INTERRUPT


}

void Timer_DeInit(void){

	TCNT0=0;
	TCCR0=0;
	OCR0=0;
	TIMSK=0;
	tick=0;
}


void Timer_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
