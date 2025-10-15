// lib config, do not change these if hardware is not changed
#define MCU_STC8H1K08
#define FOSC 22118400

// ports config, do not change these if hardware is not changed
#define VHCTL  P10
#define LED    P54
#define RXD    P30
#define TXD    P31
#define VHSAMP P35
#define ADC_VHSAMP_CH 13 // ADC channel

// flash config
#define FLASH_F1SYNC    P33
#define FLASH_F2DAT     P34
#define FLASH_F3CLK     P32

#define FLASH_LEVEL_FULL 8 // GN6 
#define FLASH_LOW_FLASH_ENHANCE
#define FLASH_START __asm orl P1, #0xfe __endasm
#define FLASH_STOP  __asm anl P1, #0x01 __endasm

// main config
#define DEBUG       2       // debug level, 0 means no debug
#define BAUDRATE    9600

/*
V_sample = V_high * VH_RATIO + VH_BIAS, if VHCTL==1
*/
#define VH_RATIO     ((6.8+4.7)/(680+470+6.8+4.7))
#define VH_BIAS      0
#define VH_LEAST     280     // 250V is the lowest fire voltage, but for P-TTL (double flash), 280V seems to be more stable
#define VH_DEST      300
#define ADC_RATE     100000  // 10us each time
#define ADC_REF_MV   1190

//#define USE_PWM_STEP_UP // IMPORTANT: it's never tested, and LM2733Y must not be on the PCB
