#ifndef     __MAIN_H__
#define     __MAIN_H__

#include <ctype.h>
#include <stdio.h>

#include "stc/def.h"

// DEBUG is macro definition for debuging
#define printf(fmt, ...) printf_tiny(fmt, ##__VA_ARGS__)
#if defined(DEBUG)
#define debug(level, fmt, ...) do { if (DEBUG>=level) printf(fmt, ##__VA_ARGS__); } while (0)
#else
#define debug(level, fmt, ...) 
#endif

// safe for ISR, need --stack-auto option in sdcc command line too
#pragma nooverlay
#if !defined(__SDCC_STACK_AUTO) && !defined(__SDCC_INT_LONG_REENT)
#error need `--stack-auto` or `--int-long-reent` option in sdcc command line, for __mulint() using in ISR
#endif

// those are small and simple functions which need few or no registers
//#pragma callee_saves 

#if FOSC<16000000  
#error system clock should be at least 16MHz, 22.1184MHz is recommend
#endif

// a system tick in 10ms
uint16_t main_tick_get(void) __naked;

// current device voltage, in mV, safe for read only
extern uint16_t volt_vdd_mv;

// current high voltage * 10, safe for read only
extern uint16_t volt_high_10;


#endif
