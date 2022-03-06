/*
 * Delay.c
 *
 *  Created on: 11 feb. 2021
 *      Author: LUISPIZANO
 */
#include <stdint.h>
#include "PIT.h"
#include "Bits.h"
#include "Delay.h"
#include "NVIC.h"

boolean_t g_Delay_status = FALSE;
boolean_t DelayCompleted(void)
{
	return g_Delay_status;
}
void delay(uint16_t delay)
{
	volatile uint16_t j;

	for(j = delay; j > 0; j--)
	{
		__asm("nop");

	}
}
void configure_delay(My_float_pit_t delay)
{
	PIT_clock_gating();
	PIT_enable();
	PIT_enable_interrupt(PIT_0);

	PIT_delay(PIT_0, SYSTEM_CLOCK, delay);
	PIT_callback_init(PIT_0,DelayStatus);
}


void DelayStatusClear(void)
{
	g_Delay_status = FALSE;
}

void DelayStatus(void)
{
	g_Delay_status = TRUE;
}

void DelayReset(void)
{
	PIT_reset(PIT_0);
	g_Delay_status = TRUE;
}
