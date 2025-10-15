#include "flash.h"
#include "stc/tmr.h"
#include "stc/pio.h"
#include "stc/sys.h"

volatile Flash_Sony_Data flash_data = {
    .state = FLASH_SONY_COMM_OFFLINE,
    .read = { FLASH_SONY_READ_FEATURE_DEF,
        FLASH_SONY_READ_UNKNOWN1_DEF,
        FLASH_SONY_READ_ZOOM_DEF,
        FLASH_SONY_READ_UNKNOWN2_DEF,
        FLASH_SONY_READ_CONTROLLED_ENABLE | (28+FLASH_LEVEL_FULL), 
        FLASH_SONY_READ_MODE_DEF | FLASH_SONY_READ_MODE_CONTROLLED | FLASH_SONY_READ_MODE_MOUNTED,
        FLASH_SONY_READ_WIRELESS_DEF,
        FLASH_SONY_READ_FOCAL_35,
        79, // 1/16 full power
        FLASH_SONY_READ_COLOR_DEF,
        FLASH_SONY_READ_UNKNOWN3_DEF },
    .rlen = 0,
    .write = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0} },
    .wlen = 0
};
volatile int8_t  flash_power_pre = FLASH_POWER_NA;
volatile int8_t  flash_power_formal = FLASH_POWER_NA;
volatile int8_t  flash_power_pre_act = FLASH_POWER_NA;
volatile int8_t  flash_power_formal_act = FLASH_POWER_NA;

__bit   flash_can_fire = 0;

#define timer_start() do { \
    TR0 = 0; \
    TH0 = (65536-FOSC/12/1000)>>8; /* timeout setting: 1ms */ \
    TL0 = (65536-FOSC/12/1000)&0xFF; \
    TF0 = 0; \
    TR0 = 1; \
} while (0) 

static uint16_t thtl = 0; // used to calculate time elapsed
#define timer_stop() do { \
    TR0 = 0; \
    TF0 = 0; \
    PACK16(&thtl, TH0, TL0); \
} while (0)

#define delay(us) __asm \
	mov dptr, MACRO_HASH(us) \
    lcall _sys_delay_us ; called in asm since sdcc cannot recognize that _sys_delay_us is __naked and tries to push/pop r0-r7 in different banks \
    __endasm


#define preflash() do { \
    if (flash_data.write.power & FLASH_SONY_WRITE_POWER_VALID) { \
        flash_power_pre = flash_data.write.power & FLASH_SONY_WRITE_POWER_LEVEL; \
        if (flash_power_pre & 0x20) flash_power_pre -= 64; \
    } else { \
        flash_power_pre = FLASH_POWER_NA; /* this value means n/a */ \
    } \
    if (flash_can_fire && flash_power_pre != FLASH_POWER_NA) { \
        if (flash_power_pre>31) flash_power_pre_act = 31; \
        else if (flash_power_pre<FLASH_PREFLASH_MIN) flash_power_pre_act = FLASH_PREFLASH_MIN; \
        else flash_power_pre_act = flash_power_pre; \
        register uint16_t delay=flash_time_of_level[flash_power_pre_act & 0x3F]; \
        FLASH_START; \
        DPH = delay>>8; \
        DPL = (uint8_t)delay; \
        __asm \
        lcall _sys_delay_us ; called in asm since sdcc cannot recognize that _sys_delay_us is __naked and tries to push/pop r0-r7 in different banks \
        __endasm; \
        FLASH_STOP; \
    } else flash_power_pre_act = FLASH_POWER_NA; \
} while (0)

