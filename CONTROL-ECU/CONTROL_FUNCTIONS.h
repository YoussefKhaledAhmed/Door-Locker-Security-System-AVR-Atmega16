/*-----------------------------------------------------------------
 * [FILE NAME]: CONTROL_FUNCTIONS.h
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 31/10/2021
 *
 * [DESCRIPTION]: header file for FUNCTIONS used in CONTROL-ECU
 ------------------------------------------------------------------*/

#ifndef CONTROL_FUNCTIONS_H_
#define CONTROL_FUNCTIONS_H_

#include "std_types.h"

#define ready 1
#define right 2
#define wrong 3
#define theif 4
#define opendoor 5

void CONTROL_init (void);
void CONTROL_receiveThePassword (uint8* const pass_ptr);
void CONTROL_savePassword (const uint8* const pass_ptr);
void CONTROL_checkPassword (uint8* const pass_ptr);
void HMI_sendPassword (uint8* const pass_ptr);
void CONTROL_buzzer (void);
void CONTROL_openingdoor (void);

#endif /* CONTROL_FUNCTIONS_H_ */
