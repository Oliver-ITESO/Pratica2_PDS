#include "MK64F12.h"


void initDAC(void){

	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
	DAC0->C0 = 0xC0;
	DAC0->DAT[0].DATL = 0;
	DAC0->DAT[0].DATH = 0;
}
