#ifndef __SPI_H
#define __SPI_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "uart.h"

#define uchar unsigned char

static volatile uint16_t PRESSURE_DATA[3] = {0};	

#define MOSI	PB5
#define MISO 	PB6
#define SCK 	PB7
#define DDR_SPI	DDRB
#define DD_SS   PB4

#define ADC_CS 	PB1
#define ADC_RDY PB2

#define MODE_ALT		0x40F4
#define MODE_SPEED		0x5086
#define MODE_ALPHA		0x4095
#define MODE_TEST		0x4076



uchar transfer(uchar byte);


/*ADC FUNCTIONS*/
#define CHECK_RDY()	!(((PINB) & (1<<ADC_RDY))) //returns 1 if ready for read

/**Setup Stuff**/
void SetFilters(void);
void SelfCalibrate(void);
void InitSPI(void);

/**READ STUFF**/
void ReadADC();
void RESET_SPI();
uint8_t WaitForRDY(void);

void PrintStatus(void);
void PrintMode(void);
void TestADC(void);


#endif
