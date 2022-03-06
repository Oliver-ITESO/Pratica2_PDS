/*
 * Delay.h
 *
 *  Created on: 11 feb. 2021
 *      Author: LUISPIZANO
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include "Bits.h"
#include "PIT.h"


#define SYSTEM_CLOCK (21000000U)


void delay(uint16_t delay);
void configure_delay(My_float_pit_t delay);
boolean_t DelayCompleted(void);


void DelayStatusClear(void);

void DelayStatus(void);

void DelayReset(void);
#endif /* DELAY_H_ */
