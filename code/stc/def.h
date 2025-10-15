#ifndef     __DEF_H__
#define     __DEF_H__

#ifndef __SDCC_mcs51
#error designed and optimized for sdcc/mcs51 only
#endif 

#include <stdint.h>


// macro control parameters, should be writen in "config.h"
// #define FOSC 22118400         // running system clock freq.
// #define MCU_xxxxxx            // MCU chip type, like MCU_STC8H1K08/MCU_STC8H8K64U/MCU_STC8H1K08T and so on
#include "../config.h"

#if \
    defined(MCU_STC8H1K08) \
 || defined(MCU_STC8H1K12) \
 || defined(MCU_STC8H1K17) \
 || defined(MCU_STC8H1K08T) \
 || defined(MCU_STC8H1K12T) \
 || defined(MCU_STC8H1K17T) \
 || defined(MCU_STC8H1K16) \
 || defined(MCU_STC8H1K24) \
 || defined(MCU_STC8H1K28) \
 || defined(MCU_STC8H1K33) \
 || defined(MCU_STC8H3K32S2) \
 || defined(MCU_STC8H3K48S2) \
 || defined(MCU_STC8H3K60S2) \
 || defined(MCU_STC8H3K64S2) \
 || defined(MCU_STC8H3K32S4) \
 || defined(MCU_STC8H3K48S4) \
 || defined(MCU_STC8H3K60S4) \
 || defined(MCU_STC8H3K64S4) \
 || defined(MCU_STC8H8K32U) \
 || defined(MCU_STC8H8K48U) \
 || defined(MCU_STC8H8K60U) \
 || defined(MCU_STC8H8K64U) \
 || defined(MCU_STC8H4K32TL) \
 || defined(MCU_STC8H4K48TL) \
 || defined(MCU_STC8H4K60TL) \
 || defined(MCU_STC8H4K64TL) \
 || defined(MCU_STC8H4K32TLCD) \
 || defined(MCU_STC8H4K48TLCD) \
 || defined(MCU_STC8H4K60TLCD) \
 || defined(MCU_STC8H4K64TLCD) 
#define MCU_STC8H
#include "stc8h.h"
#elif \
    defined(MCU_STC8G1K08_38I) /* -38I seiral */ \
 || defined(MCU_STC8G1K17_38I) /* -38I seiral */ \
 || defined(MCU_STC8G1K08_8PIN) \
 || defined(MCU_STC8G1K17_8PIN) \
 || defined(MCU_STC8G1K08T) \
 || defined(MCU_STC8G1K17T) \
 || defined(MCU_STC8G1K08A) \
 || defined(MCU_STC8G1K17A) \
 || defined(MCU_STC8G2K16S4) \
 || defined(MCU_STC8G2K32S4) \
 || defined(MCU_STC8G2K48S4) \
 || defined(MCU_STC8G2K60S4) \
 || defined(MCU_STC8G2K64S4) \
 || defined(MCU_STC8G2K16S2) \
 || defined(MCU_STC8G2K32S2) \
 || defined(MCU_STC8G2K48S2) \
 || defined(MCU_STC8G2K60S2) \
 || defined(MCU_STC8G2K64S2)
#define MCU_STC8G
#include "stc8g.h"
#else
#error Not a supported MCU
#endif

#undef NOP
#define nop()     __asm nop __endasm
#define _nop_()   __asm nop __endasm

// SMALL-ENDIAN for sdcc
#define PACK16(p, h, l) do { \
	*(uint8_t*)(p)=(l); \
	*((uint8_t*)(p)+1)=(h); \
} while(0)
	
#define PACK32(p, hh, hl, lh, ll) do { \
	*(uint8_t*)(p)=(ll); \
	*((uint8_t*)(p)+1)=(lh); \
	*((uint8_t*)(p)+2)=(hl); \
	*((uint8_t*)(p)+3)=(hh); \
} while(0)
		
#define UNPACK16H(p) *((uint8_t*)(p)+1)
#define UNPACK16L(p) *((uint8_t*)(p))
#define UNPACK32HH(p) *((uint8_t*)(p)+3)
#define UNPACK32HL(p) *((uint8_t*)(p)+2)
#define UNPACK32LH(p) *((uint8_t*)(p)+1)
#define UNPACK32LL(p) *((uint8_t*)(p))

#define CLAMP(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))
#define MAX(a,b) ((a)<(b)?(b):(a))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define MACRO_CONCAT_RAW(a,b) a ## b 
#define MACRO_CONCAT(a,b) MACRO_CONCAT_RAW(a, b)
#define MACRO_HASH #
#define ASM_SYMBOL(addr) MACRO_CONCAT(_, addr)

#define CRITICAL for (EA = 0,  nop(), nop() ; !EA; EA = 1)  

#endif

