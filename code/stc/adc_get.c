#include "adc.h"

uint16_t adc_get(uint8_t chan) __naked
{
	chan; // stored in dpl
	__asm
	orl dpl, #(ADC_POWER | ADC_START)
	mov _ADC_CONTR, dpl
	nop
	nop
	nop
00010$:
	mov	a, _ADC_CONTR
	anl a, #(ADC_FLAG | ADC_START)
	cjne a, #(ADC_FLAG), 00010$
	anl _ADC_CONTR, #(~ADC_FLAG)
	mov dph, _ADC_RES
	mov dpl, _ADC_RESL
	ret
	__endasm;
}