/*-------------------------------------------------------
 * [FILE NAME]: keypad.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 30/9/2021
 *
 * [DESCRIPTION]: Source file for AVR keypad driver
 -------------------------------------------------------*/

#include"keypad.h"
#include"gpio.h"
#include"common_macros.h"

#if (TOTAL_NUMBER_OF_COLS == 3)
	static uint8 KEYPAD_4x3_adjustKeyNumber (uint8 a_buttonNumber);
#else
	static uint8 KEYPAD_4x4_adjustKeyNumber (uint8 a_buttonNumber);
#endif

uint8 KEYPAD_getPressedKey (void)
{
	uint8 col , row;
	uint8 keypad_port_value = 0;

	while(1)
	{
		for(col = 0 ; col < TOTAL_NUMBER_OF_COLS ; col++)
		{
			GPIO_setupPortDirection(KEYPAD_PORT_ID,PORT_INPUT);
			GPIO_setupPinDirection(KEYPAD_PORT_ID , col + KEYPAD_FIRST_COL_PIN_ID , PIN_OUTPUT);
#if (KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
			keypad_port_value = (~(1<<(KEYPAD_FIRST_COL_PIN_ID + col)));
#else
			keypad_port_value = (1<<(KEYPAD_FIRST_COL_PIN_ID + col));
#endif
			GPIO_writePort(KEYPAD_PORT_ID , keypad_port_value);

			for(row = 0 ; row < TOTAL_NUMBER_OF_ROWS ; row++)
			{
				if(GPIO_readPin(KEYPAD_PORT_ID , row + KEYPAD_FIRST_ROW_PIN_ID) == KEYPAD_BUTTON_PRESSED)
				{
#if (TOTAL_NUMBER_OF_COLS == 3)
					return KEYPAD_4x3_adjustKeyNumber ((row * TOTAL_NUMBER_OF_COLS)+ col + 1);
#else
					return KEYPAD_4x4_adjustKeyNumber ((row * TOTAL_NUMBER_OF_COLS)+ col + 1);
#endif
				}
			}
		}
	}
}

#if (TOTAL_NUMBER_OF_COLS == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber (uint8 a_buttonNumber)
{
	uint8 keypad_button = 0;
	switch(a_buttonNumber)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = a_buttonNumber;
				break;
	}
	return keypad_button;
}

#else

static uint8 KEYPAD_4x4_adjustKeyNumber (uint8 a_buttonNumber)
{
	uint8 keypad_button = 0 ;
	switch(a_buttonNumber)
	{
	case 1:
		keypad_button = 7 ;
		break;
	case 2:
		keypad_button = 8 ;
		break;
	case 3:
		keypad_button = 9 ;
		break;
	case 4:
		keypad_button = 'A';
		break;
	case 5:
		keypad_button = 4 ;
		break;
	case 6:
		keypad_button = 5 ;
		break;
	case 7:
		keypad_button = 6 ;
		break;
	case 8:
		keypad_button = 'B' ;
		break;
	case 9:
		keypad_button = 1 ;
		break;
	case 10:
		keypad_button = 2 ;
		break;
	case 11:
		keypad_button = 3 ;
		break;
	case 12:
		keypad_button = '-' ;
		break;
	case 13:
		keypad_button = '*' ;
		break;
	case 14:
		keypad_button = 0 ;
		break;
	case 15:
		keypad_button = '=' ;
		break;
	case 16:
		keypad_button = '+' ;
		break;
	}
	return keypad_button ;
}
#endif















