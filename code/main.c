#include "main.h"

#include "stc/mem.h"
#include "stc/pio.h"
#include "stc/tmr.h"
#include "stc/sys.h"
#include "stc/ser.h"
#include "stc/adc.h"
#include "flash.h"

/*
this is a small flash with small Xenon tube and capacitor (GN6), 
so uses nearly a 1/4 full power (at flash_time_of_level[0]) as base/pre-flash power.
this table needs to be recalibrated after changing the Xenon tube and capacitor models. 
*/
const uint16_t flash_time_of_level[64] = {
52,61,72,87,104,126,151,183,
318,318,318,318,318,318,318,318,
318,318,318,318,318,318,318,318,
318,318,318,318,318,318,318,318,
12,12,12,12,12,12,13,14,
14,14,14,15,15,15,15,16,
17,18,19,19,20,21,21,22,
24,26,28,30,33,37,41,47
};


uint16_t volt_vdd_mv = 4000;
uint16_t volt_high = 0;

// ADC ref voltage, normally 1190mV
static uint16_t adc_ref=1190;

static __bit HV_disable = 0;
static __bit HV_on = 0;

#pragma save
#pragma disable_warning 126 // unreachable code by some setup macros
static void setup(void)
{
    sys_wdt_enable(1000, 0);
            
    // set ports (pins connected to camera are excluded)
    pio_disable_all();
    pio_reset(0);   // not to use reset pin
    pio_mclk(0, 0); // not to output sys clock
    VHSAMP=0;  pio_config(pio_pnn(VHSAMP), PIO_ANALOG); // VHSAMP
    RXD=1;     pio_config(pio_pnn(RXD), PIO_BIDIR | PIO_SCHMITT); 
    TXD=1;     pio_config(pio_pnn(TXD), PIO_BIDIR | PIO_SCHMITT); 
    LED=0;     pio_config(pio_pnn(LED), PIO_OUTPUT);
    P11=0;     pio_config(pio_pnn(P11), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P12=0;     pio_config(pio_pnn(P12), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P13=0;     pio_config(pio_pnn(P13), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P14=0;     pio_config(pio_pnn(P14), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P15=0;     pio_config(pio_pnn(P15), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P16=0;     pio_config(pio_pnn(P16), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    P17=0;     pio_config(pio_pnn(P17), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // to drive IGBT
    VHCTL=0;   pio_config(pio_pnn(VHCTL), PIO_OUTPUT | PIO_STRONG | PIO_FAST); // maybe needs to drive MOS

    // serial port 1 as debug port
    ser1_setup(BAUDRATE, 1, SER1_P30P31, 0); // use timer 1 to drive it, not to use intr.
    debug(1, "Starting\n");
        
    // LVD level
    sys_lvd_setup(3000, 0, 0);
    
    // timer 2 ticks every 10ms, started, will raise intr.
    tmr2_setup_reload24(100, 1, 1, 0, 0);

    // setup ADC
    adc_setup(ADC_RATE, 0, 0); // not to raise intr.
    debug(1, "ADC Rate = %u kHz\n", (uint16_t)(adc_real_speed(ADC_RATE)/1000));
#ifdef ADC_REF_MV
    adc_ref = ADC_REF_MV;
#else
    adc_ref = adc_ref_mv();
    if (adc_ref<1000 || adc_ref>1300) adc_ref=1190; // maybe VRef is not writen into ROM, so use the default
#endif
    debug(1, "ADC Ref = %u mV\n", adc_ref);
    
#ifdef USE_PWM_STEP_UP
    CMPCR2 = DISFLT; // not inv., no filter
    CMPEXCFG = 0;
    CMPCR1 = CMPEN | 0x04; // enable and use P36 as negative input
    PWMA_CCER1 = 0x00; // disable output for setting up
    PWMA_CR1 = 0x80; // ARR pre-load, stopped for setting up
    PWMA_CR2 = 0; 
    PWMA_RCR = 0;
    PWMA_IER = 0; // no intr. used
    PWMA_CCMR1 = 0x68; // PWM mode1, CCR pre-load
#if FOSC<20000000
#error PWM algorithm only work in at least 20MHz
#endif
    PWMA_PSCRH = 0;  // no clock pre-scale 
    PWMA_PSCRL = 0;
    PWMA_CNTRH = 0;
    PWMA_CNTRL = 0;
    PWMA_CCR1H = (uint16_t)(1.5476e-6*FOSC)>>8 ; // 4.2V, 5uH, 1.5476us -> 1.3A
    PWMA_CCR1L = (uint8_t)(uint16_t)(1.5476e-6*FOSC);
    PWMA_ARRH = 0xFF; // initialized maximum period
    PWMA_ARRL = 0xFF;
    PWMA_BKR = 0x3C; // MOE=0, AOE=0, BKP=1, BKE=1, OSSR=1, OSSI=1
    PWMA_OISR = 0; // idle state: OC1=0
    PWMA_PS = 0; // PWM1P in P10 
    PWMA_ETRPS = 0x07; // use comparator output as BRK
    PWMA_IOAUX = 0; 
    PWMA_ENO = 0x01; // enable PWM1P output
    PWMA_CCER1 = 0x01; // enable CC1P
    PWMA_CR1 |= 0x01; // start 
#endif    
}
#pragma restore

// timer 2 as system tick
static __data volatile uint16_t tick_10ms_isr = 0;
void tmr2_isr(void) __interrupt (TMR2_VECTOR) __naked
{
    // _tick_10ms_isr++
    __asm
    push    acc
    push    psw
    inc _tick_10ms_isr
    clr a
    cjne a, _tick_10ms_isr, 00010$
    inc (_tick_10ms_isr + 1)
00010$:
    pop psw
    pop acc
    reti
    __endasm;
}

uint16_t main_tick_get(void) __naked
{
    __asm
    anl _IE2, #(~ET2)
    nop
    nop
    mov dpl, (_tick_10ms_isr)
    mov dph, (_tick_10ms_isr+1)
    orl _IE2, #(ET2)
    ret
    __endasm;
}

static void shutdown(void)
{
    FLASH_STOP;
    HV_on = 0; // turn off high voltage
#ifdef USE_PWM_STEP_UP
    PWMA_BKR &= ~0xC0; // MOE=AOE=0 
#else
    VHCTL = 0;  
#endif    
    
    LED=0;
    sys_delay_ms(50);
}

// main entry
void main(void)
{
    
    EA = 0;
    nop();
    nop();
    mem_xram_enable();
    setup();
    flash_setup();
    EA = 1;
    
    // main loop
    while(1) {
        // feed the dog
        sys_wdt_clear();
        
        static uint16_t loops=0;
        ++loops;

        // power control
        if (PCON & LVDF || volt_vdd_mv<3200 || HV_disable) {
            HV_on = 0;
        } else if (volt_high<(uint16_t)(VH_DEST)-5) {
            HV_on = 1;
        } else if (volt_high>(uint16_t)(VH_DEST)+5) {
            HV_on = 0;
        }
        
#ifdef USE_PWM_STEP_UP
        if (HV_on) PWMA_BKR |= 0xC0; // MOE=AOE=1
        else PWMA_BKR &= ~0xC0; // MOE=AOE=0
#else
        VHCTL = HV_on;  
#endif    

        //To speed up the cycle turnaround, the tasks are spreaded using task number, which should be at 1-255
        static __data uint8_t taskno = 0;
        ++taskno;
        if (taskno == 1) { // get device voltages
            uint16_t t16 = adc_get(ADC_VREF_CH);
            t16 = adc_get(ADC_VREF_CH); // double get to avoid cross-interference
            if (t16<=4096) t16 = adc_get(ADC_VREF_CH);
            if (t16<=256) continue; // sometimes get 0, seems to be the "zero value" bug of STC ADC, many have encountered it too
            // adc_value/65536*Vdd = adc_ref
            // Vdd = adc_ref * 65536 / adc_value
            t16 = (uint16_t)((((uint32_t)adc_ref<<16)+(t16>>1))/t16);
            t16 = ((volt_vdd_mv<<1)+volt_vdd_mv+t16+2)>>2; // a simple filter
            EA = 0; // guarantee actomic data
            nop();
            nop();
            volt_vdd_mv=t16;
            EA = 1;
        } else if (taskno == 2) { // get high voltage
            uint16_t t16 = adc_get(ADC_VHSAMP_CH);
            t16 = adc_get(ADC_VHSAMP_CH); // double get to avoid cross-interference
            if (t16<=4096) t16 = adc_get(ADC_VHSAMP_CH);
            if (t16<=256) continue; // sometimes get 0 or noises, seems to be the "zero value" bug of STC ADC, many have encountered it too
            // adc_value/65536*volt_vdd_mv/1000 = volt_high*VH_RATIO+VH_BIAS
            // volt_high = (adc_value/65536*volt_vdd_mv/1000 - VH_BIAS)/VH_RATIO
            // volt_high = (1049*(adc_value/64)*volt_vdd_mv/65536 - VH_BIAS*16384)*(4/VH_RATIO)/65536
            t16 = (1049UL*volt_vdd_mv*(t16>>6)+32768)>>16;
            t16 = t16>(uint32_t)(VH_BIAS*16384) ? ((t16-(uint32_t)(VH_BIAS*16384))*(uint32_t)(4/VH_RATIO)+32768)>>16 : 0;
            t16 = ((volt_high<<1)+volt_high+t16+2)>>2; // a simple filter
            EA = 0; // guarantee actomic data
            nop();
            nop();
            volt_high = t16;
            EA = 1;
#ifdef USE_PWM_STEP_UP
            if (volt_high<=2) {
                PWMA_ARRH = 0xFF;
                PWMA_ARRL = 0xFF;            
            } else {
                uint16_t toff=(uint16_t)(0.08125*0.00128*FOSC)/(volt_high-2)+(uint16_t)(1.5476e-6*FOSC)+2; // 1.3/(15+1)=81.25mA, 5*(15+1)^2=1.28mH
                PWMA_ARRH = toff>>8;
                PWMA_ARRL = (uint8_t)toff;
            }
#endif
        } else if (taskno == 3) { // show LED
            if (volt_high<(uint16_t)(VH_LEAST)) {
                flash_can_fire = 0;
                if (HV_on) {
                    LED = (uint8_t)main_tick_get() & 0x10;
                } else {
                    LED = 1;
                }
            } else {
            	flash_can_fire = 1;
                LED = 1;
            } 
        } else if (taskno == 4) {
            // incoming message (1 byte only) from default serial port
            switch ((unsigned char)tolower(getchar())) {
                case 'b': printf("SP = %x, ticks = %u, loops=%u\n", SP, main_tick_get(), loops);
                          break;
                case 'd': shutdown();
                          pio_disable_all(); 
                          sys_boot_ISP();
                          break;
                case 'r': shutdown();
                          pio_disable_all();
                          sys_boot();
                          break;
                case 'a': printf("VH = %u, VDD = %u mV, VH = %u V\n", HV_on, volt_vdd_mv, volt_high);
                          break;
                case 'p': printf("VH = %u, LVD=%u, LED = %u\n", HV_on, (PCON & LVDF)?1:0, LED);
                          printf("F1SYNC = %u, F2DAT = %u, F3CLK = %u\n", FLASH_F1SYNC, FLASH_F2DAT, FLASH_F3CLK);
                          break;
                case 'c': HV_on = 0;
                          HV_disable = 1;
                          sys_delay_ms(1);
                          printf("VH = %u, VDD = %u mV, VH = %u V\n", HV_on, volt_vdd_mv, volt_high);
                          break;
                case 'x': HV_on = 0;
                          HV_disable = 0;
                          sys_delay_ms(1);
                          printf("VH = %u, VDD = %u mV, VH = %u V\n", HV_on, volt_vdd_mv, volt_high);
                          break;
                case 'f': FLASH_START;
                          sys_delay_us(30);
                          FLASH_STOP;
                          sys_delay_ms(20);
                          FLASH_START;
                          sys_delay_us(100);
                          FLASH_STOP;
                          break;
                case 's': printf("Sony read : ");
                		  for (uint8_t i=0; i<flash_data.rlen; i++) printf("%x ", flash_data.rbytes[i]);
                		  printf("\nSony write : ");
                		  for (uint8_t i=0; i<flash_data.wlen; i++) printf("%x ", flash_data.wbytes[i]);
                		  printf("\nPower pre=%d formal=%d", flash_power_pre, flash_power_formal);
                          printf("\nActual pre=%d formal=%d\n", flash_power_pre_act, flash_power_formal_act);
                          break;
                case 'm': static int8_t power=-15;
                          power++;
                          if (power>FLASH_LEVEL_FULL) power=-12;
                          flash_data.read.mode &= ~FLASH_SONY_READ_MODE_CONTROLLED; // manual mode
                          flash_data.read.power = ((FLASH_POWER_LEVEL_MAX-power)<<2)+15;
                          printf("Manual mode, power=%d\n", power);
						  break;    
                case '?': printf("bdrapcxfsm\n");
                          break;
            } 
        }  else taskno = 0;
    }
} 
