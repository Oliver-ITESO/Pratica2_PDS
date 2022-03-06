/**
 * @file    Convolution.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MK64F12.h"

/* TODO: insert other include files here. */

#include "ADC_example.h"
#include "DAC_example.h"

#include "Convolution.h"
#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#include "Delay.h"
#include "Bits.h"

/*#define NO_CHANGES 	0
#define IMP_RES1	1
#define IMP_RES2	2*/
#define SYSTEM_CLOCK (21000000U)
#define DELAY_SWITCH 1000
#define SAMPLING_FREQUENCY (1/22050)
#define SIZE_ARRAY 7



typedef enum {NO_CHANGES, IMP_RES1, IMP_RES2} select_conv;

/* TODO: insert other definitions and declarations here. */
void flag_SW3(void);
void flag_SW2(void);
volatile float volumeUp(volatile float volume);
volatile float volumeDown(volatile float volume);

const float g_h1[SIZE_ARRAY] = { -0.1050, -0.1448, -0.1721, 0.8182, -0.1721, -0.1448, -0.1050};
const float g_h2[SIZE_ARRAY] = { 0.0802, 0.0860, 0.0897, 0.0909, 0.0897, 0.0860, 0.0802};

uint32_t ampli(uint32_t conv_out,volatile float volume);

uint32_t conv(select_conv conv_status, volatile uint16_t signalIn);

/*
 * @brief   Application entry point.
 */
boolean_t SW3_status = TRUE;
boolean_t SW2_status = TRUE;
boolean_t g_ISR_flag_PIT0 = FALSE;

int main(void) {
	uint32_t output;

	volatile uint16_t ADC_out;

	select_conv conv_status = NO_CHANGES;

	volatile float volume = 1;

	GPIO_configure_switches();

	GPIO_callback_init(SW3_PORT, flag_SW3);

	GPIO_callback_init(SW2_PORT, flag_SW2);

	PIT_clock_gating();
	PIT_enable();
	PIT_enable_interrupt(PIT_0);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_4);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_5);
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5);

	NVIC_global_enable_interrupts;
	PIT_delay(PIT_0, SYSTEM_CLOCK, SAMPLING_FREQUENCY);

	initADC();
	initDAC();

    while(1) {

    	if(g_ISR_flag_PIT0)
    	{
    		ADC_out = ADC0_read();
    		g_ISR_flag_PIT0 = FALSE;
    	}
    	delay(DELAY_SWITCH);

    	if(!SW3_status && !SW2_status)
    	{
    		conv_status++;
    	}
    	else if(!SW2_status)
		{
    		volume = volumeUp(volume);
    	}
    	else if(!SW3_status)
		{
    		volume = volumeDown(volume);
		}
    	else
    	{

    	}

    	output = ampli(conv(conv_status,ADC_out),volume);

		DAC0->DAT[0].DATL = (uint16_t) output & 0xFF;
		DAC0->DAT[0].DATH = (uint16_t) ((output >> 8) & 0x0F);
   }
    return 0 ;
}

/**Func from callback to set SW3 flag*/
void flag_SW3(void)
{
	SW3_status = FALSE;
	/**firstIntFlag = TRUE;*/
}
/**Func from callback to set SW2 flag*/
void flag_SW2(void)
{
	SW2_status = FALSE;
	/**firstIntFlag = TRUE;*/
}

volatile float volumeUp(volatile float volume)
{
	return(volume+0.1);
}

volatile float volumeDown(volatile float volume)
{
	return(volume-0.1);
}

uint32_t conv(select_conv conv_status, volatile uint16_t signalIn)
{
	uint16_t back = 0;
	static float shiftArray[SIZE_ARRAY] = { };
	uint32_t i = 0;

	if (NO_CHANGES == conv_status)
	{

		back = signalIn;
	}

	else if(IMP_RES1 == conv_status)
	{
		for ( i = SIZE_ARRAY-1; i > 0; i--)
		{
			shiftArray[i] = shiftArray[i - 1];
		}
		shiftArray[0] = signalIn;
		for (i = 0; i < SIZE_ARRAY; i++)
		{
			back += (shiftArray[i] * g_h1[SIZE_ARRAY - i]);
		}
	}
	else if(IMP_RES2 == conv_status) {

		for (uint8_t i = (SIZE_ARRAY-1); i > 0; i--)
		{
			shiftArray[i] = shiftArray[i - 1];
		}
		shiftArray[0] = signalIn;
		//Operación de la convolución
		for (i = 0; i < SIZE_ARRAY; i++)
		{
			back += (shiftArray[i] * g_h2[SIZE_ARRAY - i]);
		}
	}
	return back;
}

uint32_t ampli(uint32_t conv_out,volatile float volume)
{
	return (conv_out*volume);
}
