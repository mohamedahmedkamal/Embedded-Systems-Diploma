#include"twi.h"
#include"timer0.h"
#include"external_eeprom.h"
#include"buzzer.h"
#include"dc_motor.h"
#include"avr/io.h"
#include"gpio.h"
#include"uart.h"
#include<util/delay.h>
#define MC2_READY 0x01
#define open 1
#define alarm 2

uint8 flag2 =0, counter11 =0 ,counter22 =0,value;

void Call_Back_Func2(void)
{
	if(flag2 == open){
		if(counter11 == 0){

			DcMotor_Rotate_CW();
			counter11++;
		}
		else if(counter11 == 1){

			DcMotor_OFF();
			counter11++;
		}
		else if(counter11 == 2){

			DcMotor_Rotate_ACW();
			counter11=3;
		}
		else if(counter11 == 3){
			DcMotor_OFF();
			counter11=0;
			flag2=0;

		}
	}

	else if(flag2 == alarm){

		counter22++;
		Buzzer_ON();

		if(counter22 == 5){

			counter22 = 0;
			flag2 =0;
			Buzzer_OFF();

		}

	}

}

int main(void)
{
	uint8 i,j,offset;
	uint8 Data[5];
	SREG |= (1<<7);

	Timer_ConfigType Timer_Config = {Normal,F_CPU_1024,0,0};
	UART_ConfigType UART_Config = {Disable, BD_rate9600, EightBits, oneBit};
	TWI_ConfigType TWI_Config = {2,1,prescale1};
	UART_init(&UART_Config);
	Buzzer_Init();
	DcMotor_Init();

	//for testing motor
	DcMotor_Rotate_CW();
	_delay_ms(9000);
	DcMotor_OFF();

	while(1){

		while(UART_recieveByte() != MC2_READY){}
		UART_sendByte(MC2_READY);

		for(i=0;i<5;i++){
			Data[i]=UART_recieveByte();
			_delay_ms(2000);
		}

		TWI_init(&TWI_Config);

		for(j=0;j<5;j++){

			uint16 address = 0x0311 + offset;

			EEPROM_writeByte(address,Data[j]);
			offset++;
		}
		while(UART_recieveByte() != MC2_READY){}
		UART_sendByte(MC2_READY);
		value=UART_recieveByte();

		if(open == value)
		{
			flag2 = open;
			Timer_Init(&Timer_Config);
			Timer_setCallBack(Call_Back_Func2);
		}
		else if(alarm == value){

			flag2 = alarm;
			Timer_Init(&Timer_Config);
			Timer_setCallBack(Call_Back_Func2);
		}

	}
}
