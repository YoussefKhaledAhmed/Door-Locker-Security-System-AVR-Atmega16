/*-------------------------------------------------------
 * [FILE NAME]: gpio.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 30/9/2021
 *
 * [DESCRIPTION]: source file for AVR GPIO driver
 -------------------------------------------------------*/
#include "avr/io.h"
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"


/*
 * Description :
 * the following functions are to setup the direction of the pins.
 * if the port or pin numbers are entered wrong then the function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num , uint8 pin_num , GPIO_PinDirectionType direction  )
{
	if((port_num > NUM_OF_PORTS ) || (pin_num > NUM_OF_PINS_PER_PORT))
	{
		/*Do nothing*/
	}
	else
	{
		/*setup the chosen pin as required*/
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break ;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);

			}
			break;
		case PORTC_ID:
			if(direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			else
			{
				SET_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
		}
	}
}
/*
 * Description:
 * Write the value of logic high or logic low on the required pin.
 * If the input port number or pin number are not correct the request will not be handled
 * if the pin is input, the function will enable/disable the pull-up resistor as required
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if((port_num > NUM_OF_PORTS) || (pin_num > NUM_OF_PINS_PER_PORT))
	{
		/*Do nothing*/
	}
	else
	{
		/*Write Logic one or Logic zero to the chosen pin*/
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			else
			{
				SET_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}
/*
 * Description:
 * Read and return the value of the required pin, it should be LOGIC_HIGH or LOGIC_LOW
 * If the input port number or pin number are not correct, the function will return logic low
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 readValue = 0 ;
	if((port_num > NUM_OF_PORTS) || (pin_num > NUM_OF_PINS_PER_PORT))
	{
		readValue = 0 ;
	}
	else
	{
		/*
		 * read the value of the chosen pin
		 */
		switch(port_num)
		{
		case PORTA_ID:
			/*
			 * BIT_IS_SET to check if the bit is set or not and shifting right the answer as we need
			 * to read only LOGI_HIGH (1) or LOGIC_LOW (0)
			 * if ((PINA = 00000010)&(1<<(pin_num=1)))>>(1) = 1
			 */
			readValue = (BIT_IS_SET(PINA,pin_num)>>pin_num) ;
			break;
		case PORTB_ID:
			/*
			 * here as what happened in PORTA
			 */
			readValue = ((BIT_IS_SET(PINB,pin_num)) >> pin_num) ;
			break;
		case PORTC_ID:
			/*
			 * here as what happened in PORTA
			 */
			readValue = ((BIT_IS_SET(PINC,pin_num)) >> pin_num) ;
			break;
		case PORTD_ID:
			/*
			 * here as what happened in PORTA
			 */
			readValue = ((BIT_IS_SET(PIND,pin_num)) >> pin_num) ;
			break;
		}
	}
	return readValue ;
}
/*
 * Description:
 * Write the value on the required port.
 * if any pin in the port is output pin the value will be written.
 * if any pin in the port is input pin then this will activate/deactivate the internal pull_up
 * resistor.
 * if the input port number is not correct, the function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if(port_num > NUM_OF_PORTS)
	{
		/*Do nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}
/*
 * Description:
 * write the value on the required port.
 * if any pin in the port is output pin the value will be written.
 * if any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * if the input port is not correct, the function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if(port_num > NUM_OF_PORTS)
	{
		/*Do Nothing*/
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value ;
			break;
		case PORTB_ID:
			PORTB = value ;
			break;
		case PORTC_ID:
			PORTC = value ;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}
/*
 * Description:
 * Read and return the value of the required port.
 * if the port number is not correct, the function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 readValue = 0 ;
	if(port_num > NUM_OF_PORTS)
	{
		return 0 ;
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			readValue = PINA;
			break;
		case PORTB_ID:
			readValue = PINB;
			break;
		case PORTC_ID:
			readValue = PINC;
			break;
		case PORTD_ID:
			readValue = PIND;
			break;
		}
	}
	return readValue ;
}

















