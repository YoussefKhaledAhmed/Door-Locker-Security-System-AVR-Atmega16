/*
 * buzzer.c
 *
 *  Created on: Nov 3, 2021
 *      Author: youss
 */

#include "buzzer.h"
#include "gpio.h"

void BUZZER_init (void)
{
	GPIO_setupPinDirection(BUZZER_CTRL_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_CTRL_PORT, BUZZER_PIN, LOGIC_LOW);
}

void BUZZER_on (void)
{
	GPIO_writePin(BUZZER_CTRL_PORT, BUZZER_PIN, LOGIC_HIGH);
}

void BUZZER_off (void)
{
	GPIO_writePin(BUZZER_CTRL_PORT, BUZZER_PIN, LOGIC_LOW);
}
