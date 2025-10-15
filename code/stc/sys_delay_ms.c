#include "sys.h"

void sys_delay_ms(uint16_t ms) __naked
{
	ms; 
	__asm
	inc dpl
	inc dph
00010$:	
	djnz dpl, 00011$
	djnz dph, 00011$
	ret
00011$:
	; FOSC should not have postfix like 'UL'
	__endasm;
	// sdas8051 seems to use signed 24-bit value when calculating const expressions, FOSC then become overflowed.
	ACC = (FOSC/3008)>>8;
	B = (FOSC/3008)&0xFF;
	__asm
00012$: 
	djnz b, 00012$ 
	djnz acc, 00012$
	sjmp 00010$
	__endasm;
}
