/*-----------------------------------------------------------------
 * [FILE NAME]: HMI_FUNCTIONS.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 31/10/2021
 *
 * [DESCRIPTION]: source file for FUNCTIONS used in HMI-ECU
 ------------------------------------------------------------------*/

#include "HMI_FUNCTIONS.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
#include <avr/delay.h>


extern uint8 tick;

/*
 * input: void
 * return: void
 * Description: initializing the HMI_ECU (i.e. initializing the used drivers [UART , LCD])
 */
void HMI_init (void){
	/************************* UART initialization ********************/
	/* configuration is a structure of (uart_config type):            *
	 * no_of_bits_per_frame , parity_mode , no_of_stop_bits , bit rate*/
	uart_config configuration = {EIGHT_BITS , DISABLED , ONE_BIT , 9600};
	/* passing the configuration to the UART_init function */
	UART_init(&configuration);
	/************************* LCD_init ************************/
	LCD_init();
}

/*
 * input: password array pointer
 * return: void
 * description:it basically a function that is responsible for taking the password for the first
 * time or when it's required to change the old one and confirming it if it's confirmed
 * so, the password is saved in the array that is passed to this function through its address.
 */
void HMI_firstTimeOrChangePassword (uint8 *const pass_ptr){

	/* **************************  variables definition  ************************************
	 * confirm_pass[5]: is a temporary array that holds the confirmation password.          *
	 * pass_index: is the index that will loop on the password digits.                      *
	 * end_key: is the password that works as an indication that the user ends entering.    *
	 * the password.                                                                        *
	 * passwords_ptr[2]: is an array of pointers that contains the address of these arrays  *
	 * that hold the password and the configuration password.                               *
	 * check_loop: is the index used in the 2 passwords matching check loop.                *
	 * check_2_passwords: is a number used to check if all the elements in the password and *
	 * the confirmation password are exact the same.                                        *
	 * **************************************************************************************/

	uint8 confirm_pass[5] = {0} , password_index = 0 , end_key = 0 ;
	uint8 *passwords_ptr[2] = {pass_ptr , confirm_pass} , check_loop = 0 , check_2_passwords = 0;
	/* the following do..while loop is for taking the password and confirming that its the
	 * one that the user want to set */
	do{
		LCD_clearScreen();
		LCD_displayString("please enter the password:");
		LCD_moveCursor(1, 0);
		/* the following for loop is for filling the pass_ptr and the confirm_pass arrays */
		for (int loop = 0 ; loop < 2 ; loop++)
		{
			for(password_index = 0 ; password_index < 5 ; password_index++)
			{
				_delay_ms(1500);
				(passwords_ptr[loop])[password_index] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
			}
			/* the following while loop if for confirming that he pressed '=' (i.e. enter) */
			while(1)
			{
				end_key = KEYPAD_getPressedKey();
				if(end_key == '=')
					break;
			}
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "please confirm it:");
			LCD_moveCursor(1, 0);
		}
		/* the following for loop is for checking that the 2 arrays are the exactly the same *
		 * and then moving on.                                                               */
		for(check_loop = 0 ; check_loop < 5 ; check_loop++)
		{
			/* at any time the 2 elements that will have the same index are different then *
			 * break the loop with changing the check_2_passwords value to 9.              */
			if(pass_ptr[check_loop] != confirm_pass[check_loop])
			{
				check_2_passwords = 9;
				break;
			}
			else
			{
				check_2_passwords = 0;
			}
		}
		/* here is the if statement that is checking for the value of check_2_passwords.*/
		if(9 == check_2_passwords)
		{
			LCD_displayStringRowColumn(0, 0, "the 2 passwords ");
			LCD_displayStringRowColumn(1, 0, "don't match");
			_delay_ms(5000);
		}
		/* while these 2 passwords are different then loop to get a new one.*/
	}while(9 == check_2_passwords);
}

/*
 * input: the password array pointer
 * return: void
 * Description: it is the function responsible for
 */
void HMI_sendPassword (uint8* const pass_ptr)
{
	UART_sendByte(ready);
	while (UART_receiveByte() != ready){}
	for (uint8 i = 0 ; i < 5 ; i++)
	{
		UART_sendByte(pass_ptr[i]);
	}
}

/*
 * input: void
 * return: chosen character
 * Description: it presents the menu , takes the chosen character then return it to the
 * main function.
 */
uint8 HMI_mainMenu (void)
{
	/* presenting the menu */
	LCD_clearScreen();
	LCD_displayString("+: open door");
	LCD_displayStringRowColumn(1, 0,"-: change password");
	/* the following while loop is for waiting till the user enter one of two characters *
	 * '-' or '+' not any other character.                                               */
	while(1)
	{
		if((KEYPAD_getPressedKey()=='-')||(KEYPAD_getPressedKey()=='+'))
			break;
	}
	return KEYPAD_getPressedKey();
}

/*
 * input: password array pointer and the chosen character from the main menu
 * return: void
 * Description: it asks the user to reenter the password then compare it with the saved password
 * then we have here two situations:
 * 1. the password that the user enters matches the saved one then the function will
 * 	  do one of two things:
 * 	  a. open the door
 * 	  b. change the password
 * 	  and this depends on the choice that is passed to this function
 * 	  at the same moment this function will send the chosen character to the CONTROL_ECU
 * 	  to make it open the door or to save the new password.
 *
 * 2. the 2 passwords don't match then the function will ask the user again to enter the
 *    right one if he does it will perform the first situation if n't till 3 times asking
 *    him to enter the correct one it will displays the " error message " for one minute.
 */
