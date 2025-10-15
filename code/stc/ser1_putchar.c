#include "ser.h"

int ser1_putchar (int c) __naked
{
	c; // stored in dph/dpl
	__asm
#if SER_FOR_STDIO==1
	.globl _putchar
_putchar:
#endif
00010$:
	jbc	_TI, 00011$
	sjmp 00010$
00011$:
	mov	_SBUF, dpl		
	ret
	__endasm;
}

