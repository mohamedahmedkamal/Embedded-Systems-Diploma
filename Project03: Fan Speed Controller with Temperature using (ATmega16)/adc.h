/************************************************************************************************
 *
 * Module     : ADC
 *
 * File name  : adc.h
 *
 * Description: Header file for ADC driver (for AVR Controller)
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#ifndef ADC_H_
#define ADC_H_
/*************************************************************************************************
                                            Includes
 *************************************************************************************************/
#include "std_types.h"
/*************************************************************************************************
                                   Definitions and Configurations
 *************************************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
/*************************************************************************************************
                                           ENUM & STRUCT
 *************************************************************************************************/
typedef enum{

	AREF,AVCC,Reserved,Internal

}ADC_ReferenceVolatge;

typedef enum{

	F_CPU_TWO,F_CPU_2,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128

}ADC_Prescaler;

typedef struct{

	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler ;

}ADC_ConfigType;


/************************************************************************************************
 *                                    Functions Prototypes                                   *
 ***********************************************************************************************/

void ADC_init(const ADC_ConfigType*config_Ptr);

uint16 ADC_readchannel(uint8 channel);

#endif /* ADC_H_ */
