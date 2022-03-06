/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * @file    PIT.c
 * @brief   Application entry point.
 *
 * 	\author Axel Ramirez Herrera, ie727589@iteso.mx
	\author Oliver Rodea Aragon,  ie727549@iteso.mx
	\date	17/09/2018
 */
#include <stdio.h>
#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"
#include "GPIO.h"

uint8_t g_ISR_flag_PIT0 = FALSE;
static void (*pit_0_callback)(void) = 0;
/*
 * This function sets the time that PIT will count to send an interrupt
 * The time is calculated with the system clock 21MHz and the time in seconds (delay)
 * Notice that PIT clock is 10.5 MHz*/
void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay){

	My_float_pit_t PIT_register_value = (delay*(system_clock/2.0f));
	PIT->CHANNEL[pit_timer].LDVAL = (uint32_t)PIT_register_value;
	//PIT_enable_interrupt(pit_timer);
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN(1);
}
/*
 * This function set on the clock of PIT*/
void PIT_clock_gating(void){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}
/*
 * This functions gives the flag status of the interruption
*/
uint8_t PIT_get_interrupt_flag_status(void){
	return g_ISR_flag_PIT0;
}
/*
 *This function ISR sets a flag to let know when the interruption show up
 *the last instruction reads control register for clear PIT flag, this is silicon bug*/
void PIT0_IRQHandler(void)
{
	if(pit_0_callback)
	{
		pit_0_callback();
	}
	g_ISR_flag_PIT0 = TRUE;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	uint32_t dummyRead = PIT->CHANNEL[0].TCTRL;
}
/*
 * This functions clears the flag seted by the interruption*/
void PIT_clear_interrupt_flag(void)
{
	g_ISR_flag_PIT0 = FALSE;
}
/*
 * This function enables the interruption of the PIT*/
void PIT_enable_interrupt(PIT_timer_t pit){

	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK;

}
/*This function enables the PIT Module*/
void PIT_enable(void){
	PIT->MCR = 0;
}

void PIT_callback_init(PIT_timer_t pit,void (*handler)(void))
{
	if(PIT_0 == pit)
	{
		pit_0_callback = handler;
	}
}

void PIT_reset(PIT_timer_t pit)
{
	PIT->CHANNEL[pit].TCTRL &= ~PIT_TCTRL_TEN(1);

	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TEN(1);
}
