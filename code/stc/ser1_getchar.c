#include "ser.h"

int ser1_getchar(void) __naked
{
	__asm
#if SER_FOR_STDIO==1
	.globl _getchar
_getchar:
#endif		
	jbc	_RI, 00010$
	mov	dptr, #(0XFFFF)
	ret
00010$:
	mov	dpl, _SBUF
	mov	dph, #0x00
	ret
	__endasm;		
}
