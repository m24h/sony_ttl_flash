#include "pio.h"

void pio_config(uint16_t addr, uint8_t mode) __reentrant __naked
{
	addr;
	mode;
	
	__asm
	ar0 = 0x00
	ar6 = 0x06
	ar7 = 0x07
	push ar7
	push ar6
	push ar0
	; b = mode
	mov a, sp
	add a, #0xfb
	mov r0, a
	mov b, @r0
	; if mode.bit0==1, r7=port bit-address, else r7=0
	; if mode.bit1==1, r6=port bit-address, else r6=0
	; r0 =~(port bit-address)
	clr a
	mov r7, a
	mov r6, a
	mov a, dpl
	jnb b.0, #00010$
	mov r7, a 
00010$:
	jnb b.1, #00011$
	mov r6, a  
00011$:
	cpl a
	mov r0, a
	; look up table and set mode
	push dph		
	mov a, dph
	rl a
	add a, dph
	rl a
	rl a
	add a, dph	; =dph*13
	mov	dptr, #00012$		
	jmp	@a+dptr
00012$:
	mov a, r0
	anl _P0M0, a
	anl _P0M1, a
	mov a, r7
	orl _P0M0, a
	mov a, r6
	orl _P0M1, a
	sjmp 00013$	
	mov a, r0
	anl _P1M0, a
	anl _P1M1, a
	mov a, r7
	orl _P1M0, a
	mov a, r6
	orl _P1M1, a
	sjmp 00013$	
	mov a, r0
	anl _P2M0, a
	anl _P2M1, a
	mov a, r7
	orl _P2M0, a
	mov a, r6
	orl _P2M1, a
	sjmp 00013$	
	mov a, r0
	anl _P3M0, a
	anl _P3M1, a
	mov a, r7
	orl _P3M0, a
	mov a, r6
	orl _P3M1, a
	sjmp 00013$	
	mov a, r0
	anl _P4M0, a
	anl _P4M1, a
	mov a, r7
	orl _P4M0, a
	mov a, r6
	orl _P4M1, a
	sjmp 00013$	
	mov a, r0
	anl _P5M0, a
	anl _P5M1, a
	mov a, r7
	orl _P5M0, a
	mov a, r6
	orl _P5M1, a
	sjmp 00013$	
	mov a, r0
	anl _P6M0, a
	anl _P6M1, a
	mov a, r7
	orl _P6M0, a
	mov a, r6
	orl _P6M1, a
	sjmp 00013$	
	mov a, r0
	anl _P7M0, a
	anl _P7M1, a
	mov a, r7
	orl _P7M0, a
	mov a, r6
	orl _P7M1, a
00013$:
	mov r7, ar0
	xrl ar7, #0xFF
	pop ar6 ; dph, port number
	; P?IE
	mov dptr, #_P0IE
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jb b.2, 00014$
	orl a, r7
00014$:
	movx @dptr, a
	; P?NCS
	mov dptr, #_P0NCS
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jb b.3, PIOCF08$
	orl a, r7
PIOCF08$:
	movx @dptr, a
	; P?PU
	mov dptr, #_P0PU
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jnb b.4, 00015$
	orl a, r7
00015$:
	movx @dptr, a
#if defined(MCU_STC8H)
	; P?PD
	mov dptr, #_P0PD
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jnb b.5, 00016$
	orl a, r7
00016$:
	movx @dptr, a
#endif
	; P?SR
	mov dptr, #_P0SR
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jb b.6, 00017$
	orl a, r7
00017$:
	movx @dptr, a
	; P?DR
	mov dptr, #_P0DR
	mov a, r6
	add a, dpl
	mov dpl, a
	clr a
	addc a, dph
	mov dph, a
	movx a, @dptr
	anl a, r0
	jb b.7, 00018$
	orl a, r7
00018$:
	movx @dptr, a
	;done	
	pop ar0
	pop ar6
	pop ar7
	ret
	__endasm;	
}
