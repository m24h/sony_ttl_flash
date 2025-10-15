#include "tmr.h"

uint16_t tmr0_get(void) __naked
{
	__asm 
	mov c, _TR0
	clr _TR0
	nop
	mov dph, _TH0
	mov dpl, _TL0
	mov _TR0, c
	ret
	__endasm;
}
