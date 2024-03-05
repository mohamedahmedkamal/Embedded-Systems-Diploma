/************************************************************************************************
 *
 * Module     : DC_MOTOR
 *
 * File name  : dc_motor.h
 *
 * Description: Header file for DC_MOTOR driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
/*************************************************************************************************
                                            Includes
 *************************************************************************************************/
#include "std_types.h"
/*************************************************************************************************
                                   Definitions and Configurations
 *************************************************************************************************/

/*************************************************************************************************
                                              ENUMS
 *************************************************************************************************/
typedef enum{
	OFF, CW, ACW
}DcMotor_State;  /*a data type used for DC_MOTOR state*/
/************************************************************************************************
 *                                    Functions Prototypes                                   *
 ***********************************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.*/

void DcMotor_Init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.*/

void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
