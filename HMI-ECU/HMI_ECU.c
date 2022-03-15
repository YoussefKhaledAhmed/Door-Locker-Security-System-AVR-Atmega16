/*-------------------------------------------------------
 * [FILE NAME]: HMI-ECU.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 27/10/2021
 *
 * [DESCRIPTION]: source file for HMI-ECU
 -------------------------------------------------------*/

#include "HMI_FUNCTIONS.h"
#include <avr/io.h>

int main()
{
	uint8 password[5] = {};
	uint8 main_menu_choice = 0;
	SREG |= (1<<7);
	HMI_init();
	HMI_firstTimeOrChangePassword(password);
	HMI_sendPassword(password);
	while(1)
	{
	main_menu_choice = HMI_mainMenu();
	HMI_openOrError(password,main_menu_choice);
	}
}








