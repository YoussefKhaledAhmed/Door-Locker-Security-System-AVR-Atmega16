/*-------------------------------------------------------
 * [FILE NAME]: uart.h
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 9/10/2021
 *
 * [DESCRIPTION]: header file for AVR UART driver
 -------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/****************************************
 *          SOME DEFINITIONS            *
 ****************************************/

typedef enum {
	FIVE_BITS , SIX_BITS , SEVEN_BITS , EIGHT_BITS , NINE_BITS = 7
} no_of_bits_per_frame;

typedef enum {
	DISABLED , EVEN_PARITY = 2 , ODD_PARITY
} parity_mode;

typedef enum{
	ONE_BIT , TWO_BITS
} no_of_stop_bits;

typedef struct{
	no_of_bits_per_frame CHARACTER_SIZE;
	parity_mode PARITY_MODE;
	no_of_stop_bits STOP_BITS_NO;
	uint32 BIT_RATE;
} uart_config;

/**********************************************
 *           Functions prototype              *
 **********************************************/

void UART_init (const uart_config*) ;
void UART_sendByte (uint8 data);
uint8 UART_receiveByte (void);
void UART_sendString (const uint8 *);
void UART_receiveString (uint8 *);


#endif /* UART_H_ */
