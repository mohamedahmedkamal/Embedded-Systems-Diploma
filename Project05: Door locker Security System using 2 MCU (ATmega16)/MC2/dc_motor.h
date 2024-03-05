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
#include "std_types.h"
/*************************************************************************************************
                                            Definitions
 *************************************************************************************************/

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
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input.
*/
void DcMotor_OFF(void);
void DcMotor_Rotate_CW(void);
void DcMotor_Rotate_ACW(void);


#endif /* DC_MOTOR_H_ */