void HMI_openOrError (uint8* const pass_ptr , uint8 main_menu_choice)
{
	uint8 check = 0 , count = 0 , end_key = 0;
	LCD_clearScreen();
	LCD_displayString("please reenter the password:");
	LCD_moveCursor(1, 0);
/*******************************************/
	/* this do..while loop is for taking the password from user and send it to the             *
	 * CONTROL_ECU to compare it with the saved one to see if it matches or not if it matches  *
	 * then the CONTROL_ECU will send nothing but if it doesn't match it will send "wrong"     *
	 * which is a character defined in the .h file then it will loop if it is receiving        *
	 * the "wrong" character for three times then it will change the value of "check" variable *
	 * to 1 then it will stop looping.                                                         */
	do{
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		_delay_ms(1500);
		pass_ptr[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
	}
	while(1)
	{
		end_key = KEYPAD_getPressedKey();
		if(end_key == '=')
			break;
	}
	HMI_sendPassword(pass_ptr);
	while(UART_receiveByte() != ready){}
	/* here if it receives "wrong" it will assign the "check" variable by 1 then displays the *
	 * message below.                                                                         */
	if(UART_receiveByte() == wrong)
	{
		check = 1;
		count++;
		if(count == 3)
		{
			break;
		}
		LCD_clearScreen();
		LCD_displayString("the password is wrong please");
		LCD_displayStringRowColumn(1, 0, "try again: ");
	}
	/* if it didn't receive the "wrong" character then it will assign the "check" value again *
	 * to 0 then break the loop.                                                              */
	else
	{
		check = 0 ;
		break;
	}
	}while((check == 1) && (count<3));
/*******************************************/
	/* checking if the "check" value equals 1 that means it will display the error message for
	 * */
	if((count == 3)&&(check==1))
	{
		/* error_configuration is a configuration for the TIMER driver:     *
		 * timer_id , timer_mode , TCNT , OCR , used technique , pre-scaler */
		TIMER_configType error_configuration = {timer1, TIMER1_CTC , 0 , 65535 ,interrupt , FCPU_1024};
		LCD_clearScreen();
		/* setting the errorMessage as a call back function*/
		TIMER_setCallBack(HMI_errorMessage);
		/* initializing the TIMER by passing the previous structure to it. */
		TIMER_init(&error_configuration);
		LCD_displayString("move away or i will call the");
		LCD_displayStringRowColumn(1, 0, "Police!");
		/* waiting till it becomes a minute displaying this message where each tick will take  *
		 * almost 8.4 seconds so approximately one minute = 7 ticks.                           */
		while(tick < 8){}
		/* after finishing the time assigning the tick value back again by 0 for the next counts*/
		tick = 0 ;
	}
	else
	{
		/* sending "ready" to make the CONTROL_ECU wait to send the main_menu_choice */
		UART_sendByte(ready);
		/* sending the '+' or '-' choice */
		UART_sendByte(main_menu_choice);
		/* configuration is a structure of 'TIMER_configType' type:         *
		 * timer_id , timer_mode , TCNT , OCR , used technique , pre-scaler */
		TIMER_configType configuration = {timer1, TIMER1_CTC , 0 , 7813 ,interrupt , FCPU_1024};
		/* checking if the choice is '+' or '-' (i.e. open the door or change the password)*/
		if(main_menu_choice == '+')
		{
			LCD_clearScreen();
			/* setting the call back function to the 'HMI_openingdoor' function. */
			TIMER_setCallBack(HMI_openingdoor);
			/* initializing the TIMER driver by passing the configuration. */
			TIMER_init(&configuration);
			LCD_clearScreen();
			LCD_displayString("the door is opening...");
			/* waiting till the 15 seconds is up as the tick here is almost 1 second*/
			while(tick<=15){}
			LCD_clearScreen();
			LCD_displayString("the door is opened");
			/* waiting till another 3 seconds is up*/
			while(tick<=18){}
			LCD_clearScreen();
			LCD_displayString("the door is closing...");
			/* waiting till another 15 seconds is up*/
			while((tick<=33)&&(tick!=0)){}
			LCD_clearScreen();
		}
		else if(main_menu_choice == '-')
		{
			/* here it will call the function that is responsible for changing the password. */
			HMI_firstTimeOrChangePassword(pass_ptr);
			/* then it will send the password to the CONTROL_ECU to save it. */
			HMI_sendPassword(pass_ptr);
		}
	}
}

/* input: void
 * return: void
 * Description: it is the function that is called back by the TIMER driver to check if the tick
 * reaches 8 which means that the 1 minute of displaying the error message is up then it will
 * stop the timer from counting.
 */
void HMI_errorMessage (void)
{
	if(tick==8)
	{
		TIMER_deInit();
	}
}

/* input: void
 * return: void
 * Description: it is the function that is called back by the TIMER driver to check if the tick
 * reaches 34 which means that the time of displaying the door status is up then it will
 * stop the timer from counting.
 */
void HMI_openingdoor (void)
{
	if(tick>33)
	{
		TIMER_deInit();
		tick = 0;
	}
}



