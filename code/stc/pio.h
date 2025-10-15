#ifndef __PIO_H__
#define __PIO_H__

#include "def.h"

// to use P54 as reset pin or not to
#define pio_reset(enable) do { \
	if (enable) RSTCFG |= P54RST; \
	else RSTCFG &= ~P54RST; \
} while(0)

// output main clock to a pin if `div` is not 0 
#define PIO_MCLK_P54    0
#define PIO_MCLK_P16    1 
#define pio_mclk(pin, div) MCLKOCR = ((PIO_MCLK_P16)?0x80:0) | (div)

#define PIO_BIDIR    0
#define PIO_OUTPUT   1
#define PIO_INPUT    2
#define PIO_DRAIN    3
#define PIO_ANALOG   6
#define PIO_FLOAT    6

#define PIO_STRONG        0x80
#define PIO_FAST          0x40
#if defined(MCU_STC8H)
#define PIO_PULLDOWN      0x20
#endif
#define PIO_PULLUP        0x10
#define PIO_SCHMITT       0x08

#define PIO_P00 (0<<8 | 1<<0)
#define PIO_P01 (0<<8 | 1<<1)
#define PIO_P02 (0<<8 | 1<<2)
#define PIO_P03 (0<<8 | 1<<3)
#define PIO_P04 (0<<8 | 1<<4)
#define PIO_P05 (0<<8 | 1<<5)
#define PIO_P06 (0<<8 | 1<<6)
#define PIO_P07 (0<<8 | 1<<7)
#define PIO_P10 (1<<8 | 1<<0)
#define PIO_P11 (1<<8 | 1<<1)
#define PIO_P12 (1<<8 | 1<<2)
#define PIO_P13 (1<<8 | 1<<3)
#define PIO_P14 (1<<8 | 1<<4)
#define PIO_P15 (1<<8 | 1<<5)
#define PIO_P16 (1<<8 | 1<<6)
#define PIO_P17 (1<<8 | 1<<7)
#define PIO_P20 (2<<8 | 1<<0)
#define PIO_P21 (2<<8 | 1<<1)
#define PIO_P22 (2<<8 | 1<<2)
#define PIO_P23 (2<<8 | 1<<3)
#define PIO_P24 (2<<8 | 1<<4)
#define PIO_P25 (2<<8 | 1<<5)
#define PIO_P26 (2<<8 | 1<<6)
#define PIO_P27 (2<<8 | 1<<7)
#define PIO_P30 (3<<8 | 1<<0)
#define PIO_P31 (3<<8 | 1<<1)
#define PIO_P32 (3<<8 | 1<<2)
#define PIO_P33 (3<<8 | 1<<3)
#define PIO_P34 (3<<8 | 1<<4)
#define PIO_P35 (3<<8 | 1<<5)
#define PIO_P36 (3<<8 | 1<<6)
#define PIO_P37 (3<<8 | 1<<7)
#define PIO_P40 (4<<8 | 1<<0)
#define PIO_P41 (4<<8 | 1<<1)
#define PIO_P42 (4<<8 | 1<<2)
#define PIO_P43 (4<<8 | 1<<3)
#define PIO_P44 (4<<8 | 1<<4)
#define PIO_P45 (4<<8 | 1<<5)
#define PIO_P46 (4<<8 | 1<<6)
#define PIO_P47 (4<<8 | 1<<7)
#define PIO_P50 (5<<8 | 1<<0)
#define PIO_P51 (5<<8 | 1<<1)
#define PIO_P52 (5<<8 | 1<<2)
#define PIO_P53 (5<<8 | 1<<3)
#define PIO_P54 (5<<8 | 1<<4)
#define PIO_P55 (5<<8 | 1<<5)
#define PIO_P56 (5<<8 | 1<<6)
#define PIO_P57 (5<<8 | 1<<7)
#define PIO_P60 (6<<8 | 1<<0)
#define PIO_P61 (6<<8 | 1<<1)
#define PIO_P62 (6<<8 | 1<<2)
#define PIO_P63 (6<<8 | 1<<3)
#define PIO_P64 (6<<8 | 1<<4)
#define PIO_P65 (6<<8 | 1<<5)
#define PIO_P66 (6<<8 | 1<<6)
#define PIO_P67 (6<<8 | 1<<7)
#define PIO_P70 (7<<8 | 1<<0)
#define PIO_P71 (7<<8 | 1<<1)
#define PIO_P72 (7<<8 | 1<<2)
#define PIO_P73 (7<<8 | 1<<3)
#define PIO_P74 (7<<8 | 1<<4)
#define PIO_P75 (7<<8 | 1<<5)
#define PIO_P76 (7<<8 | 1<<6)
#define PIO_P77 (7<<8 | 1<<7)

