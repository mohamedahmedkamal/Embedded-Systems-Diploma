/************************************************************************************************
 *
 * Module     : ADC
 *
 * File name  : adc.c
 *
 * Description: Source file for ADC driver (for AVR Controller)
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#include"adc.h"
#include <avr/io.h>
#include "common_macros.h"

void ADC_init(const ADC_ConfigType*config_Ptr){

	ADMUX = 0;
	/*VREF SELECTION BITS by enter value in last two bits in ADMUX (REFS1,REFS0)*/
	ADMUX = (ADMUX & 0x3F)|((config_Ptr->ref_volt)<<6);

	/*ADC PRESCALER SELECT BITS by enter value in first three bits in ADCSRA (ADPS0,ADPS1,ADPS2)
	 *  (HERE DIVISON FACTOR = 8)*/
	ADCSRA = (ADCSRA & 0xF8)|(config_Ptr->prescaler);

	SET_BIT(ADCSRA,ADEN);  /*ENABLE ADC*/

}

uint16 ADC_readchannel(uint8 channel){

	    channel &= 0x07; /* Input channel number must be from 0 --> 7 */
		ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
		ADMUX = ADMUX | channel; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
		SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
		while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
		SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
		return ADC; /* Read the digital value from the data register */
}

