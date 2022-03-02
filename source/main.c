/**
 * @file    Convolution.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

/* TODO: insert other include files here. */

#include "ADC_example.h"
#include "DAC_example.h"

#include "Convolution.h"
#include "GPIO.h"

/*#define NO_CHANGES 	0
#define IMP_RES1	1
#define IMP_RES2	2*/
#define delay_switch 1000

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	volatile uint16_t au_input;

	typedef enum {NO_CHANGES, IMP_RES1, IMP_RES2}select_conv;

	select_conv conv_status = NO_CHANGES;

	volatile float volume = 1;

	uint32_t output;

	initSwitch(SW2);
	initSwitch(SW3);
	initADC();
	initDAC();

    while(1) {
    	ADC_read();
    	sw2_status = switchRead(SW2);
    	delay(delay_switch);
    	sw3_status = switchRead(SW3);

    	if(ON == sw2 && ON == sw1)
    	{
    		conv_status++;
    	}
    	else if(ON == sw2)
		{
    		volume = volumeUp(volume);
    	}
    	else if(ON == sw3)
		{
    		volume = volumeDown(volume);
		}
    	output = ampli(conv(select_conv),volume);
    	DAC_output(output);
   }
    return 0 ;
}
