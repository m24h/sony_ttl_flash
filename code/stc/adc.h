#ifndef __ADC_H__
#define __ADC_H__

#include "def.h"
#include "sys.h"
#include "mem.h"

/* ADC_BITS    : the ADC bits, 10 or 12 */
/* ADC_VREF_CH : the ADC channel to sample internal 1190mV */
#if   defined(MCU_STC8H1K08) \
   || defined(MCU_STC8H1K17) \
   || defined(MCU_STC8H1K16) \
   || defined(MCU_STC8H1K24) \
   || defined(MCU_STC8H1K28)
#define ADC_BITS      10
#define ADC_VREF_CH   15 
#elif defined(MCU_STC8H3K32S2) \
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
   || defined(MCU_STC8H4K64TLCD) \
   || defined(MCU_STC8H1K08T) \
   || defined(MCU_STC8H1K17T)
#define ADC_BITS 12
#define ADC_VREF_CH   15
#elif defined(MCU_STC8G1K08_38I) \
   || defined(MCU_STC8G1K17_38I) \
   || defined(MCU_STC8G1K08T) \
   || defined(MCU_STC8G1K17T) \
   || defined(MCU_STC8G1K08A) \
   || defined(MCU_STC8G1K17A) \
   || defined(MCU_STC8G2K32S4) \
   || defined(MCU_STC8G2K48S4) \
   || defined(MCU_STC8G2K60S4) \
   || defined(MCU_STC8G2K64S4) \
   || defined(MCU_STC8G2K32S2) \
   || defined(MCU_STC8G2K48S2) \
   || defined(MCU_STC8G2K60S2) \
   || defined(MCU_STC8G2K64S2)
#define ADC_BITS 10
#define ADC_VREF_CH   15
#else
#error Not a supported MCU
#endif

#ifdef FOSC
/* setup ADC with the rate specified by `rate`, CSSETUP=0, CSHOLD=1 */
/* According to the STC manual, some speeds may not be achievable, and the closest and slightly lower speed will be adopted. */
#define adc_setup(rate, right_align, intr) do { \
	EADC = 0;  /* disable intr. */ \
	ADC_CONTR = ADC_POWER;  /* power on, but not started */ \
	sys_delay_ms(10);  /* wait for ADC POWER to be stable */ \
	ADCCFG = ((right_align)?RESFMT:0) | CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(1+32+2+ADC_BITS)), 0, 15); \
	ADCTIM = 0x20 | CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(1+32+2+ADC_BITS)), 0, 15)+1))-(1+2+ADC_BITS), 11, 31); \
	if (intr) EADC=1; \
} while(0)

/* get real ADC speed for specified `rate` in adc_setup() */
#define adc_real_speed(rate) (FOSC/(2UL*(CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(1+32+2+ADC_BITS)), 0, 15)+1)*(1+2+ADC_BITS+CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(CLAMP((FOSC-1L)/(2L*(uint32_t)(rate)*(1+32+2+ADC_BITS)), 0, 15)+1))-(1+2+ADC_BITS), 11, 31)+1)))

#endif /* #ifdef FOSC */

/* set up ADC intr. priority */
#define adc_intr_priority(priority) do { \
	if ((priority)>1) IPH |= PADCH; \
	else IPH &= ~PADCH; \
	PADC = (priority) & 1; \
} while (0)

/* adc_ref_mv() : get adc reference voltage from CHIPID/ROM/default in MCU 
   Notice : In fact, there is often no correct data, judgment is required */
#if defined(MCU_STC8H8K32U) \
	|| defined(MCU_STC8H8K48U) \
	|| defined(MCU_STC8H8K60U) \
	|| defined(MCU_STC8H8K64U) \
	|| defined(MCU_STC8H4K32TLCD) \
	|| defined(MCU_STC8H4K48TLCD) \
	|| defined(MCU_STC8H4K60TLCD) \
	|| defined(MCU_STC8H4K64TLCD) \
	|| defined(MCU_STC8H1K08T) \
	|| defined(MCU_STC8H1K12T) \
	|| defined(MCU_STC8H1K17T)
uint16_t adc_ref_mv_cid(void) __naked;
#define adc_ref_mv() adc_ref_mv_cid()
#else 
uint16_t adc_ref_mv_rom(void) __naked;
#define adc_ref_mv() adc_ref_mv_rom()
#endif

/* sample and get ADC value */
uint16_t adc_get(uint8_t chan) __naked;

#endif