/*-------------------------------------------------------
 * [FILE NAME]: dc_motor.c
 *
 * [AUTHOR]: YOUSEF KHALED
 *
 * [DATE CREATED]: 14/10/2021
 *
 * [DESCRIPTION]: source file for the DC_MOTOR_DRIVER
 -------------------------------------------------------*/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

typedef enum
{ STOP , CW , A_CW }DcMotor_State;

/*------------------------------------*
 *        functions prototypes        *
 *------------------------------------*/

void DCMotor_init(void);
void DCMotor_rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
