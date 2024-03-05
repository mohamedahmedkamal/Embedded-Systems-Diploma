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



void DcMotor_Init(void){

	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);

	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
}



void DcMotor_OFF(void){


	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

}

void DcMotor_Rotate_CW(void){

	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
}

void DcMotor_Rotate_ACW(void){

	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);

}




