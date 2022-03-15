/*-----------------------------------------------------------------
 * [FILE NAME]: CONTROL_FUNCTIONS.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 31/10/2021
 *
 * [DESCRIPTION]: source file for FUNCTIONS used in CONTROL-ECU
 ------------------------------------------------------------------*/

#include "uart.h"
#include "CONTROL_FUNCTIONS.h"
#include <util/delay.h>
#include "twi.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "timer.h"
#include "gpio.h"
#include "std_types.h"
#include "buzzer.h"

extern uint8 tick ;

/*
 * input: void
 * return: void
 * Description: initializing the UART driver
 */
void CONTROL_init (void)
{
	uart_config configuration = {EIGHT_BITS , DISABLED , ONE_BIT , 9600};
	UART_init(&configuration);
}

/*
 * input: password array pointer
 * return: void
 * Description: receiving the password from the HMI_ECU
 */
void CONTROL_receiveThePassword (uint8* const pass_ptr)
{
	while (UART_receiveByte() != ready){}
	UART_sendByte(ready);
	for(uint8 i = 0 ; i < 5 ; i++)
	{
		pass_ptr[i] = UART_receiveByte();
	}
}

/*
 * input: password array pointer
 * return: void
 * Description: saving the password at the EEPROM
 */
void CONTROL_savePassword (const uint8* const pass_ptr)
{
	I2C_config configuration = {400000 , 0x02};

	/* Initialize the TWI/I2C Driver */
	TWI_init(&configuration);

	for (uint8 i = 0 ; i < 5 ; i++)
	{
		EEPROM_writeByte(0x0311+i, pass_ptr[i]);
		_delay_ms(10);
	}
}

/*
 * input: password array pointer
 * return: void
 * Description: comparing the saved password with the one sent by the HMI_ECU if it is mismatching for
 * 3 times it will operate the buzzer if not it will receive the main_menu_choice from the HMI_ECU
 * if '+' then it will turn on the motor for 15 seconds then stop it for 3 seconds then turn it on
 * in the other direction for 15 seconds.
 */
void CONTROL_checkPassword (uint8* const pass_ptr)
{
	uint8 check_password[5]={} , check=0 , count = 0 , choice;
	for(uint8 j = 0 ; j < 5 ; j++)
	{
		EEPROM_readByte(0x0311+j , check_password+j);
	}
	do{

	CONTROL_receiveThePassword(pass_ptr);
	for(uint8 j = 0 ; j<5 ; j++)
	{
		if(pass_ptr[j] != check_password[j])
		{
			check = 1;
			count++;
			break;
		}
		else
		{
			check = 0;
		}
	}
	UART_sendByte(ready);
	(check == 1)?(UART_sendByte(wrong)):(UART_sendByte(right));

	}while((check == 1) && (count<3));
	if((count == 3)&&(check==1))
		{
			TIMER_configType error_configuration = {timer1, TIMER1_CTC , 0 , 65535 ,interrupt , FCPU_1024};
			TIMER_setCallBack(CONTROL_buzzer);
			TIMER_init(&error_configuration);
			BUZZER_init();
			BUZZER_on();
			while(tick < 8){}
			tick = 0 ;
		}
		else
		{
			while(UART_receiveByte() != ready);
			choice = UART_receiveByte();
			TIMER_configType configuration = {timer1, TIMER1_CTC , 0 , 7813 ,interrupt , FCPU_1024};
			if(choice == '+')
			{
				DCMotor_init();
				TIMER_setCallBack(CONTROL_openingdoor);
				TIMER_init(&configuration);

				DCMotor_rotate(CW, 100);
				while(tick<=15){}

				DCMotor_rotate(STOP, 0);
				while(tick<=18){}

				DCMotor_rotate(A_CW, 100);
				while((tick<=33)&&(tick!=0)){}
			}
			else if(choice == '-')
			{
				CONTROL_receiveThePassword(pass_ptr);
				CONTROL_savePassword(pass_ptr);
			}
		}
}

/* input: void
 * return: void
 * Description: it is the function that is called back by the TIMER driver to check if the tick
 * reaches 8 which means that the 1 minute of turning on the BUZZER is up then it will
 * stop the timer from counting.
 */
void CONTROL_buzzer (void)
{
	if(tick==8)
	{
		TIMER_deInit();
		BUZZER_off();
	}
}

/* input: void
 * return: void
 * Description: it is the function that is called back by the TIMER driver to check if the tick
 * reaches 34 which means that the time of opening then closing the door is up then it will
 * stop the timer from counting.
 */
void CONTROL_openingdoor (void)
{
	if(tick>33)
	{
		TIMER_deInit();
		DCMotor_rotate(STOP, 0);
		tick = 0;
	}
}
