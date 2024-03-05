#include"avr/io.h"
#include"lcd.h"
#include"keypad.h"
#include"uart.h"
#include"timer0.h"
#include<util/delay.h>
#define Enter '='
#define match 1
#define mismatch 0
#define MC2_READY 0x01
#define open_door '+'
#define change_pass  '-'
#define open 1
#define alarm 2
uint8 flag =0, counter1 =0 ,counter2 =0, compare;

void Call_Back_Func1(void) //msh b3rf atl3 menha
{
	if(flag==open){

		 if(counter1 == 0){

			LCD_clearScreen();
			counter1++;
		}
		else if(counter1 == 1){

			LCD_displayString("door is unlocking");
			counter1++;
		}
		else if(counter1 == 2){

			LCD_clearScreen();
			LCD_displayString("yes"); //code stick here
			counter1 = 0;
			flag = 0;
			Timer_DeInit();
			return;
		}
	}
	else if(flag == alarm){

		counter2++;

		if(counter2 == 4){

			counter2 = 0;
			flag = 0;
			Timer_DeInit();
			return;
		}

	}
}
/*uint8 compare_pass(uint8 *ptr1,uint8 *ptr2){

	uint8 i=0,  j=0,  k=0;
	uint8 compare = match ;

	while(k<5)
	{
		if(ptr1[i] != ptr2[j])
		{
			compare = mismatch ;
			break;
		}
		else{
			i++;
			j++;
			k++;
		}
	}
	return compare;
}*/
/*void get_pass(uint8 (*ptr_save_pass)[5])
{
	LCD_displayString("please enter Pass");
	LCD_moveCursor(1,0);
	for(uint8 i=0;i<5;i++)
	{
		if(0 <= KEYPAD_getPressedKey() && 9 >= KEYPAD_getPressedKey()){
		(*ptr_save_pass)[i]=KEYPAD_getPressedKey();
		}
		LCD_displayCharacter('*');
	}

}*/

int main(void){

	SREG |= (1<<7);         /* enable interrupts */
	LCD_init();
	Timer_ConfigType Timer_Config = {Normal,F_CPU_1024,0,0};
	UART_ConfigType UART_Config = {Disable,BD_rate9600,EightBits,oneBit};
	UART_init(&UART_Config);

	while(1){

		uint8 passcode[5];
		uint8 passcode_again[5];
		uint8 i,j,data,k,choice;
		/*step 1*/
		/* take passcode from the user */
		LCD_clearScreen();
		LCD_displayString("Enter Pass");
		LCD_moveCursor(1,0);
		for(i=0;i<5;i++)
		{

			passcode[i]=KEYPAD_getPressedKey();
			_delay_ms(2000);
			LCD_displayCharacter('*');
		}
		i=0;

		/* waiting user to press enter */
		while(Enter != KEYPAD_getPressedKey());
		_delay_ms(2000);
		LCD_clearScreen();

		/* take passcode from the user again*/
		LCD_displayString("Enter Pass again");
		LCD_moveCursor(1,0);
		for(i=0;i<5;i++)
		{
			passcode_again[i]=KEYPAD_getPressedKey();
			_delay_ms(2000);
			LCD_displayCharacter('*');
		}
		i=0;

		/*waiting user to press enter */
		while(Enter != KEYPAD_getPressedKey());
		_delay_ms(2000);
		LCD_clearScreen();

		/*compare first passcode with second passcode*/
		for(k=0;k<5;k++)
		{
			compare = match;
			if(passcode[k] != passcode_again[k])
			{   LCD_displayString("X");
			compare = mismatch ;
			_delay_ms(2000);
			LCD_clearScreen();
			break;
			}
		}

		if(compare == mismatch){
			LCD_displayString("wrong");
			_delay_ms(2000);
			LCD_clearScreen();
			continue; /*return to step 1*/
		}
		else{


			UART_sendByte(MC2_READY);
			while(UART_recieveByte() != MC2_READY);
			LCD_clearScreen();
			LCD_displayString("saving data");
			_delay_ms(2000);
			/*send passcode to be saved in memory*/
			for(uint8 i=0;i<5;i++){
				data=passcode[i];
				UART_sendByte(data);
				_delay_ms(2000);

			}
		}
		while(1){
			/*step 2*/
			LCD_clearScreen();
			LCD_displayString("+  open door");
			LCD_moveCursor(1,0);
			LCD_displayString("-  change PassCode");
			choice=KEYPAD_getPressedKey();
			_delay_ms(2000);
			/*if user choose to open the door*/
			if(open_door == choice){

				for( j=0;j<3;j++){
					/*ask user to enter passcode*/
					LCD_clearScreen();
					LCD_displayString("Enter Pass");
					LCD_moveCursor(1,0);
					for(i=0;i<5;i++)
					{
						passcode[i]=KEYPAD_getPressedKey();
						_delay_ms(2000);
						LCD_displayCharacter('*');
					}

					/*waiting user to press enter */
					while(Enter != KEYPAD_getPressedKey());
					_delay_ms(2000);
					LCD_clearScreen();
					/*compare passcode with saved passcode*/
					for(k=0;k<5;k++)
					{
						compare = match;
						if(passcode[k] != passcode_again[k])
						{
							LCD_displayString("wrong");
							compare = mismatch ;
							break;
						}
					}
					/*if the passcode is correct*/
					if(compare == match){
						/*order system to open the door*/
						LCD_displayString("send open");
						_delay_ms(4000);
						LCD_clearScreen();
						UART_sendByte(MC2_READY);
						while(UART_recieveByte() != MC2_READY){}
						UART_sendByte(open);

						flag=open;
						LCD_clearScreen();
									LCD_displayString("Door is locking");
						Timer_Init(&Timer_Config);
						Timer_setCallBack(Call_Back_Func1);


						break;
					}
				}
			}
			/*if user want to change saved passcode*/
			else if(change_pass == choice){
				for( j=0;j<3;j++){
					/*ask user to enter the saved passcode*/
					LCD_clearScreen();
					LCD_displayString("Enter Pass");
					LCD_moveCursor(1,0);
					for(i=0;i<5;i++)
					{

						passcode[i]=KEYPAD_getPressedKey();
						_delay_ms(2000);
						LCD_displayCharacter('*');
					}
					i=0;
					/*waiting user to press enter*/
					while(Enter != KEYPAD_getPressedKey());
					_delay_ms(2000);
					/*compare the passcode entered by user and the saved one */
					for(k=0;k<5;k++)
					{
						compare = match;
						if(passcode[k] != passcode_again[k])
						{
							compare = mismatch ;
							break;
						}
					}
					/*if the passcode entered by user is correct*/
					if( compare == match){
						break; /*return to step 1*/
					}
				}
			}
			/*if user entered wrong passcode for 3 times*/
			if(j==3){
				/*order system to activate alarm*/
				UART_sendByte(MC2_READY);
				while(UART_recieveByte() != MC2_READY);
				UART_sendByte(alarm);

				flag = alarm;
				LCD_clearScreen();
										LCD_displayString("DANGER");
				Timer_Init(&Timer_Config);
				Timer_setCallBack(Call_Back_Func1);
				LCD_clearScreen();
						LCD_displayString("no");
				continue; /*return to step 2*/
			}
			break;

		}

	}
}