// get address of specified port/bit
#define pio_addr(port, bit) ((pn)<<8 | 1<<(bit))
#define pio_pnn(pnn) MACRO_CONCAT(PIO_, pnn)

// get IO value, `addr` is PIO_Pnn or returned value of pio_addr()
__bit pio_get(uint16_t addr) __naked;

// set IO value, `addr` is PIO_Pnn or returned value of pio_addr()
void pio_set(uint16_t addr, __bit value) __reentrant __naked;

// set IO mode, `port` is PIO_Pnn or returned value of pio_addr(), `mode` is PIO_xxx
void pio_config(uint16_t addr, uint8_t mode) __reentrant __naked;

// turn all IO port off
#pragma callee_saves pio_disable_all
void pio_disable_all(void);

#if defined(MCU_STC8H)
#define pio_port_disable(port) do { \
	P ## port ## PU = 0; \
	P ## port ## PD = 0; \
	P ## port ## IE = 0; \
	P ## port ## M0 = 0; \
	P ## port ## M1 = 0xFF; \
	P ## port ## SR = 0xFF; \
	P ## port ## DR = 0xFF; \
	P ## port ## NCS = 0xFF; \
} while (0)
#else
#define pio_port_disable(port) do { \
	P ## port ## PU = 0; \
	P ## port ## IE = 0; \
	P ## port ## M0 = 0; \
	P ## port ## M1 = 0xFF; \
	P ## port ## SR = 0xFF; \
	P ## port ## DR = 0xFF; \
	P ## port ## NCS = 0xFF; \
} while (0)
#endif

