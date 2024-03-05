/************************************************************************************************
 *
 * Module     : BUZZER
 *
 * File name  : buzzer.h
 *
 * Description: Header file for BUZZER driver
 *
 * Author     : Mohamed Ahmed Kamal
 *
 ************************************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID                   PORTC_ID
#define BUZZER_PIN_ID                    PIN2_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*Description
 * set pin connected to buzzer (pin name , direction output)
 * */
void Buzzer_Init(void);

/*Description
 * make buzzer on (put logic high on buzzer pin)
 * */
void Buzzer_ON(void);

/*Description
 * make buzzer off (put logic low on buzzer pin)
 * */
void Buzzer_OFF(void);


#endif /* BUZZER_H_ */
