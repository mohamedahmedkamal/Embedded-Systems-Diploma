#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char seconds = 0 , minutes =0 , hours =0;
ISR(TIMER1_COMPA_vect){
	seconds++;
	if(seconds == 60){
		seconds = 0;
		minutes ++;
	}
	if(minutes == 60){
		minutes = 0;
		hours ++;
	}
	if(hours == 24){
		hours =0;
	}
}

ISR(INT2_vect)
{
	TIMSK = (1<<4);
}

ISR(INT0_vect){

	seconds =0;
	minutes =0;
	hours =0;
}

ISR(INT1_vect)
{
	TIMSK &= ~(1<<4);
}
void Init_Timer1(void)
{
	SREG |=(1<<7);
	TCNT1 = 0;
	OCR1A= 1000;
	TCCR1A = (1<<FOC1A);
	TCCR1B =  (1<<WGM12) | (1<<CS10) | (1<<CS12) ;
	TIMSK = (1<<4);
}

void RESUME (void)
{
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
	DDRB  &= ~(1<<PB2);                  // Configure INT2/PB2 as input pin
	PORTB |= (1<<PB2);                    //enable internal pull-up
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT2
	MCUCSR &= ~(1<<ISC2) ;              // Trigger INT2 with the falling edge

}

void RESET(void){

	SREG  |= (1<<7);                   // Enable interrupts by setting I-bit
	DDRD  &= (~(1<<PD2));              // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);                 //enable internal pull-up
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |=  (1<<ISC01);               // Trigger INT0 with the falling edge

}

void PAUSE (void){

	SREG  |= (1<<7);                   // Enable interrupts by setting I-bit
	DDRD  &= (~(1<<PD3));              // Configure INT1/PD3 as input pin
	PORTD |= (1<<PD3);                 //enable internal pull-up
	GICR  |= (1<<INT1);                 // Enable external interrupt pin INT1
	MCUCR |=  (1<<ISC11) | (1<<ISC10) ;  // Trigger INT0 with the raising edge


}
int main(){

	DDRA |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ; //enable for each 7 segment
	PORTA |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) ; //all 7SEGMENT ARE ON
	DDRC |= 0x0F; //FIRST 4 PINS ARE THE INPUT OF DECODER
	PORTC = 0 ; //SHOW ZERO ON THE 3 7SEGMENT
	RESET();
	PAUSE();
	RESUME();
	Init_Timer1();

	while(1){
		PORTA = (1<<5);
		PORTC = seconds % 10 ;
		_delay_ms(5);
		PORTA = (1<<4);
		PORTC = seconds / 10 ;
		_delay_ms(5);
		PORTA = (1<<3);
		PORTC = minutes % 10 ;
		_delay_ms(5);
		PORTA = (1<<2);
		PORTC = minutes / 10 ;
		_delay_ms(5);
		PORTA = (1<<1);
		PORTC = hours % 10 ;
		_delay_ms(5);
		PORTA = (1<<0);
		PORTC = hours % 10 ;
		_delay_ms(5);

	}
}
