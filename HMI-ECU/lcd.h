/*-------------------------------------------------------
 * [FILE NAME]: lcd.h
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 5/10/2021
 *
 * [DESCRIPTION]: Header file for AVR LCD driver
 -------------------------------------------------------*/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
/*******************************************************
 *            LCD FUNCTIONS PROTOTYPE                  *
 *******************************************************/
void LCD_init (void);
void LCD_sendCommand (uint8 a_command);
void LCD_displayCharacter (uint8 a_character);
void LCD_displayString (const char *string);
void LCD_moveCursor(uint8 col ,uint8 row);
void LCD_displayStringRowColumn (uint8 row , uint8 col , const char *strROWCOL);
void LCD_clearScreen (void);
void LCD_intgerToString (int data);

/******************************************
 *            DEFINITIONS                 *
 ******************************************/
/* LCD_COMMAND DATA PINS */
#define LCD_COMMANDS_DATA_PORT_ID PORTC_ID

#define LCD_COMMAND_BITS 8

#define LCD_COMMAND_BIT_1 0
#define LCD_COMMAND_BIT_2 1
#define LCD_COMMAND_BIT_3 2
#define LCD_COMMAND_BIT_4 3
#define LCD_COMMAND_BIT_5 4
#define LCD_COMMAND_BIT_6 5
#define LCD_COMMAND_BIT_7 6
#define LCD_COMMAND_BIT_8 7

/* LCD RS PIN */
#define LCD_RS_PORT_ID PORTB_ID /* THE PORT WHERE RS PIN IS CONNECTED */
#define LCD_RS_PIN_ID PIN0_ID /* RS PIN logic_low for transferring instructions , logic_high for data */

/* LCD R/(W)' PIN */
#define LCD_RW_PORT_ID PORTB_ID /* THE PORT WHERE R/W PIN IS CONNECTED */
#define LCD_RW_PIN_ID PIN1_ID /* R/(W)' logic_low for write , logic_high for read */

/* LCD ENABLE PIN */
#define LCD_ENABLE_PORT_ID PORTB_ID /* THE PORT WHERE THE ENABLE PIN IS CONNECTED */
#define LCD_ENABLE_PIN_ID PIN2_ID /* Enable */

/* LCD MEMORY LOCATION */
#define LCD_SET_CURSOR_LOCATION 0X80 /* The command of setting the cursor at the required location */
#define LCD_FIRST_ROW 0X00 /* The address of the first location at the first row */
#define LCD_SECOND_ROW 0X40/* the address of the first location at the second row */
#define LCD_THIRD_ROW 0X10/* the address of the first location at the third row */
#define LCD_FOURTH_ROW 0X50/* the address of the first location at the forth row */


#endif /* LCD_H_ */










