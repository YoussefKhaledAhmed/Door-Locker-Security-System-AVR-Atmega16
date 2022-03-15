/*-------------------------------------------------------
 * [FILE NAME]: dc_motor.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 14/10/2021
 *
 * [DESCRIPTION]: header file for the DC_MOTOR_DRIVER
 -------------------------------------------------------*/


#include "dc_motor.h"
//#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>

/*
 * Description:
 * this function is to set the two pins (pin0 , pin1) at portB where the motor is connected through the H-bridge
 * to turn on and control the direction of the motor
 */
void DCMotor_init(void)
{
	/* setting the direction of the two required pins as OUTPUT pins */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);

	/* writing zeros on the two pins to initially stop the motor */
	GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
}

/*
 * function arguments: state , speed
 * output: void
 * Description:
 * this function is to set the direction of the motor by checking if it's clock-wise
 * or Anti clock-wise or to stop the motor .
 * then, passing the required speed to the PWM function to generate the corresponding digital signal
 * through the pin " PB3" where the EN1 pin of the H-bridge is connected which therefore
 * control the speed of the motor.
 */
void DCMotor_rotate(DcMotor_State state,uint8 speed)
{
	if (state == CW)/* checking if the required state is clock-wise */
	{
		/* setting pin0 and clearing pin1*/
		GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_HIGH);
		GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_LOW);
	}
	else if (state == A_CW)/* checking if the required state is Anti clock-wise */
	{
		/* clearing pin0 and setting pin1*/
		GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_HIGH);
	}
	else if(state == STOP)/* checking if the required state is STOP */
	{
		/* clearing both pin0 & pin1 */
		GPIO_writePin(PORTD_ID, PIN6_ID, LOGIC_LOW);
		GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_LOW);

		/* note: it can be done by setting both pin0 & pin1 *
		 * GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);    *
		 * GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);    */
	}
	/* passing the speed to the PWM function to out the required analog signal through PB3 pin */
//	PWM_Timer0_Start(speed);
}
