#include "SPI.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

#define WAIT_COUNT 60000

uint16_t ADC_MODES[3] PROGMEM = {MODE_TEST, MODE_TEST, MODE_TEST};
static volatile uint8_t MODE_COUNT = 0; //mode you are currently reading

#define SELECT_ADC() (PORTB &= ~(1<<ADC_CS))
#define DESELECT_ADC() (PORTB |= (1<<ADC_CS))

void TestADC(void)
{
	char c = 0;
	transfer(0x02);
	transfer(0x40);
	transfer(0x76);
	WaitForRDY();
	//_delay_ms(500);
	transfer(0x11);
	//c = transfer(0x00);
	//uart_putc(c);
	c = transfer(0x00);
	//uart_putc(c);
};

void PrintMode(void)
{
	transfer(0x12);
	unsigned char c = transfer(0x00);
	//uart_putc(c);
	c = transfer(0x00);
	//uart_putc(c);

};

void SETADC_MODE(void)
{
	transfer(0x02); //mode register
	transfer(pgm_read_byte((uint8_t*)ADC_MODES+2*MODE_COUNT+1));
	transfer(pgm_read_byte((uint8_t*)ADC_MODES+2*MODE_COUNT));
	PrintMode();
};

void READADC_DATA(void)
{
	transfer(0x11);
	PRESSURE_DATA[MODE_COUNT] = (transfer(0x00)<<8);
	PRESSURE_DATA[MODE_COUNT] |= (transfer(0x00));

};

void ReadADC(void)
{
	
	READADC_DATA();
	MODE_COUNT = ((MODE_COUNT+1)%3); //move mode count forward...
	SETADC_MODE();


	//DESELECT_ADC(); //set adc_cs high
};

void InitSPI(void)
{
	DDR_SPI = (1<<MOSI)|(1<<SCK)|(1<<ADC_CS)|(1<<DD_SS);
	DDR_SPI &= ~(1<<ADC_RDY);
	

	SELECT_ADC();
	//DESELECT_ADC();

	SPCR = ((1<<SPE)|(1<<MSTR)|(0<<SPR0)|(1<<SPR1)|(0<<DORD)|(0<<CPOL)|(1<<CPHA));
	uint8_t tmp;
	tmp = SPSR;
	tmp = SPDR;
};


void SetFilters(void)
{
/* Check out this site to figure out what filters to use
http://designtools.analog.com/dt/adc/codegen/ad7731.html
*/

	transfer(0x03);
	transfer(0x80);
	transfer(0x05);

};

void SelfCalibrate(void)
{
/* Check out this site to figure out what calibrations to use to use
http://designtools.analog.com/dt/adc/codegen/ad7731.html
*/

	
	do{
	transfer(0x02);
	transfer(0xD0);
	transfer(0x86);
	} while(WaitForRDY());
	do{
	transfer(0x02);
	transfer(0xB0);
	transfer(0xB6);
	} while(WaitForRDY());
	//calibrate Alpha
	do {
	transfer(0x02);
	transfer(0xC0);
	transfer(0x95);
	} while(WaitForRDY());
	do{
	transfer(0x02);
	transfer(0xA0);
	transfer(0xB5);
	}while(WaitForRDY());

	//calibrate Altitude
	do{
	transfer(0x02);
	transfer(0xC0);
	transfer(0xF5);
	}while(WaitForRDY());
	do{
	transfer(0x02);
	transfer(0xA0);
	transfer(0xF5);
	} while(WaitForRDY());

	
};

void RESET_SPI()
{
	for(unsigned char i = 0; i<4; i++)
			transfer(0Xff);
};

uchar transfer( uchar byte)
{
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
};

uint8_t WaitForRDY(void)
{
	uint16_t X = 0;
	while(((PINB) & (1<<ADC_RDY)))
	{
		X++;
		if(X>WAIT_COUNT)
		{
			RESET_SPI();
			//uart_puts_P("Reset\r\n");
			PrintStatus();
			return 0;
		};
	};
	return 1;
};


void PrintStatus(void)
{
	RESET_SPI();
	transfer(0x10);
	transfer(0x00); //read the byte
	//uart_putc(byte);
};


