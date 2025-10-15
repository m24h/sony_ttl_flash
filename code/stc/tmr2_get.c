#include "tmr.h"

uint16_t tmr2_get(void) __naked
{
	__asm 
	mov a, _AUXR 
	anl _AUXR, #(~T2R)
	anl a, #(T2R)
	mov dph, _T2H
	mov dpl, _T2L
	orl _AUXR, a
	ret
	__endasm;
}