#ifdef FLASH_LOW_FLASH_ENHANCE
#define low_flash_enhance if (flash_power_formal<flash_power_pre) flash_power_formal_act += (flash_power_pre - flash_power_formal)>>1; 
#else
#define low_flash_enhance 
#endif
#define flash() do { \
    if (flash_data.write.power & FLASH_SONY_WRITE_POWER_VALID) { \
        flash_power_formal = flash_data.write.power & FLASH_SONY_WRITE_POWER_LEVEL; \
        if (flash_power_formal & 0x20) flash_power_formal -= 64; \
    } else { \
        flash_power_formal = FLASH_POWER_NA; \
    } \
    if (flash_data.read.mode & FLASH_SONY_READ_MODE_CONTROLLED) { /* TTL */ \
        if (flash_power_pre_act != FLASH_POWER_NA /* formal flash is only after pre-flash */ ) { \
            flash_power_formal_act = flash_power_formal - flash_power_pre + flash_power_pre_act; \
            low_flash_enhance \
        } else flash_power_formal_act = FLASH_POWER_NA; \
    } else if (flash_can_fire) { /* Manual flash */ \
        flash_power_formal_act = FLASH_POWER_LEVEL_MAX-((flash_data.read.power-15)>>2); \
    } else { \
        flash_power_formal_act = FLASH_POWER_NA; \
    } \
    if (flash_power_formal_act != FLASH_POWER_NA) { \
        if (flash_power_formal_act>31) flash_power_formal_act = 31; \
        else if (flash_power_formal_act<-32) flash_power_formal_act = -32; \
        register uint16_t delay=flash_time_of_level[flash_power_formal_act & 0x3F]; \
        FLASH_START; \
        DPH = delay>>8; \
        DPL = (uint8_t)delay; \
        __asm \
        lcall _sys_delay_us ; called in asm since sdcc cannot recognize that _sys_delay_us is __naked and tries to push/pop r0-r7 in different banks \
        __endasm; \
        FLASH_STOP; \
    } \
} while (0)

void flash_f3clk_isr(void)  __interrupt (MACRO_CONCAT(FLASH_F3CLK, _VECTOR)) __using(FLASH_ISR_BANK)
{
    FLASH_SONY_COMM_CLK (
        flash_data, FLASH_F3CLK, FLASH_F2DAT,
        thtl<(65536-FOSC/12/1000+FOSC/12*6/100000), 
        thtl<(65536-FOSC/12/1000+FOSC/12*13/100000), 
        thtl<(65536-FOSC/12/1000+FOSC/12*22/100000), 
        thtl<(65536-FOSC/12/1000+FOSC/12*33/100000), 
        timer_start(), timer_stop(),
        FLASH_F2DAT = 0, FLASH_F2DAT = 1, 
        FLASH_PREPARE,
        delay(FLASH_PREFLASH_DELAY),
        preflash() 
    );
}

void flash_f1sync_isr(void) __interrupt (MACRO_CONCAT(FLASH_F1SYNC, _VECTOR)) __using(FLASH_ISR_BANK)
{
    if (
#ifdef F1SYNC_NEGATIVE    
    !FLASH_F1SYNC
#else
    FLASH_F1SYNC
#endif
    ) FLASH_SONY_COMM_FIRE (
        flash_data, 
        FLASH_F2DAT = 0, FLASH_F2DAT = 1, 
        delay(FLASH_FORMAL_DELAY), flash() 
    );
}

void flash_timer_isr(void)  __interrupt (TMR0_VECTOR) __using(FLASH_ISR_BANK)
{
    FLASH_SONY_COMM_TIMEOUT ( 
        flash_data, FLASH_F3CLK, 
        FLASH_F2DAT = 1, timer_stop() 
     );
}

#pragma save
#pragma disable_warning 126 // unreachable code by some setup macros
void flash_setup(void)
{
#ifdef F1SYNC_NEGATIVE
    FLASH_F1SYNC=1;  pio_config(pio_pnn(FLASH_F1SYNC), PIO_INPUT | PIO_SCHMITT | PIO_PULLUP);
#elif defined(PIO_PULLDOWN)
    FLASH_F1SYNC=0;  pio_config(pio_pnn(FLASH_F1SYNC), PIO_INPUT | PIO_SCHMITT | PIO_PULLDOWN);
#else
    FLASH_F1SYNC=0;  pio_config(pio_pnn(FLASH_F1SYNC), PIO_INPUT | PIO_SCHMITT); // it's best to have a pull-down resistor outside.
#endif
    FLASH_F2DAT=1;   pio_config(pio_pnn(FLASH_F2DAT), PIO_BIDIR | PIO_SCHMITT | PIO_PULLUP);
    FLASH_F3CLK=0;   pio_config(pio_pnn(FLASH_F3CLK), PIO_INPUT | PIO_SCHMITT);

    // FLASH_F3CLK/INT0 and FLASH_F1SYNC/INT1 intr.
    pio_int0_config(0, 1, FLASH_ISR_PRIORITY);
    pio_int1_config(0, 1, FLASH_ISR_PRIORITY);
        
    // prepare timer 0 for flash, in T12 mode, not started, will raise intr.
    tmr0_setup(TMR0_RESET16, 0, 1, 0, 1, 0, 0, 0);
    tmr0_intr_priority(FLASH_ISR_PRIORITY); // must be the same as 
}
#pragma restore
