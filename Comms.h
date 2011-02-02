#ifndef __COMMS_H__
#define __COMMS_H__

#include <stdint.h>
#include <stdlib.h>

#define MUX_A PD5
#define MUX_B PD6

#define SET_RADIO()	(PORTD &= ~(1<<MUX_A | 1<<MUX_B))
#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)
#define UART_BAUD_SELECT_DOUBLE_SPEED(baudRate,xtalCpu) (((xtalCpu)/((baudRate)*8l)-1)|0x8000)

#define DATA_PACKET_START	0xFAFB
#define END_SIGNAL			0xAAFF

#define DATA_WRITE_MODE		0x01
#define STATUS_WRITE_MODE	0x02
#define WRITE_STRING		0x03

<<<<<<< HEAD
#define COMMAND_BUFFER_SIZE 16 //needs to be power of 2
#define COMMAND_BUFFER_MASK (COMMAND_BUFFER_SIZE-1)
#define BUFFER_FULL	0x01
#define ADD_SUCCESS	0x02

/** COMMAND LIST **/
#define WRITE_DATA 'L'
#define TEST_COMMAND 't'

typedef struct
{
	volatile uint8_t *DATA;
	volatile uint16_t head, tail; //index of head and tail
	volatile uint16_t count;
	volatile uint8_t Status;
} RING_BUFFER;

=======
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9
typedef struct
{
	uint16_t start;
	uint32_t CLOCK_TIME;
	long GPS_TIME;
	long Lattitude;
	long Longitude;
	long Altitude;
	long Ground_Speed;
	long Speed_3d;
	long Ground_Course;
	uint8_t NumSats;
	uint8_t Fix;
	float GYRO_X; //single percision float in labview
	float GYRO_Y;
	float GYRO_Z;
	float ACCEL_X;
	float ACCEL_Y;
	float ACCEL_Z;
	uint16_t Temp; //taken from bmp thingy
	uint16_t CabinPressure; //taken from bmp thingy
	float AIRSPEED;
	float ALTITUDE_P;
	float ALPHA;
	uint16_t end;
	volatile uint8_t block; //don't transmit block, but set to one while transmitting
} RADIO_OUT_DATA;

typedef struct
{
	uint8_t Writing;
	uint8_t *Current; //points to data packet...
	uint8_t *DataPacket; //pointer to the head
	volatile size_t PACKET_SIZE;
} TRANSMIT_PACKAGE;


//Initiate the radio writer stuff
extern void INIT_RADIO(unsigned int baudrate);
<<<<<<< HEAD
uint8_t WriteData(uint8_t WriteMode);

//Data for the command buffer
void ClearCommandBuffer(void);
void CheckCommand(void);
=======

uint8_t WriteData(uint8_t WriteMode);
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9

#endif


