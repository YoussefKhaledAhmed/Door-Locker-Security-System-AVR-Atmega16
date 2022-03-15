/*-------------------------------------------------------
 * [FILE NAME]: timer.h
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 24/10/2021
 *
 * [DESCRIPTION]: header file for AVR timer driver
 -------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/**************************************
 *        SOME DEFINITIONS            *
 **************************************/

/* TIMER_ID (i.e. which timer is used) */
typedef enum {
	timer0 , timer1 , timer2
}id;

/* timer_mode */
typedef enum{
	NORMAL , TIMER0_CTC , TIMER1_CTC , TIMER2_CTC
} mode;

/* methods of using the timers */
typedef enum{
	polling , interrupt
} technique;

/* clock of the timer */
typedef enum{
	no_clock , FCPU , FCPU_8 , FCPU_64 , FCPU_256 , FCPU_1024 , EXTERNAL_FALLING_EDGE , EXTERNAL_RISING_EDGE
} clock_source;


/* structure that will be used to configure the timer */
typedef struct{
	id TIMER_ID;
	mode TIMER_MODE;
	uint16 TCNT_INITIAL;
	uint16 TIMER_CTC_REG;
	technique TIMER_TECHNIQUE;
	clock_source TIMER_CLOCK;
} TIMER_configType;



/****************************************
 *        functions prototypes          *
 ****************************************/
void TIMER_init (const TIMER_configType*);
void TIMER_setCallBack (void*a_ptr(void));
void TIMER_deInit (void);


#endif /* TIMER_H_ */
