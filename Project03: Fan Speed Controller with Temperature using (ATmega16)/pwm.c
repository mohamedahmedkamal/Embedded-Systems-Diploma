/************************************************************************************************
 *
 * Module     : PWM
 *
 * File name  : PWM.h
 *
 * Description: Header file for DC_MOTOR driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#include <avr/io.h>
#include "pwm.h"

void PWM_Timer0_Init(uint8 duty_cycle)
{

	TCNT0 = 0; /* Set Timer Initial value*/

	switch(duty_cycle){
	case 25:
		OCR0  = 64; /* Set Compare Value */
		break;
	case 50:
		OCR0  = 128; /* Set Compare Value */
		break;
	case 75:
		OCR0  = 192; /* Set Compare Value */
		break;
	case 100:
		OCR0  = 255; /* Set Compare Value */
		break;
	}

	DDRB  = DDRB | (1<<PB3);  /* Set PB3/OC0 as output pin --> pin
	                          where the PWM signal is generated from MC.*/

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
