/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed ahmed kamal
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	Disable,Even_Parity=2,Odd_Parity=3
}Parity_Mode;

typedef enum{
	BD_rate10=10, BD_rate300=00, BD_rate600=600, BD_rate1200=1200, BD_rate2400=2400,
	BD_rate4800=4800, BD_rate9600=9600, BD_rate14400=14400, BD_rate19200=19200,
	BD_rate38400=38400, BD_rate57600=57600, BD_rate115200=115200,
	BD_rate128000=128000, BD_rate256000=256000
}Baudrate;

typedef enum{
	FiveBits, SixBits, SevenBits, EightBits, NineBits=7
}DataBit_Num;

typedef enum{
	oneBit,TwoBits
}StopBit_Num;
typedef struct{

	Parity_Mode   UART_ParityType;
	Baudrate      UART_BitRate;
	DataBit_Num   UART_DataBit_Num;
	StopBit_Num   UART_StopBit_Num;

}UART_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
