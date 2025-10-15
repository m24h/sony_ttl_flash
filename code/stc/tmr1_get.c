#include "tmr.h"

uint16_t tmr1_get(void) __naked
{
	__asm 
	mov c, _TR1
	clr _TR1
	nop
	mov dph, _TH1
	mov dpl, _TL1
	mov _TR1, c
	ret
	__endasm;
}