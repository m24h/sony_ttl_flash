#include "adc.h"

uint16_t adc_ref_mv_cid(void) __naked
{
	__asm
	mov	    dptr, #_CHIPID7
	movx	a, @dptr
	push    acc
	inc	    dptr
	movx	a, @dptr
	mov     dpl, a
	pop     dph
	ret
	__endasm;
}
