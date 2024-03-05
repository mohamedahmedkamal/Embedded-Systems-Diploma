/************************************************************************************************
 *
 * Module     : PWM
 *
 * File name  : pwm.h
 *
 * Description: Header file for PWM driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#ifndef PWM_H_
#define PWM_H_
/*************************************************************************************************
                                            Includes
 *************************************************************************************************/
#include "std_types.h"
/************************************************************************************************
 *                                    Functions Prototypes                                   *
 ***********************************************************************************************/

/*Definition
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode with Non-Inverting.
 * Setup the PRESCALER with F_CPU/8.
 * Setup the compare value based on the required input duty cycle
 * Setup the direction for OC0 as output pin through the GPIO driver.
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 * */

void PWM_Timer0_Init(uint8 duty_cycle);

#endif /* PWM_H_ */
