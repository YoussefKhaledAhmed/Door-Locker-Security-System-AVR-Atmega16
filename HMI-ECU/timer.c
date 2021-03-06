/*-------------------------------------------------------
 * [FILE NAME]: timer.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 24/10/2021
 *
 * [DESCRIPTION]: source file for AVR timer driver
 -------------------------------------------------------*/

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h> /* For timer ISR */


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

uint8 tick = 0;

ISR (TIMER0_OVF_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER0_COMP_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER1_OVF_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER1_COMPA_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER1_COMPB_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER2_OVF_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


ISR (TIMER2_COMP_vect)
{
	tick++;
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


/*
 * input: pointer to structure of TIMER_configType type
 * return: void
 * Description: initializing the TIMER driver as desired in the passed structure
 */
void TIMER_init (const TIMER_configType* config_ptr )
{
	/*******************************************************************************************************
	 *        configuring the control register(TCCR) & timer register(TCNT) & compare register(OCR)        *
	 *                              & interrupt mask register(TIMSK)                                       *
	 *******************************************************************************************************/

	/******************************
	  if timer0 is the chosen one
	 ******************************/
	if ((config_ptr-> TIMER_ID) == timer0)
	{
		/* initializing timer0 register TCNT0 */
		TCNT0 = config_ptr -> TCNT_INITIAL;

		/* configuring the chosen clock as the cs02:0 are the first 3 bits */
		TCCR0 = (config_ptr -> TIMER_CLOCK) | (1<<FOC0);

		/* configuring the timer mode.                            *
		 * where in NORMAL mode: WGM01:0 are cleared both         *
		 * while in CTC mode: WGM01:0 = 2 & also OCR0 is assigned */
		if ((config_ptr -> TIMER_MODE) == TIMER0_CTC) /* (i.e. if the used mode is compare mode) */
		{
			/* assigning the value from the passed structure in the OCR0*/
			OCR0 = (config_ptr -> TIMER_CTC_REG);

			/* (2)(decimal) = (10)(binary) (WGM01 WGM00) = (1 0) */
			TCCR0 |= (1<<WGM01);

			/* checking on the desired technique (i.e. polling or interrupt) but for the CTC mode */
			if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
			{
				/* setting the OCIE0 bit (timer0 output compare match interrupt enable)  */
				TIMSK = (1 << OCIE0);
			}
		}
		else /* (i.e. if the used mode is NORMAL mode)*/
		{
			/* checking on the desired technique (i.e. polling or interrupt) but for the NORMAL mode */
			if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
			{
				/* setting the TOIE0 bit (timer0 overflow interrupt enable) */
				TIMSK = (1 << TOIE0);
			}
		}
	}

	/*******************************************************************************************************/

	/*******************************
	   if timer1 is the chosen one
	 *******************************/
	if((config_ptr -> TIMER_ID) == timer1)
	{
		/* initializing timer1 register TCNT1 */
		TCNT1 = config_ptr -> TCNT_INITIAL;

		/* configuring the chosen clock as the cs12:0 are the first 3 bits */
		TCCR1B = (config_ptr -> TIMER_CLOCK);

		/* setting FOC1A & FOC1B as we aren't working through PWM mode */
		TCCR1A = 12;

		/* configuring the timer mode.                             *
		 * where in NORMAL mode: WGM13:0 are all cleared           *
		 * while in CTC mode: WGM13:0 = 4 & also OCR1 is assigned  */
		if ((config_ptr -> TIMER_MODE) == TIMER1_CTC)
		{
			/* assigning the value from the passed structure in the OCR1A*/
			OCR1A = (config_ptr -> TIMER_CTC_REG);

			/* 4 = 1 0 0  which means (WGM13 WGM12 WGM11 WGM10) = (0100)*/
			TCCR1B |= (1<<WGM12);

			/* checking on the desired technique (i.e. polling or interrupt) but for the CTC mode */
			if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
				{
					/* setting the OCIE1A bit (timer1 output compare A match interrupt enable)  */
					TIMSK = (1 << OCIE1A);
				}
			}
			else /* (i.e. if the used mode is NORMAL mode)*/
			{
				/* checking on the desired technique (i.e. polling or interrupt) but for the NORMAL mode */
				if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
				{
					/* setting the TOIE1 bit (timer1 overflow interrupt enable) */
					TIMSK = (1 << TOIE1);
				}
			}
	}
	/*******************************************************************************************************/

	/******************************
	  if timer2 is the chosen one
	 ******************************/
	if ((config_ptr-> TIMER_ID) == timer2)
	{
		/* initializing timer2 register TCNT2 */
		TCNT2 = config_ptr -> TCNT_INITIAL;

		/* configuring the chosen clock as the cs22:0 are the first 3 bits */
		TCCR2 = (config_ptr -> TIMER_CLOCK) | (1<<FOC2);

		/* configuring timer2 mode.                               *
		 * where in NORMAL mode: WGM21:0 are cleared both         *
		 * while in CTC mode: WGM21:0 = 2 & also OCR1 is assigned */
		if ((config_ptr -> TIMER_MODE) == TIMER2_CTC)
		{
			/* assigning the value from the passed structure in the OCR2*/
			OCR2 = (config_ptr -> TIMER_CTC_REG);

			/* (2)(decimal) = (10)(binary) (WGM21 WGM20) = (1 0) */
			TCCR2 |= (1<<WGM21);

			/* checking on the desired technique (i.e. polling or interrupt) but for the CTC mode */
			if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
			{
				/* setting the OCIE2 bit (timer2 output compare match interrupt enable)  */
				TIMSK = (1 << OCIE2);
			}
		}
		else /* (i.e. if the used mode is NORMAL mode)*/
		{
			/* checking on the desired technique (i.e. polling or interrupt) but for the NORMAL mode */
			if((config_ptr -> TIMER_TECHNIQUE) == interrupt)
			{
				/* setting the TOIE2 bit (timer2 overflow interrupt enable) */
				TIMSK = (1 << TOIE2);
			}
		}
	}
}


void TIMER_setCallBack (void*a_ptr(void))
{
	g_callBackPtr = a_ptr;
}

void TIMER_deInit (void)
{
	TCCR0 = 0;
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR2 = 0;
	TCNT0 = 0;
	TCNT1 = 0;
	TCNT2 = 0;
	TIMSK = 0;
	OCR0 = 0;
	OCR1A = 0;
	OCR1B = 0;
	OCR2 = 0;
}

























