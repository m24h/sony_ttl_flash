#include "pio.h"

__bit pio_get(uint16_t addr) __naked
{
	addr;
	__asm
	mov a, dph
	rl a
	rl a
	push dpl
	mov	dptr, #00010$
	jmp	@a+dptr
00010$:
	mov	a, _P0
	sjmp 00011$		
	mov	a, _P1
	sjmp 00011$		
	mov	a, _P2
	sjmp 00011$		
	mov	a, _P3
	sjmp 00011$		
	mov	a, _P4
	sjmp 00011$		
	mov	a, _P5
	sjmp 00011$		
	mov	a, _P6
	sjmp 00011$		
	mov	a, _P7
00011$:
	pop dpl
	anl a, dpl
	add a, #0xFF
	ret
	__endasm;	
}
