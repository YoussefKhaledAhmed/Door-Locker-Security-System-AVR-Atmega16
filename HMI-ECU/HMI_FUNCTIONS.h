/*-----------------------------------------------------------------
 * [FILE NAME]: HMI_FUNCTIONS.h
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 31/10/2021
 *
 * [DESCRIPTION]: header file for FUNCTIONS used in HMI-ECU
 ------------------------------------------------------------------*/

#ifndef HMI_FUNCTIONS_H_
#define HMI_FUNCTIONS_H_

#include "std_types.h"

#define ready 1
#define right 2
#define wrong 3
#define theif 4
#define opendoor 5

/*******************************************************
 *              functions prototype                    *
 *******************************************************/
void HMI_init (void);
void HMI_firstTimeOrChangePassword (uint8* const pass_ptr);
void HMI_sendPassword (uint8* const pass_ptr);
uint8 HMI_mainMenu (void);
void HMI_openOrError (uint8* const pass_ptr , uint8 main_menu_choice);
void HMI_errorMessage(void);
void HMI_openingdoor (void);
void HMI_doorHold (void);
void HMI_doorClose (void);



#endif /* HMI_FUNCTIONS_H_ */
