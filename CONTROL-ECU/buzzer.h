/*
 *
 *
 *
 *
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"


#define BUZZER_CTRL_PORT PORTD_ID
#define BUZZER_PIN PIN3_ID

void BUZZER_init (void);
void BUZZER_on (void);
void BUZZER_off (void);

#endif /* BUZZER_H_ */
