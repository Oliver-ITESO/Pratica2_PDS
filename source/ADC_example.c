/*
 * ADC_example.c
 *
 *  Created on: Mar 1, 2022
 *      Author: Oliver Rodea
 */
#include "ADC_example.h"
#include "MK64F12.h"

	void initADC(void)
	{
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
		ADC0->CFG1 = ADC_CFG1_MODE(1);
	}

	uint16_t ADC0_read(void) {
		uint16_t adcData;
		ADC0->SC1[0] = ADC_SC1_ADCH(12); //PTB2 tarjeta, ADC0SE12
		while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0);
			adcData = ADC0->R[0];
		return (adcData);
	}
