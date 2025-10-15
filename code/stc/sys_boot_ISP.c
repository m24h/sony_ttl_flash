#include "sys.h"

void sys_boot_ISP(void) __naked
{
	__asm
	; reboot to download mode
	mov _IAP_CONTR, #(SWBS | SWRST)
00010$:
	; not to return
	sjmp 00010$;
	__endasm;
}




