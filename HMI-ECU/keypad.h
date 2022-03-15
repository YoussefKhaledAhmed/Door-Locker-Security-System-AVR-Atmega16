 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/********************************************************
 *              function prototype                      *
 ********************************************************/
/*
 * Description:
 * get which key is pressed
 */
uint8 KEYPAD_getPressedKey(void);


/********************************************************
 *              definitions                             *
 ********************************************************/
/* total number of rows and columns */
#define TOTAL_NUMBER_OF_COLS  4
#define TOTAL_NUMBER_OF_ROWS  4

/* at which port keypad is connected */
#define KEYPAD_PORT_ID PORTA_ID

/* the first pin where the rows and the columns of the keypad are attached */
#define KEYPAD_FIRST_ROW_PIN_ID PIN0_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

/* this is for detecting if one pin is pressed or not as the push button is connected pulled-up so to check it we should
 * check for LOGIC_LOW but if it is connected pulled-down we should check on LOGIC_HIGH then*/
#define KEYPAD_BUTTON_PRESSED LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH


#endif /* KEYPAD_H_ */






