#if defined(MCU_STC8H)
#define pio_port_config(port, mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7) do { \
	P ## port ## PU=((mode0) & PIO_PULLUP?0x01:0) | ((mode1) & PIO_PULLUP?0x02:0) | ((mode2) & PIO_PULLUP?0x04:0) | ((mode3) & PIO_PULLUP?0x08:0) \
		          | ((mode4) & PIO_PULLUP?0x10:0) | ((mode5) & PIO_PULLUP?0x20:0) | ((mode6) & PIO_PULLUP?0x40:0) | ((mode7) & PIO_PULLUP?0x80:0); \
	P ## port ## PD=((mode0) & PIO_PULLDOWN?0x01:0) | ((mode1) & PIO_PULLDOWN?0x02:0) | ((mode2) & PIO_PULLDOWN?0x04:0) | ((mode3) & PIO_PULLDOWN?0x08:0) \
		          | ((mode4) & PIO_PULLDOWN?0x10:0) | ((mode5) & PIO_PULLDOWN?0x20:0) | ((mode6) & PIO_PULLDOWN?0x40:0) | ((mode7) & PIO_PULLDOWN?0x80:0); \
	P ## port ## IE=((mode0) & 0x04?0:0x01) | ((mode1) & 0x04?0:0x02) | ((mode2) & 0x04?0:0x04) | ((mode3) & 0x04?0:0x08) \
		          | ((mode4) & 0x04?0:0x10) | ((mode5) & 0x04?0:0x20) | ((mode6) & 0x04?0:0x40) | ((mode7) & 0x04?0:0x80); \
	P ## port ## M0=((mode0) & 0x01?0x01:0) | ((mode1) & 0x01?0x02:0) | ((mode2) & 0x01?0x04:0) | ((mode3) & 0x01?0x08:0) \
		          | ((mode4) & 0x01?0x10:0) | ((mode5) & 0x01?0x20:0) | ((mode6) & 0x01?0x40:0) | ((mode7) & 0x01?0x80:0); \
	P ## port ## M1=((mode0) & 0x02?0x01:0) | ((mode1) & 0x02?0x02:0) | ((mode2) & 0x02?0x04:0) | ((mode3) & 0x02?0x08:0) \
		          | ((mode4) & 0x02?0x10:0) | ((mode5) & 0x02?0x20:0) | ((mode6) & 0x02?0x40:0) | ((mode7) & 0x02?0x80:0); \
	P ## port ## SR=((mode0) & PIO_FAST?0:0x01) | ((mode1) & PIO_FAST?0:0x02) | ((mode2) & PIO_FAST?0:0x04) | ((mode3) & PIO_FAST?0:0x08) \
		          | ((mode4) & PIO_FAST?0:0x10) | ((mode5) & PIO_FAST?0:0x20) | ((mode6) & PIO_FAST?0:0x40) | ((mode7) & PIO_FAST?0:0x80); \
	P ## port ## DR=((mode0) & PIO_STRONG?0:0x01) | ((mode1) & PIO_STRONG?0:0x02) | ((mode2) & PIO_STRONG?0:0x04) | ((mode3) & PIO_STRONG?0:0x08) \
		          | ((mode4) & PIO_STRONG?0:0x10) | ((mode5) & PIO_STRONG?0:0x20) | ((mode6) & PIO_STRONG?0:0x40) | ((mode7) & PIO_STRONG?0:0x80); \
	P ## port ## NCS=((mode0) & PIO_SCHMITT?0:0x01) | ((mode1) & PIO_SCHMITT?0:0x02) | ((mode2) & PIO_SCHMITT?0:0x04) | ((mode3) & PIO_SCHMITT?0:0x08) \
		          |  ((mode4) & PIO_SCHMITT?0:0x10) | ((mode5) & PIO_SCHMITT?0:0x20) | ((mode6) & PIO_SCHMITT?0:0x40) | ((mode7) & PIO_SCHMITT?0:0x80); \
} while (0)
#else
#define pio_port_config(port, mode0, mode1, mode2, mode3, mode4, mode5, mode6, mode7) do { \
	P ## port ## PU=((mode0) & PIO_PULLUP?0x01:0) | ((mode1) & PIO_PULLUP?0x02:0) | ((mode2) & PIO_PULLUP?0x04:0) | ((mode3) & PIO_PULLUP?0x08:0) \
		          | ((mode4) & PIO_PULLUP?0x10:0) | ((mode5) & PIO_PULLUP?0x20:0) | ((mode6) & PIO_PULLUP?0x40:0) | ((mode7) & PIO_PULLUP?0x80:0); \
	P ## port ## IE=((mode0) & 0x04?0:0x01) | ((mode1) & 0x04?0:0x02) | ((mode2) & 0x04?0:0x04) | ((mode3) & 0x04?0:0x08) \
		          | ((mode4) & 0x04?0:0x10) | ((mode5) & 0x04?0:0x20) | ((mode6) & 0x04?0:0x40) | ((mode7) & 0x04?0:0x80); \
	P ## port ## M0=((mode0) & 0x01?0x01:0) | ((mode1) & 0x01?0x02:0) | ((mode2) & 0x01?0x04:0) | ((mode3) & 0x01?0x08:0) \
		          | ((mode4) & 0x01?0x10:0) | ((mode5) & 0x01?0x20:0) | ((mode6) & 0x01?0x40:0) | ((mode7) & 0x01?0x80:0); \
	P ## port ## M1=((mode0) & 0x02?0x01:0) | ((mode1) & 0x02?0x02:0) | ((mode2) & 0x02?0x04:0) | ((mode3) & 0x02?0x08:0) \
		          | ((mode4) & 0x02?0x10:0) | ((mode5) & 0x02?0x20:0) | ((mode6) & 0x02?0x40:0) | ((mode7) & 0x02?0x80:0); \
	P ## port ## SR=((mode0) & PIO_FAST?0:0x01) | ((mode1) & PIO_FAST?0:0x02) | ((mode2) & PIO_FAST?0:0x04) | ((mode3) & PIO_FAST?0:0x08) \
		          | ((mode4) & PIO_FAST?0:0x10) | ((mode5) & PIO_FAST?0:0x20) | ((mode6) & PIO_FAST?0:0x40) | ((mode7) & PIO_FAST?0:0x80); \
	P ## port ## DR=((mode0) & PIO_STRONG?0:0x01) | ((mode1) & PIO_STRONG?0:0x02) | ((mode2) & PIO_STRONG?0:0x04) | ((mode3) & PIO_STRONG?0:0x08) \
		          | ((mode4) & PIO_STRONG?0:0x10) | ((mode5) & PIO_STRONG?0:0x20) | ((mode6) & PIO_STRONG?0:0x40) | ((mode7) & PIO_STRONG?0:0x80); \
	P ## port ## NCS=((mode0) & PIO_SCHMITT?0:0x01) | ((mode1) & PIO_SCHMITT?0:0x02) | ((mode2) & PIO_SCHMITT?0:0x04) | ((mode3) & PIO_SCHMITT?0:0x08) \
		          |  ((mode4) & PIO_SCHMITT?0:0x10) | ((mode5) & PIO_SCHMITT?0:0x20) | ((mode6) & PIO_SCHMITT?0:0x40) | ((mode7) & PIO_SCHMITT?0:0x80); \
} while (0)
#endif	
	
#define pio_int0_config(fall_only, intr, priority) do { \
	IT0 = (fall_only); \
	IE0 = 0; \
	EX0 = (intr); \
	if ((priority)>1) IPH |= PX0H; \
	else IPH &= ~PX0H; \
	PX0 = (priority) & 1; \
} while (0)

#define pio_int1_config(fall_only, intr, priority) do { \
	IT1 = (fall_only); \
	IE1 = 0; \
	EX1 = (intr); \
	if ((priority)>1) IPH |= PX1H; \
	else IPH &= ~PX1H; \
	PX1 = (priority) & 1; \
} while (0)


#endif