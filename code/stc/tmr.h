#ifndef __TMR_H__
#define __TMR_H__

#include "def.h"

// setup timer 0
#define TMR0_RELOAD16       0
#define TMR0_RESET16        1
#define TMR0_RELOAD8        2
#define TMR0_RELOAD16_NMI   3
#define tmr0_setup(mode, tick, t12, to_start, raise_intr, output_pins, is_counter, use_gate) do { \
	ET0 = 0; /* disable intr. */ \
	INTCLKO &= ~T0CLKO; /* no output to pin */ \
	TR0 = 0; /* stop */ \
	TMOD &= ~(T0_CT | T0_GATE | T0_M0 | T0_M1); \
	TMOD |= ((is_counter)?T0_CT:0) | ((use_gate)?T0_GATE:0) | (mode); \
	if (t12) AUXR &= ~T0x12; \
	else AUXR |= T0x12; \
	TH0 = (uint16_t)(tick)>>8; \
	TL0 = (uint8_t)(tick); \
	TF0 = 0; \
	if (raise_intr) ET0 = 1; \
	if (output_pins) INTCLKO |= T0CLKO; \
	if (to_start) TR0 = 1; \
} while (0)

#ifdef FOSC
#define tmr0_setup_reload16(freq, to_start, raise_intr, output_pins, is_counter, use_gate, nmi) do { \
	if ((FOSC+((freq)>>1))/(freq)>65536) { \
		tmr0_setup((nmi)?TMR0_RELOAD16_NMI:TMR0_RELOAD16, \
			(FOSC+6UL*(freq))/(12UL*(freq))>65536 ? 0 : (65536-(FOSC+6UL*(freq))/(12UL*(freq))), 1, \
			to_start, raise_intr, output_pins, is_counter, use_gate); \
	} else { \
		tmr0_setup((nmi)?TMR0_RELOAD16_NMI:TMR0_RELOAD16, \
			(FOSC+((freq)>>1))/(freq)>=1 ? (65536-(FOSC+((freq)>>1))/(freq)) : 0xFFFF, 0, \
			to_start, raise_intr, output_pins, is_counter, use_gate); \
	} \
} while(0)
#endif

#define tmr0_intr_priority(priority) do { \
	if ((priority)>1) IPH |= PT0H; \
	else IPH &= ~PT0H; \
	PT0 = (priority) & 1; \
} while (0)

// get current tick (count number) of timer 0
uint16_t tmr0_get(void) __naked;

// set up timer 1
#define TMR1_RELOAD16       0
#define TMR1_RESET16        0x10
#define TMR1_RELOAD8        0x20
#define tmr1_setup(mode, tick, t12, to_start, raise_intr, output_pins, is_counter, use_gate) do { \
	ET1 = 0; /* disable intr. */ \
	INTCLKO &= ~T1CLKO; /* no output to pin */ \
	TR1 = 0; /* stop */ \
	TMOD &= ~(T1_CT | T1_GATE | T1_M0 | T1_M1); \
	TMOD |= ((is_counter)?T1_CT:0) | ((use_gate)?T1_GATE:0)) | (mode); \
	if (t12) AUXR &= ~T1x12; \
	else AUXR |= T1x12; \
	TH1 = (uint16_t)(tick)>>8; \
	TL1 = (uint8_t)(tick); \
	TF1 = 0; \
	if (raise_intr) ET1 = 1; \
	if (output_pins) INTCLKO |= T1CLKO; \
	if (to_start) TR1 = 1; \
} while (0)

#ifdef FOSC
#define tmr1_setup_reload16(freq, to_start, raise_intr, output_pins, is_counter, use_gate) do { \
	if ((FOSC+((freq)>>1))/(freq)>65536) { \
		tmr1_setup(TMR1_RELOAD16, \
			(FOSC+6UL*(freq))/(12UL*(freq))>65536 ? 0 : (65536-(FOSC+6UL*(freq))/(12UL*(freq))), 1, \
			to_start, raise_intr, output_pins, is_counter, use_gate); \
	} else { \
		tmr1_setup(TMR1_RELOAD16, \
			(FOSC+((freq)>>1))/(freq)>=1 ? (65536-(FOSC+((freq)>>1))/(freq)) : 0xFFFF, 0, \
			to_start, raise_intr, output_pins, is_counter, use_gate); \
	} \
} while(0)
#endif

