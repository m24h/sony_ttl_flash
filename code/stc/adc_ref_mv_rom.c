#include "adc.h"
#include "mem.h"

uint16_t adc_ref_mv_rom(void) __naked
{
	__asm
	mov dptr, #(MEM_ROM_SIZE-9)
	clr a
	movc a,@a+dptr
	push acc
	inc	dptr
	clr a
	movc a,@a+dptr
	mov dpl,a
	pop dph
	ret
	__endasm;
}
