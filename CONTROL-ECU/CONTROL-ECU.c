/*-------------------------------------------------------
 * [FILE NAME]: HMI-ECU.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 27/10/2021
 *
 * [DESCRIPTION]: source file for HMI-ECU
 -------------------------------------------------------*/

#include "CONTROL_FUNCTIONS.h"
#include "uart.h"
#include "external_eeprom.h"
#include "avr/io.h"
#include <util/delay.h>

int main()
{
	uint8 password[5] = {};
	SREG |= (1<<7);
	CONTROL_init();
	CONTROL_receiveThePassword(password);
	CONTROL_savePassword(password);
	while(1)
	{
	CONTROL_checkPassword(password);
	}
}
