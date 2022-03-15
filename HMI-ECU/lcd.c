/*-------------------------------------------------------
 * [FILE NAME]: lcd.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 5/10/2021
 *
 * [DESCRIPTION]: source file for AVR LCD driver
 -------------------------------------------------------*/
//#error "it's not complete yet"
#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>

/*
 * Description:
 * 1. it is a function that sets up the direction of the required pins of RS,R/W,ENABLE
 * 	  as output pins and port of commands & data as output port.
 * 2. sending (0x38) command to use 2 lines + 5x8 matrix mode.
 * 3. sending (0x0c) command to turn on the display and turn off the cursor.
 * 4. sending (0x01) command to clear the screen.
 */
void LCD_init(void)
{
	/* RS PIN logic_low for instructions , logic_high for data */
	GPIO_setupPinDirection(LCD_RS_PORT_ID , LCD_RS_PIN_ID , PIN_OUTPUT);

	/* R/(W)' logic_low for write , logic_high for read */
	GPIO_setupPinDirection(LCD_RW_PORT_ID , LCD_RW_PIN_ID , PIN_OUTPUT);

	/* Enable */
	GPIO_setupPinDirection(LCD_ENABLE_PORT_ID , LCD_ENABLE_PIN_ID , PIN_OUTPUT);
#if (LCD_COMMAND_BITS == 8)

	/* setting up the direction of the whole port */
	GPIO_setupPortDirection(LCD_COMMANDS_DATA_PORT_ID , PORT_OUTPUT);

	LCD_sendCommand(0X38); /* 2 lines and 8-bits mode command */

#else

	/* LCD command bits = 4 bits */
	GPIO_setupPinDirection(LCD_COMMANDS_DATA_PORT_ID , LCD_COMMAND_BIT_1 , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_COMMANDS_DATA_PORT_ID , LCD_COMMAND_BIT_2 , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_COMMANDS_DATA_PORT_ID , LCD_COMMAND_BIT_3 , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_COMMANDS_DATA_PORT_ID , LCD_COMMAND_BIT_4 , PIN_OUTPUT);

	LCD_sendCommand(0X02); /* Return home command */
	LCD_sendCommand(0x28); /* 2 lines and 4-bits mode command */

#endif



	LCD_sendCommand(0X0C); /* Display on cursor off command */
	LCD_sendCommand(0X01); /* Clear display screen command */

}

/*
 * Description:
 * this function is to send the essential command to the LCD.
 */
void LCD_sendCommand (uint8 a_command)
{
	/* RS PIN logic_low for instructions , logic_high for data */
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_LOW);

	/* R/(W)' logic_low for write , logic_high for read */
	GPIO_writePin(LCD_RW_PORT_ID , LCD_RW_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

	/* Enable */
	GPIO_writePin(LCD_ENABLE_PORT_ID , LCD_ENABLE_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

	/* for writing the command */
	GPIO_writePort(LCD_COMMANDS_DATA_PORT_ID , a_command);
	_delay_ms(1);

	/* Disable LCD */
	GPIO_writePin(LCD_ENABLE_PORT_ID , LCD_ENABLE_PIN_ID , LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description:
 * this function is used to display a single character on the LCD.
 */
void LCD_displayCharacter (uint8 a_character)
{
	/* RS PIN logic_low for transferring instructions , logic_high for data */
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_HIGH);

	/* R/(W)' logic_low for write , logic_high for read */
	GPIO_writePin(LCD_RW_PORT_ID , LCD_RW_PIN_ID , LOGIC_LOW);
	_delay_ms(1);

	/* Enable LCD */
	GPIO_writePin(LCD_ENABLE_PORT_ID , LCD_ENABLE_PIN_ID , LOGIC_HIGH);
	_delay_ms(1);

	/* for writing the command */
	GPIO_writePort(LCD_COMMANDS_DATA_PORT_ID , a_character);
	_delay_ms(1);

	/* Disable LCD */
	GPIO_writePin(LCD_ENABLE_PORT_ID , LCD_ENABLE_PIN_ID , LOGIC_LOW);
	_delay_ms(1);
}

/*
 * Description:
 * this function takes the string and display it.
 */
void LCD_displayString (const char *string)
{
	while(*(string) != '\0')
	{
		/* display the characters of the string one by one */
		LCD_displayCharacter(*string) ;
		string++ ;
	}
}

/*
 * Description:
 * 1. it takes the the row no. and the column no. then shift the cursor to this location.
 */
void LCD_moveCursor(uint8 row , uint8 col)
{
	uint8 LCD_cursor_address = 0 ;
	switch(row)
	{
	case 0:
		/* The address of the first location at the first row + the no. of the column */
		LCD_cursor_address = LCD_FIRST_ROW + col;
		break;
	case 1:
		/* the address of the first location at the second row + the no. of the column */
		LCD_cursor_address = LCD_SECOND_ROW + col;
		break;
	case 2:
		/* the address of the first location at the third row + the no. of the column */
		LCD_cursor_address = LCD_THIRD_ROW + col;
		break;
	case 3:
		/* the address of the first location at the forth row + the no. of the column */
		LCD_cursor_address = LCD_FOURTH_ROW + col;
		break;
	}
	/*LCD_SET_CURSOR_LOCATION = 0x80 The command of setting the cursor at the required location */
	LCD_sendCommand(LCD_SET_CURSOR_LOCATION | LCD_cursor_address);
}

/*
 * Description:
 * this function takes row , column and the string as arguments then displays this string
 * at this specific row and column.
 */
void LCD_displayStringRowColumn (uint8 row , uint8 col , const char *strROWCOL)
{
	LCD_moveCursor(row, col) ;/* it moves the cursor to this specific location */
	LCD_displayString(strROWCOL) ;/* it displays the string at the required location */
}

/*
 * Description:
 * this function clears the screen of the LCD.
 */
void LCD_clearScreen (void)
{
	LCD_sendCommand(0x01);
}

/*
 * Description:
 * this function displays the integer on the LCD after converting it to a string using the
 * built-in function:
 * itoa(integer_value , array_where_the_ascii_will_be_displayed , base_of_this_value).
 */
void LCD_intgerToString (int data)
{
	char int_to_ascii[16] ;/* this array for saving the converted data */
	itoa(data , int_to_ascii , 10);/* 10 is for decimal as the data is a decimal value */
	LCD_displayString(int_to_ascii);
}




















