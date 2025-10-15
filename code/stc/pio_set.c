#include "pio.h"

static void dummy(__bit value) __reentrant __naked
{
	value;
	__asm
	; sdcc does not generate this for __bit parameters automatically when __naked 
	.area BIT_BANK	(REL,OVR,DATA)
bits:
	.ds 1
	b0 = bits[0]
	b1 = bits[1]
	b2 = bits[2]
	b3 = bits[3]
	b4 = bits[4]
	b5 = bits[5]
	b6 = bits[6]
	b7 = bits[7]
	
	.area CSEG    (CODE)
	__endasm;
}

void pio_set(uint16_t addr, __bit value) __reentrant __naked
{
	addr;
	value;
	
	__asm
	jb b0, 00011$  ; if value!=0
	xrl dpl, #0xFF ; inversed
	push dpl
	mov a, dph
	rl a
	rl a
	add a, dph	
	mov	dptr, #00010$		
	jmp	@a+dptr
00010$:
	pop acc
	anl _P0, a
	ret
	pop acc
	anl _P1, a
	ret		
	pop acc
	anl _P2, a
	ret		
	pop acc
	anl _P3, a
	ret		
	pop acc
	anl _P4, a
	ret		
	pop acc
	anl _P5, a
	ret		
	pop acc
	anl _P6, a
	ret		
	pop acc
	anl _P7, a
	ret		
00011$:
	push dpl
	mov a, dph
	rl a
	rl a
	add a, dph	
	mov	dptr, #00012$
	jmp	@a+dptr
00012$:
	pop acc
	orl _P0, a
	ret
	pop acc
	orl _P1, a
	ret		
	pop acc
	orl _P2, a
	ret		
	pop acc
	orl _P3, a
	ret		
	pop acc
	orl _P4, a
	ret		
	pop acc
	orl _P5, a
	ret		
	pop acc
	orl _P6, a
	ret		
	pop acc
	orl _P7, a
	ret		
	__endasm;		
}
