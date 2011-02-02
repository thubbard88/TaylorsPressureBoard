#include "Buzzer.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define TIME_COUNT 500
static volatile unsigned int count_global = 0;
static volatile unsigned int time = 0;
static volatile uint8_t buzz = 0;

void BUZZER_SETUP(void)
{
	//set buzzer pin to output
	DDRA |= (1<<BUZZ_PIN);
	
	//Configure timer 0 for CTC mode
	TCCR0A |= (1<<WGM01);
	OCR0A = 30;

	BUZZZ_DURATION(10);
};

void BUZZZ_DURATION(unsigned int count)
{
	//use a 256 prescaler
	//400hz = 97 clocks
	count_global = count;
	time = 0;
	TIMSK0 |= (1<<OCIE0A); //enable the interrupt
	TCCR0B |= (1<<CS02); //start timer at Fcpu/256
	return;
	
};

ISR(TIMER0_COMPA_vect)
{	
	if(buzz)
		PORTA ^= (1<<BUZZ_PIN);
	if(time<1)
	{
		count_global--;
		time = TIME_COUNT;
		buzz ^= 1;
	};
	time--;
	if(!count_global)
		TIMSK0 &= ~(1<<OCIE0A); //DISABLE THE INTTERUPT

};
