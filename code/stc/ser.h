#ifndef __SER_H__
#define __SER_H__

#include "def.h"

// defaultly, serial port 1 will be used for putchar()/getchar() used by stdio.h, set it to 0 to cancel this feature.
#ifndef SER_FOR_STDIO
#define SER_FOR_STDIO 1
#endif

// return -1 (0xFFFF) if there's no incoming bytes, for non-intr. mode only
int ser1_getchar (void);

// return `c` without any check, may be dead if serial 1 is not setup, for non-intr. mode only
int ser1_putchar (int c);

// setup serial port 1, it does not change IO pins setting
#ifdef FOSC
#if defined(MCU_STC8H)
#define SER1_P30P31 0
#define SER1_P36P37 0x40
#define SER1_P16P17 0x80
#define SER1_P43P44 0xC0
#elif defined(MCU_STC8G1K08_8PIN) || defined(MCU_STC8G1K08A) || defined(MCU_STC8G1K17_8PIN) || defined(MCU_STC8G1K17A)
#define SER1_P30P31 0
#define SER1_P32P33 0x40
#define SER1_P54P55 0x80
#elif defined(MCU_STC8G)
#define SER1_P30P31 0
#define SER1_P36P37 0x40
#define SER1_P16P17 0x80
#define SER1_P43P44 0xC0
#else
#error Not a supported MCU
#endif
#define ser1_setup(baudrate, timer, pins, intr) do { \
	ES = 0; /* disable serial intr. */ \
	PCON &= ~(SMOD | SMOD0); \
	SM0=0; SM1=1; SM2=0; REN=1; /* mode 1, can recv. */ \
	if ((timer)==1) { \
		ET1 = 0; /* timer intr. is not needed */ \
		TR1 = 0; /* T1 is stopped */ \
		INTCLKO &= ~T1CLKO; /* not to output timer clock to pins */ \
		TMOD &= ~(T1_M0 | T1_M1 | T1_GATE | T1_CT); /* T1 in auto-reload mode */ \
		AUXR &= ~(S1M0x6 | S1ST2); \
		AUXR |= T1x12; \
		TH1 = (65536 - (FOSC+(baudrate)*2UL) / ((baudrate) * 4UL)) >> 8; \
		TL1 = (uint8_t)(65536 - (FOSC+(baudrate)*2UL) / ((baudrate) * 4UL)); \
		TR1 = 1; /* Timer is started */ \
	} else { /* use timer 2 */ \
		IE2 &= ~ET2; /* timer intr. is not needed */ \
		AUXR &= ~(S1M0x6 | T2_CT | T2R); /* T2 is stopped */ \
		AUXR |= (S1ST2 | T2x12);  \
		TM2PS = 0;   /* no prescle */ \
		TH1 = (65536 - (FOSC+(baudrate)*2UL) / ((baudrate) * 4UL)) >> 8; \
		TL1 = (uint8_t)(65536 - (FOSC+(baudrate)*2UL) / ((baudrate) * 4UL)); \
		AUXR |= T2R; /* Timer is started */ \
	} \
	TI=1; RI=0; \
	P_SW1 = P_SW1 & ~0xC0 | (pins); \
	if (intr) ES=1; /* enable intr. */ \
} while(0)
#endif

// setup intr. priority of serial port 1 
#define ser1_intr_priority(priority) do { \
	if ((priority)>1) IPH |= PSH; \
	else IPH &= ~PSH; \
	PS = (priority) & 1; \
} while (0)

#endif