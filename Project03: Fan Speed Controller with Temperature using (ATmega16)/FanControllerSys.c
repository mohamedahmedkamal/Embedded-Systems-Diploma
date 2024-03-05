/***********************************************************************************************
 *
 * Project Name: Fan Controller System

 * Description: The fan is automatically turned ON or OFF and change its speed
                according to the temperature.

 * Author: Mohamed Ahmed kamal
 *
/*************************************************************************************************
                                            Includes
 *************************************************************************************************/
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
/*************************************************************************************************
 *                                         APPLICATION
 ************************************************************************************************/
int main(){


	uint8 temp;  /*variable that carry the measured temp from sensor func*/

	ADC_ConfigType Adc_Config= {Internal,F_CPU_8};  /*configure ADC ref_volt and Prescaler*/

	LCD_init();             /* initialize LCD driver */
	ADC_init(&Adc_Config); /* initialize ADC driver */
	DcMotor_Init();        /*initialize DcMotor driver*/

	/*always display this 2 sentences waiting for their values*/

	LCD_displayString("Fan is ");
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =     C");


	while(1){

		temp =  LM35_getTemperature(); /*read temp from sensor*/

		if(temp<30){

			/*if the temp read is less than 30 C
			 * turn OFF the fan
			 * display fan state
			 * display instant Temp*/

			DcMotor_Rotate(OFF,0);
			LCD_moveCursor(0,7);
			LCD_displayString("OFF");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		}
		else if(temp>=30 && temp<60)
		{
			/*if the temp read is between 30 C and 60 C
			 * turn ON the fan with 25% of its speed
			 * display fan state
			 * display instant Temp*/

			DcMotor_Rotate(CW,25);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp>=60 && temp<90)
		{
			/*if the temp read is between 60 C and 90 C
			 * turn ON the fan with 50% of its speed
			 * display fan state
			 * display instant Temp*/

			DcMotor_Rotate(CW,50);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');

		}
		else if(temp>=90 && temp<120)
		{
			/*if the temp read is between 90 C and 120 C
			 * turn ON the fan with 75% of its speed
			 * display fan state
			 * display instant Temp*/

			DcMotor_Rotate(CW,75);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
		}
		else if(temp>120)
		{
			/*if the temp read is above 120 C
			 * turn ON the fan with 100% of its speed
			 * display fan state
			 * display instant Temp*/

			DcMotor_Rotate(CW,100);
			LCD_moveCursor(0,7);
			LCD_displayString("ON");
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
		}
	}

}
