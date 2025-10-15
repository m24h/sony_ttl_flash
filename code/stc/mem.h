#ifndef __MEM_H
#define __MEM_H

#include "def.h"

// MEM_ROM_SIZE : ROM size
#if   defined(MCU_STC8H1K08) || defined(MCU_STC8H1K08T) \
   || defined(MCU_STC8G1K08_38I) || defined(MCU_STC8G1K08_8PIN) || defined(MCU_STC8G1K08T) || defined(MCU_STC8G1K08A) 
#define MEM_ROM_SIZE 8192	
#elif defined(MCU_STC8H1K12) || defined(MCU_STC8H1K12T)
#define MEM_ROM_SIZE 12288	
#elif defined(MCU_STC8H1K17) || defined(MCU_STC8H1K17T) \
   || defined(MCU_STC8G1K17_38I) || defined(MCU_STC8G1K17_8PIN) || defined(MCU_STC8G1K17T) || defined(MCU_STC8G1K17A) 
#define MEM_ROM_SIZE 17408	
#elif defined(MCU_STC8H1K16) || defined(MCU_STC8G2K16S2) || defined(MCU_STC8G2K16S4)
#define MEM_ROM_SIZE 16384	
#elif defined(MCU_STC8H1K24)
#define MEM_ROM_SIZE 24576	
#elif defined(MCU_STC8H1K28)
#define MEM_ROM_SIZE 0x7000	
#elif defined(MCU_STC8H1K33)
#define MEM_ROM_SIZE 28672	
#elif defined(MCU_STC8H3K32S2) || defined(MCU_STC8H3K32S4) || defined(MCU_STC8H8K32U) || defined(MCU_STC8H4K32TL) || defined(MCU_STC8H4K32TLCD) \
   || defined(MCU_STC8G2K32S2) || defined(MCU_STC8G2K32S4)
#define MEM_ROM_SIZE 32768	
#elif defined(MCU_STC8H3K48S2) || defined(MCU_STC8H3K48S4) || defined(MCU_STC8H8K48U) || defined(MCU_STC8H4K48TL) || defined(MCU_STC8H4K48TLCD) \
   || defined(MCU_STC8G2K48S2) || defined(MCU_STC8G2K48S4)
#define MEM_ROM_SIZE 49152	
#elif defined(MCU_STC8H3K60S2) || defined(MCU_STC8H3K60S4) || defined(MCU_STC8H8K60U) || defined(MCU_STC8H4K60TL) || defined(MCU_STC8H4K60TLCD) \
   || defined(MCU_STC8G2K60S2) || defined(MCU_STC8G2K60S4)
#define MEM_ROM_SIZE 61440	
#elif defined(MCU_STC8H3K64S2) || defined(MCU_STC8H3K64S4) || defined(MCU_STC8H8K64U) || defined(MCU_STC8H4K64TL) || defined(MCU_STC8H4K64TLCD) \
   || defined(MCU_STC8G2K64S2) || defined(MCU_STC8G2K64S4)
#define MEM_ROM_SIZE 65024
#else
#error Not a supported MCU
#endif

// MEM_XRAM_SIZE : XRAM size
#if   defined(MCU_STC8H1K08) \
   || defined(MCU_STC8H1K12) \
   || defined(MCU_STC8H1K17) \
   || defined(MCU_STC8H1K16) \
   || defined(MCU_STC8H1K24) \
   || defined(MCU_STC8H1K28) \
   || defined(MCU_STC8H1K33) \
   || defined(MCU_STC8H1K08T) \
   || defined(MCU_STC8H1K12T) \
   || defined(MCU_STC8H1K17T) \
   || defined(MCU_STC8G1K08_38I) \
   || defined(MCU_STC8G1K17_38I) \
   || defined(MCU_STC8G1K08_8PIN) \
   || defined(MCU_STC8G1K17_8PIN) \
   || defined(MCU_STC8G1K08A) \
   || defined(MCU_STC8G1K17A) \
   || defined(MCU_STC8G1K08T) \
   || defined(MCU_STC8G1K17T) 
#define MEM_XRAM_SIZE 1024
#elif defined(MCU_STC8G2K16S4) \
   || defined(MCU_STC8G2K32S4) \
   || defined(MCU_STC8G2K48S4) \
   || defined(MCU_STC8G2K60S4) \
   || defined(MCU_STC8G2K64S4) \
   || defined(MCU_STC8G2K16S2) \
   || defined(MCU_STC8G2K32S2) \
   || defined(MCU_STC8G2K48S2) \
   || defined(MCU_STC8G2K60S2) \
   || defined(MCU_STC8G2K64S2)
#define MEM_XRAM_SIZE 2048
#elif defined(MCU_STC8H3K32S2) \
   || defined(MCU_STC8H3K48S2) \
   || defined(MCU_STC8H3K60S2) \
   || defined(MCU_STC8H3K64S2) \
   || defined(MCU_STC8H3K32S4) \
   || defined(MCU_STC8H3K48S4) \
   || defined(MCU_STC8H3K60S4) \
   || defined(MCU_STC8H3K64S4)
#define MEM_XRAM_SIZE 3072
#elif defined(MCU_STC8H4K32TL) \
   || defined(MCU_STC8H4K48TL) \
   || defined(MCU_STC8H4K60TL) \
   || defined(MCU_STC8H4K64TL) \
   || defined(MCU_STC8H4K32TLCD) \
   || defined(MCU_STC8H4K48TLCD) \
   || defined(MCU_STC8H4K60TLCD) \
   || defined(MCU_STC8H4K64TLCD)  
#define MEM_XRAM_SIZE 4096
#elif defined(MCU_STC8H8K32U) \
   || defined(MCU_STC8H8K48U) \
   || defined(MCU_STC8H8K60U) \
   || defined(MCU_STC8H8K64U)
#define MEM_XRAM_SIZE 8192
#else
#error Not a supported MCU
#endif

// enable XRAM
#define mem_xram_enable() do { \
	AUXR &= ~EXTRAM;  \
	P_SW2 |= EAXFR; \
} while(0)







#endif

