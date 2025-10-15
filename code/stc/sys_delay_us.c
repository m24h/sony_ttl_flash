#include "sys.h"

#define NOP1 nop
#define NOP2 NOP1 \
			 NOP1
#define NOP4 NOP2 \
			 NOP2
#define NOP8 NOP4 \
             NOP4
#define NOP16 NOP8 \
              NOP8
#define NOP32 NOP16 \
              NOP16

void sys_delay_us(uint16_t us) __naked
{
	us; 
	__asm
	inc dpl
	inc dph
00010$:
#if FOSC/1000000>=6
	djnz dpl, 00011$
	djnz dph, 00011$
	ret
00011$:
#if (FOSC/1000000-6) & 0x01
	NOP1
#endif
#if (FOSC/1000000-6) & 0x02
	NOP2
#endif
#if (FOSC/1000000-6) & 0x04
	NOP4
#endif
#if (FOSC/1000000-6) & 0x08
	NOP8
#endif
#if (FOSC/1000000-6) & 0x10
	NOP16
#endif
#if (FOSC/1000000-6) & 0x20
	NOP32
#endif
	sjmp 00010$
#elif FOSC/1000000>=3
#if (FOSC/1000000-3) & 0x01
	NOP1
#endif	
#if (FOSC/1000000-3) & 0x02
	NOP2
#endif
	djnz dpl, 00010$
	djnz dph, 00010$
	ret	
#else 
#error FOSC is too low for this algorithm
#endif	
	__endasm;
}

