#ifndef __SYS_H__
#define __SYS_H__

#include "def.h"

#ifdef FOSC

#pragma callee_saves sys_delay_ms, sys_delay_us

// delay in millisecond, specified by `ms`
// safe for re-enter and ISR calling
void sys_delay_ms(uint16_t ms) __naked;

// delay in microsecond, specified by `us`
// safe for re-enter and ISR calling
void sys_delay_us(uint16_t us) __naked;

#endif

// soft reboot, this function will not return
// safe for re-enter and ISR calling
void sys_boot(void) __naked;
	
// boot to download mode, this function will not return
// safe for re-enter and ISR calling
void sys_boot_ISP(void) __naked;


// enable watch dog timer and clear current counting number
#ifdef FOSC
#define sys_wdt_enable(timeout_ms, idle_count) \
	WDT_CONTR = EN_WDT | CLR_WDT | ((idle_count)?IDL_WDT:0) | ( \
		(timeout_ms) > 12000UL*32768/(FOSC/128) ? 7 : \
		(timeout_ms) > 12000UL*32768/(FOSC/64) ? 6 : \
		(timeout_ms) > 12000UL*32768/(FOSC/32) ? 5 : \
		(timeout_ms) > 12000UL*32768/(FOSC/16) ? 4 : \
		(timeout_ms) > 12000UL*32768/(FOSC/8) ? 3 : \
		(timeout_ms) > 12000UL*32768/(FOSC/4) ? 2 : \
		(timeout_ms) > 12000UL*32768/(FOSC/2) ? 1 : \
		0 \
	)	
#endif

// clear watch dog timer (feed the dog)
#define sys_wdt_clear() WDT_CONTR |= CLR_WDT

// setup Low-Voltage detection
#define sys_lvd_setup(volt_mv, reset, intr) do { \
	ELVD = 0; \
	RSTCFG = RSTCFG & ~(((reset)?0:ENLVR) | 3) | (((reset)?ENLVR:0) | \
		((volt_mv)<=2000?0: (volt_mv)<=2400?1: (volt_mv)<=2700?2: 3)); \
    PCON &= ~LVDF; \
    if (intr) ELVD=1;  \
} while (0)

// set Low-Voltage intr. priority
#define sys_lvd_intr_priority(priority) do { \
	if ((priority)>1) IPH |= PLVDH; \
	else IPH &= ~PLVDH; \
	PLVD = (priority) & 1; \
} while (0)
		







#endif