#define tmr1_intr_priority(priority) do { \
	if ((priority)>1) IPH |= PT1H; \
	else IPH &= ~PT1H; \
	PT1 = (priority) & 1; \
} while (0)

// get current tick (count number) of timer 0
uint16_t tmr1_get(void) __naked;

#if !defined(MCU_STC8G1K08_8PIN) && !defined(MCU_STC8G1K17_8PIN) && !defined(MCU_STC8G1K08A) && !defined(MCU_STC8G1K17A) // those do not have timer 2

#define tmr2_setup(tick, prescale, t12, to_start, raise_intr, output_pins, is_counter) do { \
	IE2 &= ~ET2; /* disable intr. */ \
	INTCLKO &= ~T2CLKO; /* no output to pin */ \
	AUXR &= ~(T2R | T2_CT); /* stop */ \
	if (is_counter) AUXR |= T2_CT; \
	if (t12) AUXR &= ~T2x12; \
	else AUXR |= T2x12; \
	TM2PS = (uint8_t)(prescale); \
	T2H = (uint16_t)(tick)>>8; \
	T2L = (uint8_t)(tick); \
	AUXINTIF &= ~T2IF; \
	if (raise_intr) IE2 |= ET2; \
	if (output_pins) INTCLKO |= T2CLKO; \
	if (to_start) AUXR |= T2R; \
} while (0)

#ifdef FOSC
#define tmr2_setup_prescale(tick, scaled_freq, to_start, raise_intr, output_pins, is_counter) do { \
	if ((FOSC+((scaled_freq)>>1))/(scaled_freq)>256) { \
		tmr2_setup(tick, CLAMP((FOSC+6UL*(scaled_freq))/(12UL*(scaled_freq)), 1, 256)-1, 1, \
			to_start, raise_intr, output_pins, is_counter); \
	} else { \
		tmr2_setup(tick, MAX((FOSC+((scaled_freq)>>1))/(scaled_freq), 1)-1, 0, \
			to_start, raise_intr, output_pins, is_counter); \
	} \
} while (0)

#define tmr2_setup_reload24(freq, to_start, raise_intr, output_pins, is_counter) do { \
	if ((FOSC+((freq)>>1))/(freq)>(256*65536)) { \
		if (((FOSC+6UL*(freq))/(12UL*(freq))+65535)/65536>256) { \
			tmr2_setup(0, 0xFF, 1, \
					to_start, raise_intr, output_pins, is_counter); \
		} else { \
			tmr2_setup(65536-(FOSC+6UL*(((FOSC+6UL*(freq))/(12UL*(freq))+65535)/65536)*(freq))/(12UL*(((FOSC+6UL*(freq))/(12UL*(freq))+65535)/65536)*(freq)), \
				    ((FOSC+6UL*(freq))/(12UL*(freq))+65535)/65536 -1, 1, \
					to_start, raise_intr, output_pins, is_counter); \
		} \
	} else { \
		if ((FOSC+((((FOSC+((freq)>>1))/(freq)+65535)/65536*(freq))>>1))/(((FOSC+((freq)>>1))/(freq)+65535)/65536*(freq))>=1) { \
			tmr2_setup(65536-(FOSC+((((FOSC+((freq)>>1))/(freq)+65535)/65536*(freq))>>1))/(((FOSC+((freq)>>1))/(freq)+65535)/65536*(freq)), \
				    ((FOSC+((freq)>>1))/(freq)+65535)/65536 -1, 0, \
					to_start, raise_intr, output_pins, is_counter); \
		} else { \
			tmr2_setup(0xFFFF, ((FOSC+((freq)>>1))/(freq)+65535)/65536 -1, 0, \
					to_start, raise_intr, output_pins, is_counter); \
		} \
	} \
} while (0)
#endif
			
// get current tick (count number) of timer 2
uint16_t tmr2_get(void) __naked;

#endif

#endif