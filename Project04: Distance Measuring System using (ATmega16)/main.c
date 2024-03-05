#include"lcd.h"
#include"ultrasonic.h"
#include"avr/io.h"

int main(void)
{
	uint16 distance;
	SREG |= (1<<7);         /* enable interrupts */
	LCD_init();             /* initialize LCD driver */
	Ultrasonic_Init();      /* initialize Ultrasonic sensor driver */

	distance=Ultrasonic_ReadDistance(); /* load sensor read in distance local variable */

	/* always display and wait for distance value to be displayed in the space */
	LCD_displayString("Distance =    cm ");
	LCD_moveCursor(0,11);

	LCD_intgerToString(distance); /* display distance value */
}
