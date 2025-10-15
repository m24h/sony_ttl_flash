#ifndef     __FLASH_H__
#define     __FLASH_H__

/* 
Sony P-TTL Flash implementation on STC8 (8051) serial MCU. (currently manual flashing is not supported)
It needs and initializes such resources:
- P32/P33 IO port
- INT0/INT1 and its ISR, with highest priority
- Timer 0 and its ISR, with priority 2
- a bidirectional IO port
- a register bank, defaultly 3
*/

#include "stc/def.h"
#include "flash_sony.h"

/*
It must use INT0/1 (P32/P33) for both rising/falling edge supported ext-interruption for FLASH_F3CLK and FLASH_F1SYNC, since the other pins normally does not support both edge ext-interruption.
FLASH_F3CLK should be connected to pin 18 of Sony MI port.
Defaultly, FLASH_F1SYNC uses INT1(P33) and FLASH_F3CLK uses INT0(P32), define FLASH_F1SYNC and FLASH_F3CLK before this file to change this.
*/
#ifndef FLASH_F1SYNC
#define FLASH_F1SYNC    P33
#endif
#ifndef FLASH_F3CLK
#define FLASH_F3CLK     P32
#endif

// check definition of FLASH_F1SYNC & FLASH_F3CLK
#define P32_VECTOR INT0_VECTOR
#define P33_VECTOR INT1_VECTOR
#if MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)!=INT0_VECTOR && MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)!=INT1_VECTOR || MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)==MACRO_CONCAT(FLASH_F3CLK, _VECTOR)
#error FLASH_F1SYNC must be one of P32/P33, and can not be the same as FLASH_F3CLK
#endif
#if MACRO_CONCAT(FLASH_F3CLK, _VECTOR)!=INT0_VECTOR && MACRO_CONCAT(FLASH_F3CLK, _VECTOR)!=INT1_VECTOR || MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)==MACRO_CONCAT(FLASH_F3CLK, _VECTOR)
#error FLASH_F3CLK must be one of P32/P33, and can not be the same as FLASH_F1SYNC
#endif

/*
FLASH_F1SYNC needs to be connected to the pin 20 of MI port or the ISO central point (called X of ISO shoe, or pin 22 of MI port), but the logic levels of them are opposite. 
When connecting to pin 20 of MI port, flashing is triggered by the rising edge and requires a pull-down resistor (Many MCU does not support internal pull-down).
when connecting the ISO central point, flashing is triggered by the falling edge and requires a pull-up resistor (Many MCU support internal pull-up).
Defaultly pin 20 of MI port is used, define following macro to take negative logic and use the ISO central point.
*/ 
//#define F1SYNC_NEGATIVE

/* 
A bidirectional IO port is needed and it should be connected to pin 19 of MI port.	
*/
//#define FLASH_F2DAT P??
#ifndef FLASH_F2DAT
#error FLASH_F2DAT must be defined as P??
#endif

/* 
define FLASH_START for starting flash (open IGBT), and FLASH_STOP for stopping flash (close IGBT)	
*/
//#define FLASH_START  <some code>
//#define FLASH_STOP   <some code>
#if !defined(FLASH_START) || !defined(FLASH_STOP)
#error FLASH_START and FLASH_STOP must be defined
#endif

/*
FLASH_PREPARE is called about 13ms before the flashing, in ISR.
*/
#ifndef FLASH_PREPARE
#define FLASH_PREPARE
#endif 

/*
A delay is needed for camera to capture before pre-flash, normally 200-300us
*/
#ifndef FLASH_PREFLASH_DELAY
#define FLASH_PREFLASH_DELAY 300
#endif

/*
A delay is needed before formal flash, normally 200-300us
*/
#ifndef FLASH_FORMAL_DELAY
#define FLASH_FORMAL_DELAY 300
#endif

/*
The table of flash time in us to signed flash power level (-32 to 31), it should be defined somewhere.
flash_time_of_level[0] is the pre-flash/base power level, and 4 levels mean 1EV.
The max power level should be defined in macro FLASH_POWER_LEVEL_MAX, flash_time_of_level[FLASH_POWER_LEVEL_MAX] is the highest power level, likely :
*/
#ifndef FLASH_POWER_LEVEL_MAX
#define FLASH_POWER_LEVEL_MAX 31
#endif

extern const uint16_t  flash_time_of_level[64]; // should be customized and defined somewhere

/*
Generally, the camera will send a pre-flash request with required energy level. 
However, if controlling the light output with too little energy is difficult, this program can use at least a fixed power level for pre-flash and amplifies it accordingly. 
Use following macro to specify minimum pre-flash power level.
*/
#ifndef FLASH_PREFLASH_MIN
#define FLASH_PREFLASH_MIN -16 // minimum pre-flash power level for F1.0 lens 
#endif

/*
FLASH_LEVEL_FULL is the index of maximum time value in flash_time_of_level taable,
it is also log2(Guide_Number)*8-20 .
*/
#ifndef FLASH_LEVEL_FULL
#error FLASH_LEVEL_FULL must be defined
#endif
/*
Sometimes if the pre-flash is too strong, it can cause the camera to calculate the formal flash intensity too low.
Use this macro to compress the effect.
*/
//#define FLASH_LOW_FLASH_ENHANCE

/* useful parameters, should be readonly outside, it's volatile for  */
extern volatile Flash_Sony_Data  flash_data;         // current flash communication data
extern volatile int8_t           flash_power_pre;    // last pre-flash power level instructed by camera
extern volatile int8_t           flash_power_formal; // last formal flash power level instructed by camera
extern volatile int8_t           flash_power_pre_act;     // last actual pre-flash power level
extern volatile int8_t           flash_power_formal_act;  // last actual formal flash power level
#define FLASH_POWER_NA (-128) // this value is for above power levels, means not available

/* controlling parameters */
extern __bit   flash_can_fire;    // set to 1 to enable flashing when primary capacitor is charged enough

// declaration of ISRs must be included in .c file with main() to take effect, so to include this file in main .c file.
// ISRs here should have the same priority and bank.
// IMPORTANT!! a register bank (defaultly 3) is reserved for exclusive use
#ifndef FLASH_ISR_BANK
#define FLASH_ISR_BANK 3
#endif
#ifndef FLASH_ISR_PRIORITY
#define FLASH_ISR_PRIORITY 3
#endif
void flash_f3clk_isr(void)  __interrupt (MACRO_CONCAT(FLASH_F3CLK, _VECTOR))  __using(FLASH_ISR_BANK);
void flash_f1sync_isr(void) __interrupt (MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)) __using(FLASH_ISR_BANK);
void flash_timer_isr(void)  __interrupt (TMR0_VECTOR) __using(FLASH_ISR_BANK);

/*
Call this function to initialize this module in setup progress
*/
void flash_setup(void);

#endif