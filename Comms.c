#include "Comms.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

 #define UART0_RECEIVE_INTERRUPT   SIG_USART_RECV
 #define UART0_TRANSMIT_INTERRUPT  SIG_USART_DATA
 #define UART0_STATUS   UCSR0A
 #define UART0_CONTROL  UCSR0B
 #define UART0_DATA     UDR0
 #define UART0_UDRIE    UDRIE0


extern RADIO_OUT_DATA Data_Packet;
extern TRANSMIT_PACKAGE Transmit_Packet;

<<<<<<< HEAD
static RING_BUFFER CommandBuffer;

//INITIATE THE DATA WRITING...
extern void INIT_RADIO(unsigned int baudrate)
{
	/** INITIALIZE THE DATA PACKET **/
	Data_Packet.start = DATA_PACKET_START;
	Data_Packet.end = END_SIGNAL;

	/**INITIALIZE THE COMMAND BUFFER **/
	CommandBuffer.DATA = malloc(COMMAND_BUFFER_SIZE);
	CommandBuffer.count = 0;
	CommandBuffer.head = 0;
	CommandBuffer.tail = 0;

=======
//INITIATE THE DATA WRITING...
extern void INIT_RADIO(unsigned int baudrate)
{
	Data_Packet.start = DATA_PACKET_START;
	Data_Packet.end = END_SIGNAL;

>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9
	//enable the mux pins...
	DDRD |= (1<<MUX_A) | (1<<MUX_B);

	//set the baud rate
	if ( baudrate & 0x8000 )
	{
		UART0_STATUS = (1<<U2X0);  //Enable 2x speed
		baudrate &= ~0x8000;
	};
	UBRR0H = (unsigned char)(baudrate>>8);
	UBRR0L = (unsigned char) baudrate;

	UART0_CONTROL = _BV(RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);

	WriteData(WRITE_STRING);
};


<<<<<<< HEAD
//EACH DATA PACKET SHOULD LOOK LIKE <start signal>data<end signal>
=======
//EACH DATA PACKET SHOULD LOOK LIKE <start>
>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9
//returns 0 if a packet is already being written
uint8_t WriteData(uint8_t WriteMode)
{
	if(Transmit_Packet.Writing) //check if there is currently a packet being written... if there is return 0
			return 0;

	static char TestString[] = "This is a test\n ";

	switch(WriteMode)
	{
		case DATA_WRITE_MODE:
			Transmit_Packet.PACKET_SIZE = sizeof(RADIO_OUT_DATA);
			Transmit_Packet.DataPacket = ((uint8_t*) &Data_Packet);
			Transmit_Packet.Writing = 1; //You are writing, so try writing anything new
			Data_Packet.block = 1; //block so nothing is added to the packet...
			UART0_CONTROL |= (1<<UDRIE0);
		case STATUS_WRITE_MODE:
			;
		case WRITE_STRING:
			Transmit_Packet.PACKET_SIZE = strlen(TestString);
			Transmit_Packet.DataPacket = ((uint8_t*) TestString);
			Transmit_Packet.Writing = 1;
			UART0_CONTROL |= (1<<UDRIE0);
		default:
			return 0;
	};
	return 1;
};


ISR(USART0_UDRE_vect)
{
	UDR0 = *Transmit_Packet.DataPacket;
	Transmit_Packet.DataPacket++;
	Transmit_Packet.PACKET_SIZE--;

	if(Transmit_Packet.PACKET_SIZE==1)
	{
		Data_Packet.block = 0; //stop blocking
		Transmit_Packet.Writing = 0; //No longer writing
		UART0_CONTROL &= ~(1<<UDRIE0); //disable interrupts

	}

};

<<<<<<< HEAD
/** COMMAND BUFFER FUNCTIONS **/
void ClearCommandBuffer(void)
{
	CommandBuffer.head = CommandBuffer.tail;
	CommandBuffer.count = 0;
};

ISR(USART0_RX_vect)
{
	uint16_t NewTail = (CommandBuffer.tail+1) & COMMAND_BUFFER_MASK;
	uint8_t data = UDR0; //read to clear the data

	if(NewTail == CommandBuffer.head)
	{
		CommandBuffer.Status = BUFFER_FULL;
		//set buffer full pin high
	} else
	{
		CommandBuffer.DATA[NewTail] = data; //add data
		CommandBuffer.tail = NewTail;
		CommandBuffer.count++;
		CommandBuffer.Status = ADD_SUCCESS;
	}
};


/**BYTE COMMAND FOR NOW**/
void CheckCommand(void)
{
	if(!CommandBuffer.count)
		return;
	switch(CommandBuffer.DATA[CommandBuffer.head])
	{
		case WRITE_DATA:
			WriteData(DATA_WRITE_MODE);
			break;
		case TEST_COMMAND:
			WriteData(WRITE_STRING);
			break;
		default:
			break;
	};
	CommandBuffer.count--;
	CommandBuffer.head = (CommandBuffer.head+1) & COMMAND_BUFFER_MASK;

	return;
};
=======


>>>>>>> 43d7a417581efd0dd9c12782e7b7dfc31417faf9
