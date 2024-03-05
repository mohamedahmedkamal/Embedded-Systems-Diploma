/************************************************************************************************
 *
 * Module     : BUZZER
 *
 * File name  : buzzer.c
 *
 * Description: Source file for BUZZER driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#include"gpio.h"
#include "buzzer.h"
#include"std_types.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Buzzer_Init(void){

	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID,PIN_OUTPUT);

}
void Buzzer_ON(void){

	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_HIGH);

}

void Buzzer_OFF(void){

	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID,LOGIC_LOW);

}
