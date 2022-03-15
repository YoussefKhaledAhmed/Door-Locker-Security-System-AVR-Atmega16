/*-------------------------------------------------------
 * [FILE NAME]: uart.C
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 9/10/2021
 *
 * [DESCRIPTION]: source file for AVR UART driver
 -------------------------------------------------------*/

#include "uart.h"
#include <avr/io.h>
#include "common_macros.h"


void UART_init (const uart_config* configuration)
{
	uint16 UBRR_value = 0;

	/* USCRA bits from bit 2 to bit 7 act as flag so we won't set them here as they   *
	 * are for checking.                                                              *
	 * U2X: is for enabling or disabling the double transmission speed mode           *
	 * MPCM: is set when the receiver is exposed to more than one transmitter         */
	UCSRA = (1<<U2X);

	/**************************** USCRB REGISTER **************************************
	 *RXCIE: RX Complete interrupt enable                                             *
	 *TXCIE: TX Complete interrupt enable                                             *
	 *UDRIE: USART Data Register Empty Interrupt Enable                               *
	 *RXEN: Receiver Enable                                                           *
	 *TXEN: Transmitter Enable                                                        *
	 *UCSZ2: Character Size                                                           *
	 *RXB8: Receive Data Bit 8                                                        *
	 *TXB8: Transmit Data Bit 8                                                       *
	 **********************************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN) | (((configuration -> CHARACTER_SIZE)>>2) << UCSZ2);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | ((((configuration -> CHARACTER_SIZE)&(0X2))>>1)<< UCSZ1) |\
			(((configuration -> CHARACTER_SIZE)&(0X1))<< UCSZ0)|\
			((configuration ->STOP_BITS_NO) << USBS);

	/* Calculate the UBRR register value */
	UBRR_value = (uint16)(((F_CPU / ((configuration -> BIT_RATE) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = UBRR_value>>8;
	UBRRL = UBRR_value;
}


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}






