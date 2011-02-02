#include "SPI.h"
#include "Comms.h"
#include "Buzzer.h"

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/wdt.h>


#define UART_BAUD_RATE	38400

RADIO_OUT_DATA Data_Packet;
TRANSMIT_PACKAGE Transmit_Packet;

<<<<<<< HEAD
void TestDataBuffer(void)
{
	Data_Packet.ACCEL_X = 0;
	Data_Packet.ACCEL_Y = 0x01;
	Data_Packet.ACCEL_Z = 0x02;
	Data_Packet.AIRSPEED = 0x05;
	Data_Packet.ALTITUDE_P = 0x15;
	Data_Packet.GPS_TIME = 0x33;
	Data_Packet.CLOCK_TIME = 0xff;
}
=======
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9

void SETUP(void)
{
	//disable watch dog timer
	wdt_disable();
<<<<<<< HEAD
	TestDataBuffer();
=======
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9

	INIT_RADIO(38400);

	SET_RADIO();
	sei();
	BUZZER_SETUP();
	
	InitSPI();

	wdt_enable(WDTO_8S); //enable watch dog timer

	RESET_SPI();
	ReadADC(); //do the first adc read
};


/**Functions for stuff**/
int main(void)
{

	SETUP();
	RESET_SPI();
	
	while(1)
	{
		asm("wdr"); //reset wdt
		
			//if(CHECK_RDY() || (NO_ADC_COUNT>NO_COUNT_MAX))
			//	ReadADC();
			//else
			//	NO_ADC_COUNT++;
			TestADC();

<<<<<<< HEAD
			CheckCommand();
			_delay_ms(500);
=======
			//_delay_ms(500);
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9
	};
};


