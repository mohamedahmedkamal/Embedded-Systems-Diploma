/************************************************************************************************
 *
 * Module     : DC_MOTOR
 *
 * File name  : dc_motor.c
 *
 * Description: Source file for DC_MOTOR driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "common_macros.h"
#include "pwm.h"


void DcMotor_Init(void){

	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);

	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	PWM_Timer0_Init(speed);

	if(state == OFF){

		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

	}
	else if(state == CW){

		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	}
	else
	{
		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);
	}



}
