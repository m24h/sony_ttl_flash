#ifndef __STC8G_H__
#define __STC8G_H__

/////////////////////////////////////////////////

//包含本头文件后,不用另外再包含"REG51.H"

__sfr       __at(0x80)      P0;
    __sbit  __at(0x80)      P00;
    __sbit  __at(0x81)      P01;
    __sbit  __at(0x82)      P02;
    __sbit  __at(0x83)      P03;
    __sbit  __at(0x84)      P04;
    __sbit  __at(0x85)      P05;
    __sbit  __at(0x86)      P06;
    __sbit  __at(0x87)      P07;

__sfr       __at(0x81)      SP;
__sfr       __at(0x82)      DPL;
__sfr       __at(0x83)      DPH;
__sfr       __at(0x84)      S4CON;
    #define S4SM0                   0x80
    #define S4ST4                   0x40
    #define S4SM2                   0x20
    #define S4REN                   0x10
    #define S4TB8                   0x08
    #define S4RB8                   0x04
    #define S4TI                    0x02
    #define S4RI                    0x01

__sfr       __at(0x85)      S4BUF;
__sfr       __at(0x87)      PCON;
    #define SMOD                    0x80
    #define SMOD0                   0x40
    #define LVDF                    0x20
    #define POF                     0x10
    #define GF1                     0x08
    #define GF0                     0x04
    #define PD                      0x02
    #define IDL                     0x01

__sfr       __at(0x88)      TCON;
    __sbit  __at(0x8F)      TF1;
    __sbit  __at(0x8E)      TR1;
    __sbit  __at(0x8D)      TF0;
    __sbit  __at(0x8C)      TR0;
    __sbit  __at(0x8B)      IE1;
    __sbit  __at(0x8A)      IT1;
    __sbit  __at(0x89)      IE0;
    __sbit  __at(0x88)      IT0;

__sfr       __at(0x89)      TMOD;
    #define T1_GATE                 0x80
    #define T1_CT                   0x40
    #define T1_M1                   0x20
    #define T1_M0                   0x10
    #define T0_GATE                 0x08
    #define T0_CT                   0x04
    #define T0_M1                   0x02
    #define T0_M0                   0x01
    
__sfr       __at(0x8A)      TL0;
__sfr       __at(0x8B)      TL1;
__sfr       __at(0x8C)      TH0;
__sfr       __at(0x8D)      TH1;

__sfr       __at(0x8E)      AUXR;
    #define T0x12                   0x80
    #define T1x12                   0x40
    #define S1M0x6                  0x20
    #define T2R                     0x10
    #define T2_CT                   0x08
    #define T2x12                   0x04
    #define EXTRAM                  0x02
    #define S1BRT                   0x01
    #define S1ST2                   0x01
    
__sfr       __at(0x8F)      INTCLKO;
    #define EX4                     0x40
    #define EX3                     0x20
    #define EX2                     0x10
    #define T2CLKO                  0x04
    #define T1CLKO                  0x02
    #define T0CLKO                  0x01

__sfr       __at(0x90)      P1;
    __sbit  __at(0x90)      P10;
    __sbit  __at(0x91)      P11;
    __sbit  __at(0x92)      P12;
    __sbit  __at(0x93)      P13;
    __sbit  __at(0x94)      P14;
    __sbit  __at(0x95)      P15;
    __sbit  __at(0x96)      P16;
    __sbit  __at(0x97)      P17;

__sfr       __at(0x91)      P1M1;
__sfr       __at(0x92)      P1M0;
__sfr       __at(0x93)      P0M1;
__sfr       __at(0x94)      P0M0;
__sfr       __at(0x95)      P2M1;
__sfr       __at(0x96)      P2M0;

__sfr       __at(0x98)      SCON;
    __sbit  __at(0x9F)      SM0;
    __sbit  __at(0x9E)      SM1;
    __sbit  __at(0x9D)      SM2;
    __sbit  __at(0x9C)      REN;
    __sbit  __at(0x9B)      TB8;
    __sbit  __at(0x9A)      RB8;
    __sbit  __at(0x99)      TI;
    __sbit  __at(0x98)      RI;

__sfr       __at(0x99)      SBUF;
__sfr       __at(0x9A)      S2CON;
    #define S2SM0                   0x80
    #define S2SM1                   0x40
    #define S2SM2                   0x20
    #define S2REN                   0x10
    #define S2TB8                   0x08
    #define S2RB8                   0x04
    #define S2TI                    0x02
    #define S2RI                    0x01

__sfr       __at(0x9B)      S2BUF;
__sfr       __at(0x9D)      IRCBAND;
    #define HIRCSEL                0x01

__sfr       __at(0x9E)      LIRTRIM;
__sfr       __at(0x9F)      IRTRIM;

__sfr       __at(0xA0)      P2;
    __sbit  __at(0xA0)      P20;
    __sbit  __at(0xA1)      P21;
    __sbit  __at(0xA2)      P22;
    __sbit  __at(0xA3)      P23;
    __sbit  __at(0xA4)      P24;
    __sbit  __at(0xA5)      P25;
    __sbit  __at(0xA6)      P26;
    __sbit  __at(0xA7)      P27;

__sfr       __at(0xA2)      P_SW1;
    #define UART1_S1                0x00
    #define UART1_S2                0x40
    #define UART1_S3                0x80
    #define UART1_S4                0xc0
    #define SPI_S1                  0x00
    #define SPI_S2                  0x04
    #define SPI_S3                  0x08
    #define SPI_S4                  0x0c
    #define PCA_S1				    0x00
    #define PCA_S2				    0x10
    #define PCA_S3				    0x20


__sfr       __at(0xA8)      IE;
    __sbit  __at(0xAF)      EA;
    __sbit  __at(0xAE)      ELVD;
    __sbit  __at(0xAD)      EADC;
    __sbit  __at(0xAC)      ES;
    __sbit  __at(0xAB)      ET1;
    __sbit  __at(0xAA)      EX1;
    __sbit  __at(0xA9)      ET0;
    __sbit  __at(0xA8)      EX0;

__sfr       __at(0xA9)      SADDR;
__sfr       __at(0xAA)      WKTCL;
__sfr       __at(0xAB)      WKTCH;
    #define WKTEN                   0x80

__sfr       __at(0xAC)      S3CON;
    #define S3SM0                   0x80
    #define S3ST3                   0x40
    #define S3SM2                   0x20
    #define S3REN                   0x10
    #define S3TB8                   0x08
    #define S3RB8                   0x04
    #define S3TI                    0x02
    #define S3RI                    0x01
    
__sfr       __at(0xAD)      S3BUF;
__sfr       __at(0xAE)      TA;
__sfr       __at(0xAF)      IE2;
    #define ETKSUI                  0x80
    #define ET4                     0x40
    #define ET3                     0x20
    #define ES4                     0x10
    #define ES3                     0x08
    #define ET2                     0x04
    #define ESPI                    0x02
    #define ES2                     0x01
    
__sfr       __at(0xB0)      P3;
    __sbit  __at(0xB0)      P30;
    __sbit  __at(0xB1)      P31;
    __sbit  __at(0xB2)      P32;
    __sbit  __at(0xB3)      P33;
    __sbit  __at(0xB4)      P34;
    __sbit  __at(0xB5)      P35;
    __sbit  __at(0xB6)      P36;
    __sbit  __at(0xB7)      P37;

    __sbit  __at(0xB7)      RD;
    __sbit  __at(0xB6)      WR;
    __sbit  __at(0xB5)      T1;
    __sbit  __at(0xB4)      T0;
    __sbit  __at(0xB3)      INT1;
    __sbit  __at(0xB2)      INT0;
    __sbit  __at(0xB1)      TXD;
    __sbit  __at(0xB0)      RXD;

__sfr       __at(0xB1)      P3M1;
__sfr       __at(0xB2)      P3M0;
__sfr       __at(0xB3)      P4M1;
__sfr       __at(0xB4)      P4M0;

__sfr       __at(0xB5)      IP2;
    #define PPWM2FD                 0x80
    #define PTKSU                   0x80
    #define PI2C                    0x40
    #define PCMP                    0x20
    #define PX4                     0x10
    #define PPWM0FD                 0x08
    #define PPWM0                   0x04
    #define PSPI                    0x02
    #define PS2                     0x01

__sfr       __at(0xB6)      IP2H;
    #define PPWM2FDH                0x80
    #define PTKSUH                  0x80
    #define PI2CH                   0x40
    #define PCMPH                   0x20
    #define PX4H                    0x10
    #define PPWM0FDH                0x08
    #define PPWM0H                  0x04
    #define PSPIH                   0x02
    #define PS2H                    0x01
    
__sfr       __at(0xB7)      IPH;
    #define PPCAH                   0x80
    #define PLVDH                   0x40
    #define PADCH                   0x20
    #define PSH                     0x10
    #define PT1H                    0x08
    #define PX1H                    0x04
    #define PT0H                    0x02
    #define PX0H                    0x01
    
__sfr       __at(0xB8)      IP;
    __sbit  __at(0xBF)      PPCA;
    __sbit  __at(0xBE)      PLVD;
    __sbit  __at(0xBD)      PADC;
    __sbit  __at(0xBC)      PS;
    __sbit  __at(0xBB)      PT1;
    __sbit  __at(0xBA)      PX1;
    __sbit  __at(0xB9)      PT0;
    __sbit  __at(0xB8)      PX0;

__sfr       __at(0xB9)      SADEN;
__sfr       __at(0xBA)      P_SW2;
    #define EAXFR                   0x80
    #define I2C_S1                  0x00
    #define I2C_S2                  0x10
    #define I2C_S3                  0x20
    #define I2C_S4                  0x30
    #define CMPO_S1                 0x00
    #define CMPO_S2                 0x08
    #define UART4_S1                0x00
    #define UART4_S2                0x04
    #define UART3_S1                0x00
    #define UART3_S2                0x02
    #define UART2_S1                0x00
    #define UART2_S2                0x01

__sfr       __at(0xBC)      ADC_CONTR;
    #define ADC_POWER               0x80
    #define ADC_START               0x40
    #define ADC_FLAG                0x20
    #define ADC_EPWMT               0x10
    
__sfr       __at(0xBD)      ADC_RES;
__sfr       __at(0xBE)      ADC_RESL;

__sfr       __at(0xC0)      P4;
    __sbit  __at(0xC0)      P40;
    __sbit  __at(0xC1)      P41;
    __sbit  __at(0xC2)      P42;
    __sbit  __at(0xC3)      P43;
    __sbit  __at(0xC4)      P44;
    __sbit  __at(0xC5)      P45;
    __sbit  __at(0xC6)      P46;
    __sbit  __at(0xC7)      P47;

__sfr       __at(0xC1)      WDT_CONTR;
    #define WDT_FLAG                0x80
    #define EN_WDT                  0x20
    #define CLR_WDT                 0x10
    #define IDL_WDT                 0x08

__sfr       __at(0xC2)      IAP_DATA;
__sfr       __at(0xC3)      IAP_ADDRH;
__sfr       __at(0xC4)      IAP_ADDRL;
__sfr       __at(0xC5)      IAP_CMD;
__sfr       __at(0xC6)      IAP_TRIG;
__sfr       __at(0xC7)      IAP_CONTR;
    #define IAPEN                   0x80
    #define SWBS                    0x40
    #define SWRST                   0x20
    #define CMD_FAIL                0x10

__sfr       __at(0xC8)      P5;
    __sbit  __at(0xC8)      P50;
    __sbit  __at(0xC9)      P51;
    __sbit  __at(0xCA)      P52;
    __sbit  __at(0xCB)      P53;
    __sbit  __at(0xCC)      P54;
    __sbit  __at(0xCD)      P55;
    __sbit  __at(0xCE)      P56;
    __sbit  __at(0xCF)      P57;

__sfr       __at(0xC9)      P5M1;
__sfr       __at(0xCA)      P5M0;
__sfr       __at(0xCB)      P6M1;
__sfr       __at(0xCC)      P6M0;
__sfr       __at(0xCD)      SPSTAT;
    #define SPIF                    0x80
    #define WCOL                    0x40

__sfr       __at(0xCE)      SPCTL;
    #define SSIG                    0x80
    #define SPEN                    0x40
    #define DORD                    0x20
    #define MSTR                    0x10
    #define CPOL                    0x08
    #define CPHA                    0x04
    #define SPR1                    0x02
    #define SPR0                    0x01

__sfr       __at(0xCF)      SPDAT;

__sfr       __at(0xD0)      PSW;
    __sbit  __at(0xD7)      CY;
    __sbit  __at(0xD6)      AC;
    __sbit  __at(0xD5)      F0;
    __sbit  __at(0xD4)      RS1;
    __sbit  __at(0xD3)      RS0;
    __sbit  __at(0xD2)      OV;
    __sbit  __at(0xD1)      F1;
    __sbit  __at(0xD0)      P;

__sfr       __at(0xD1)      T4T3M;
    #define T4R                     0x80
    #define T4_CT                   0x40
    #define T4x12                   0x20
    #define T4CLKO                  0x10
    #define T3R                     0x08
    #define T3_CT                   0x04
    #define T3x12                   0x02
    #define T3CLKO                  0x01

__sfr       __at(0xD2)      T4H;
__sfr       __at(0xD3)      T4L;
__sfr       __at(0xD4)      T3H;
__sfr       __at(0xD5)      T3L;
__sfr       __at(0xD6)      T2H;
__sfr       __at(0xD7)      T2L;

__sfr       __at(0xD1)      T3T4M;
__sfr       __at(0xD2)      TH4;
__sfr       __at(0xD3)      TL4;
__sfr       __at(0xD4)      TH3;
__sfr       __at(0xD5)      TL3;
__sfr       __at(0xD6)      TH2;
__sfr       __at(0xD7)      TL2;

__sfr       __at(0xD8)      CCON;
    __sbit  __at(0xDF)      CF;
    __sbit  __at(0xDE)      CR;
    __sbit  __at(0xDA)      CCF2;
    __sbit  __at(0xD9)      CCF1;
    __sbit  __at(0xD8)      CCF0;

__sfr       __at(0xD9)      CMOD;
__sfr       __at(0xDA)      CCAPM0;
__sfr       __at(0xDB)      CCAPM1;
__sfr       __at(0xDC)      CCAPM2;
__sfr       __at(0xDE)      ADCCFG;
    #define RESFMT                  0x20
    
__sfr       __at(0xDF)      IP3;
    #define PPWM4FD                 0x80
    #define PPWM5                   0x40
    #define PPWM4                   0x20
    #define PPWM3                   0x10
    #define PPWM2                   0x08
    #define PPWM1                   0x04
    #define PS4                     0x02
    #define PS3                     0x01
    
__sfr       __at(0xE0)      ACC;
__sfr       __at(0xE1)      P7M1;
__sfr       __at(0xE2)      P7M0;
__sfr       __at(0xE3)      DPS;
__sfr       __at(0xE4)      DPL1;
__sfr       __at(0xE5)      DPH1;
__sfr       __at(0xE6)      CMPCR1;
    #define CMPEN                   0x80
    #define CMPIF                   0x40
    #define PIE                     0x20
    #define NIE                     0x10
    #define CMPOE                   0x02
    #define CMPRES                  0x01
    
__sfr       __at(0xE7)      CMPCR2;
    #define INVCMPO                 0x80
    #define DISFLT                  0x40

__sfr       __at(0xE8)      P6;
    __sbit  __at(0xE8)      P60;
    __sbit  __at(0xE9)      P61;
    __sbit  __at(0xEA)      P62;
    __sbit  __at(0xEB)      P63;
    __sbit  __at(0xEC)      P64;
    __sbit  __at(0xED)      P65;
    __sbit  __at(0xEE)      P66;
    __sbit  __at(0xEF)      P67;

__sfr       __at(0xE9)      CL;
__sfr       __at(0xEA)      CCAP0L;
__sfr       __at(0xEB)      CCAP1L;
__sfr       __at(0xEC)      CCAP2L;
__sfr       __at(0xEE)      IP3H;
    #define PPWM4FDH                0x80
    #define PPWM5H                  0x40
    #define PPWM4H                  0x20
    #define PPWM3H                  0x10
    #define PPWM2H                  0x08
    #define PPWM1H                  0x04
    #define PS4H                    0x02
    #define PS3H                    0x01

__sfr       __at(0xEF)      AUXINTIF;
    #define INT4IF                  0x40
    #define INT3IF                  0x20
    #define INT2IF                  0x10
    #define T2IF                    0x01

__sfr       __at(0xF0)      B;
__sfr       __at(0xF1)      PWMSET;
__sfr       __at(0xF2)      PCA_PWM0;
__sfr       __at(0xF3)      PCA_PWM1;
__sfr       __at(0xF4)      PCA_PWM2;
__sfr       __at(0xF5)      IAP_TPS;
__sfr       __at(0xF6)      PWMCFG01;
__sfr       __at(0xF7)      PWMCFG23;

__sfr       __at(0xF8)      P7;
    __sbit  __at(0xF8)      P70;
    __sbit  __at(0xF9)      P71;
    __sbit  __at(0xFA)      P72;
    __sbit  __at(0xFB)      P73;
    __sbit  __at(0xFC)      P74;
    __sbit  __at(0xFD)      P75;
    __sbit  __at(0xFE)      P76;
    __sbit  __at(0xFF)      P77;

__sfr       __at(0xF9)      CH;
__sfr       __at(0xFA)      CCAP0H;
__sfr       __at(0xFB)      CCAP1H;
__sfr       __at(0xFC)      CCAP2H;
__sfr       __at(0xFE)      PWMCFG45;
__sfr       __at(0xFF)      RSTCFG;
    #define ENLVR                   0x40
    #define P54RST                  0x10
    
//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////

__xdata volatile unsigned short __at(0xFF00) PWM0C;
__xdata volatile unsigned char  __at(0xFF00) PWM0CH;
__xdata volatile unsigned char  __at(0xFF01) PWM0CL;
__xdata volatile unsigned char  __at(0xFF02) PWM0CKS;
__xdata volatile unsigned short __at(0xFF03) PWM0TADC;
__xdata volatile unsigned char  __at(0xFF03) PWM0TADCH;
__xdata volatile unsigned char  __at(0xFF04) PWM0TADCL;
__xdata volatile unsigned char  __at(0xFF05) PWM0IF;
__xdata volatile unsigned char  __at(0xFF06) PWM0FDCR;
__xdata volatile unsigned short __at(0xFF10) PWM00T1;
__xdata volatile unsigned char  __at(0xFF11) PWM00T1L;
__xdata volatile unsigned short __at(0xFF12) PWM00T2;
__xdata volatile unsigned char  __at(0xFF12) PWM00T2H;
__xdata volatile unsigned char  __at(0xFF13) PWM00T2L;
__xdata volatile unsigned char  __at(0xFF14) PWM00CR;
__xdata volatile unsigned char  __at(0xFF15) PWM00HLD;
__xdata volatile unsigned short __at(0xFF18) PWM01T1;
__xdata volatile unsigned char  __at(0xFF18) PWM01T1H;
__xdata volatile unsigned char  __at(0xFF19) PWM01T1L;
__xdata volatile unsigned short __at(0xFF1A) PWM01T2;
__xdata volatile unsigned char  __at(0xFF1A) PWM01T2H;
__xdata volatile unsigned char  __at(0xFF1B) PWM01T2L;
__xdata volatile unsigned char  __at(0xFF1C) PWM01CR;
__xdata volatile unsigned char  __at(0xFF1D) PWM01HLD;
__xdata volatile unsigned short __at(0xFF20) PWM02T1;
__xdata volatile unsigned char  __at(0xFF20) PWM02T1H;
__xdata volatile unsigned char  __at(0xFF21) PWM02T1L;
__xdata volatile unsigned short __at(0xFF22) PWM02T2;
__xdata volatile unsigned char  __at(0xFF22) PWM02T2H;
__xdata volatile unsigned char  __at(0xFF23) PWM02T2L;
__xdata volatile unsigned char  __at(0xFF24) PWM02CR;
__xdata volatile unsigned char  __at(0xFF25) PWM02HLD;
__xdata volatile unsigned short __at(0xFF28) PWM03T1;
__xdata volatile unsigned char  __at(0xFF28) PWM03T1H;
__xdata volatile unsigned char  __at(0xFF29) PWM03T1L;
__xdata volatile unsigned short __at(0xFF2A) PWM03T2;
__xdata volatile unsigned char  __at(0xFF2A) PWM03T2H;
__xdata volatile unsigned char  __at(0xFF2B) PWM03T2L;
__xdata volatile unsigned char  __at(0xFF2C) PWM03CR;
__xdata volatile unsigned char  __at(0xFF2D) PWM03HLD;
__xdata volatile unsigned short __at(0xFF30) PWM04T1;
__xdata volatile unsigned char  __at(0xFF30) PWM04T1H;
__xdata volatile unsigned char  __at(0xFF31) PWM04T1L;
__xdata volatile unsigned short __at(0xFF32) PWM04T2;
__xdata volatile unsigned char  __at(0xFF32) PWM04T2H;
__xdata volatile unsigned char  __at(0xFF33) PWM04T2L;
__xdata volatile unsigned char  __at(0xFF34) PWM04CR;
__xdata volatile unsigned char  __at(0xFF35) PWM04HLD;
__xdata volatile unsigned short __at(0xFF38) PWM05T1;
__xdata volatile unsigned char  __at(0xFF38) PWM05T1H;
__xdata volatile unsigned char  __at(0xFF39) PWM05T1L;
__xdata volatile unsigned short __at(0xFF3A) PWM05T2;
__xdata volatile unsigned char  __at(0xFF3A) PWM05T2H;
__xdata volatile unsigned char  __at(0xFF3B) PWM05T2L;
__xdata volatile unsigned char  __at(0xFF3C) PWM05CR;
__xdata volatile unsigned char  __at(0xFF3D) PWM05HLD;
__xdata volatile unsigned short __at(0xFF40) PWM06T1;
__xdata volatile unsigned char  __at(0xFF40) PWM06T1H;
__xdata volatile unsigned char  __at(0xFF41) PWM06T1L;
__xdata volatile unsigned short __at(0xFF42) PWM06T2;
__xdata volatile unsigned char  __at(0xFF42) PWM06T2H;
__xdata volatile unsigned char  __at(0xFF43) PWM06T2L;
__xdata volatile unsigned char  __at(0xFF44) PWM06CR;
__xdata volatile unsigned char  __at(0xFF45) PWM06HLD;
__xdata volatile unsigned short __at(0xFF48) PWM07T1;
__xdata volatile unsigned char  __at(0xFF48) PWM07T1H;
__xdata volatile unsigned char  __at(0xFF49) PWM07T1L;
__xdata volatile unsigned short __at(0xFF4A) PWM07T2;
__xdata volatile unsigned char  __at(0xFF4A) PWM07T2H;
__xdata volatile unsigned char  __at(0xFF4B) PWM07T2L;
__xdata volatile unsigned char  __at(0xFF4C) PWM07CR;
__xdata volatile unsigned char  __at(0xFF4D) PWM07HLD;
__xdata volatile unsigned short __at(0xFF50) PWM1C;
__xdata volatile unsigned char  __at(0xFF50) PWM1CH;
__xdata volatile unsigned char  __at(0xFF51) PWM1CL;
__xdata volatile unsigned char  __at(0xFF52) PWM1CKS;
__xdata volatile unsigned char  __at(0xFF55) PWM1IF;
__xdata volatile unsigned char  __at(0xFF56) PWM1FDCR;
__xdata volatile unsigned short __at(0xFF60) PWM10T1;
__xdata volatile unsigned char  __at(0xFF60) PWM10T1H;
__xdata volatile unsigned char  __at(0xFF61) PWM10T1L;
__xdata volatile unsigned short __at(0xFF62) PWM10T2;
__xdata volatile unsigned char  __at(0xFF62) PWM10T2H;
__xdata volatile unsigned char  __at(0xFF63) PWM10T2L;
__xdata volatile unsigned char  __at(0xFF64) PWM10CR;
__xdata volatile unsigned char  __at(0xFF65) PWM10HLD;
__xdata volatile unsigned short __at(0xFF68) PWM11T1;
__xdata volatile unsigned char  __at(0xFF68) PWM11T1H;
__xdata volatile unsigned char  __at(0xFF69) PWM11T1L;
__xdata volatile unsigned short __at(0xFF6A) PWM11T2;
__xdata volatile unsigned char  __at(0xFF6A) PWM11T2H;
__xdata volatile unsigned char  __at(0xFF6B) PWM11T2L;
__xdata volatile unsigned char  __at(0xFF6C) PWM11CR;
__xdata volatile unsigned char  __at(0xFF6D) PWM11HLD;
__xdata volatile unsigned short __at(0xFF70) PWM12T1;
__xdata volatile unsigned char  __at(0xFF70) PWM12T1H;
__xdata volatile unsigned char  __at(0xFF71) PWM12T1L;
__xdata volatile unsigned short __at(0xFF72) PWM12T2;
__xdata volatile unsigned char  __at(0xFF72) PWM12T2H;
__xdata volatile unsigned char  __at(0xFF73) PWM12T2L;
__xdata volatile unsigned char  __at(0xFF74) PWM12CR;
__xdata volatile unsigned char  __at(0xFF75) PWM12HLD;
__xdata volatile unsigned short __at(0xFF78) PWM13T1;
__xdata volatile unsigned char  __at(0xFF78) PWM13T1H;
__xdata volatile unsigned char  __at(0xFF79) PWM13T1L;
__xdata volatile unsigned short __at(0xFF7A) PWM13T2;
__xdata volatile unsigned char  __at(0xFF7A) PWM13T2H;
__xdata volatile unsigned char  __at(0xFF7B) PWM13T2L;
__xdata volatile unsigned char  __at(0xFF7C) PWM13CR;
__xdata volatile unsigned char  __at(0xFF7D) PWM13HLD;
__xdata volatile unsigned short __at(0xFF80) PWM14T1;
__xdata volatile unsigned char  __at(0xFF80) PWM14T1H;
__xdata volatile unsigned char  __at(0xFF81) PWM14T1L;
__xdata volatile unsigned short __at(0xFF82) PWM14T2;
__xdata volatile unsigned char  __at(0xFF82) PWM14T2H;
__xdata volatile unsigned char  __at(0xFF83) PWM14T2L;
__xdata volatile unsigned char  __at(0xFF84) PWM14CR;
__xdata volatile unsigned char  __at(0xFF85) PWM14HLD;
__xdata volatile unsigned short __at(0xFF88) PWM15T1;
__xdata volatile unsigned char  __at(0xFF88) PWM15T1H;
__xdata volatile unsigned char  __at(0xFF89) PWM15T1L;
__xdata volatile unsigned short __at(0xFF8A) PWM15T2;
__xdata volatile unsigned char  __at(0xFF8A) PWM15T2H;
__xdata volatile unsigned char  __at(0xFF8B) PWM15T2L;
__xdata volatile unsigned char  __at(0xFF8C) PWM15CR;
__xdata volatile unsigned char  __at(0xFF8D) PWM15HLD;
__xdata volatile unsigned short __at(0xFF90) PWM16T1;
__xdata volatile unsigned char  __at(0xFF90) PWM16T1H;
__xdata volatile unsigned char  __at(0xFF91) PWM16T1L;
__xdata volatile unsigned short __at(0xFF92) PWM16T2;
__xdata volatile unsigned char  __at(0xFF92) PWM16T2H;
__xdata volatile unsigned char  __at(0xFF93) PWM16T2L;
__xdata volatile unsigned char  __at(0xFF94) PWM16CR;
__xdata volatile unsigned char  __at(0xFF95) PWM16HLD;
__xdata volatile unsigned short __at(0xFF98) PWM17T1;
__xdata volatile unsigned char  __at(0xFF98) PWM17T1H;
__xdata volatile unsigned char  __at(0xFF99) PWM17T1L;
__xdata volatile unsigned short __at(0xFF9A) PWM17T2;
__xdata volatile unsigned char  __at(0xFF9A) PWM17T2H;
__xdata volatile unsigned char  __at(0xFF9B) PWM17T2L;
__xdata volatile unsigned char  __at(0xFF9C) PWM17CR;
__xdata volatile unsigned char  __at(0xFF9D) PWM17HLD;
__xdata volatile unsigned short __at(0xFFA0) PWM2C;
__xdata volatile unsigned char  __at(0xFFA0) PWM2CH;
__xdata volatile unsigned char  __at(0xFFA1) PWM2CL;
__xdata volatile unsigned char  __at(0xFFA2) PWM2CKS;
__xdata volatile unsigned short __at(0xFFA3) PWM2TADC;
__xdata volatile unsigned char  __at(0xFFA3) PWM2TADCH;
__xdata volatile unsigned char  __at(0xFFA4) PWM2TADCL;
__xdata volatile unsigned char  __at(0xFFA5) PWM2IF;
__xdata volatile unsigned char  __at(0xFFA6) PWM2FDCR;
__xdata volatile unsigned short __at(0xFFB0) PWM20T1;
__xdata volatile unsigned char  __at(0xFFB0) PWM20T1H;
__xdata volatile unsigned char  __at(0xFFB1) PWM20T1L;
__xdata volatile unsigned short __at(0xFFB2) PWM20T2;
__xdata volatile unsigned char  __at(0xFFB2) PWM20T2H;
__xdata volatile unsigned char  __at(0xFFB3) PWM20T2L;
__xdata volatile unsigned char  __at(0xFFB4) PWM20CR;
__xdata volatile unsigned char  __at(0xFFB5) PWM20HLD;
__xdata volatile unsigned short __at(0xFFB8) PWM21T1;
__xdata volatile unsigned char  __at(0xFFB8) PWM21T1H;
__xdata volatile unsigned char  __at(0xFFB9) PWM21T1L;
__xdata volatile unsigned short __at(0xFFBA) PWM21T2;
__xdata volatile unsigned char  __at(0xFFBA) PWM21T2H;
__xdata volatile unsigned char  __at(0xFFBB) PWM21T2L;
__xdata volatile unsigned char  __at(0xFFBC) PWM21CR;
__xdata volatile unsigned char  __at(0xFFBD) PWM21HLD;
__xdata volatile unsigned short __at(0xFFC0) PWM22T1;
__xdata volatile unsigned char  __at(0xFFC0) PWM22T1H;
__xdata volatile unsigned char  __at(0xFFC1) PWM22T1L;
__xdata volatile unsigned short __at(0xFFC2) PWM22T2;
__xdata volatile unsigned char  __at(0xFFC2) PWM22T2H;
__xdata volatile unsigned char  __at(0xFFC3) PWM22T2L;
__xdata volatile unsigned char  __at(0xFFC4) PWM22CR;
__xdata volatile unsigned char  __at(0xFFC5) PWM22HLD;
__xdata volatile unsigned short __at(0xFFC8) PWM23T1;
__xdata volatile unsigned char  __at(0xFFC8) PWM23T1H;
__xdata volatile unsigned char  __at(0xFFC9) PWM23T1L;
__xdata volatile unsigned short __at(0xFFCA) PWM23T2;
__xdata volatile unsigned char  __at(0xFFCA) PWM23T2H;
__xdata volatile unsigned char  __at(0xFFCB) PWM23T2L;
__xdata volatile unsigned char  __at(0xFFCC) PWM23CR;
__xdata volatile unsigned char  __at(0xFFCD) PWM23HLD;
__xdata volatile unsigned short __at(0xFFD0) PWM24T1;
__xdata volatile unsigned char  __at(0xFFD0) PWM24T1H;
__xdata volatile unsigned char  __at(0xFFD1) PWM24T1L;
__xdata volatile unsigned short __at(0xFFD2) PWM24T2;
__xdata volatile unsigned char  __at(0xFFD2) PWM24T2H;
__xdata volatile unsigned char  __at(0xFFD3) PWM24T2L;
__xdata volatile unsigned char  __at(0xFFD4) PWM24CR;
__xdata volatile unsigned char  __at(0xFFD5) PWM24HLD;
__xdata volatile unsigned short __at(0xFFD8) PWM25T1;
__xdata volatile unsigned char  __at(0xFFD8) PWM25T1H;
__xdata volatile unsigned char  __at(0xFFD9) PWM25T1L;
__xdata volatile unsigned short __at(0xFFDA) PWM25T2;
__xdata volatile unsigned char  __at(0xFFDA) PWM25T2H;
__xdata volatile unsigned char  __at(0xFFDB) PWM25T2L;
__xdata volatile unsigned char  __at(0xFFDC) PWM25CR;
__xdata volatile unsigned char  __at(0xFFDD) PWM25HLD;
__xdata volatile unsigned short __at(0xFFE0) PWM26T1;
__xdata volatile unsigned char  __at(0xFFE0) PWM26T1H;
__xdata volatile unsigned char  __at(0xFFE1) PWM26T1L;
__xdata volatile unsigned short __at(0xFFE2) PWM26T2;
__xdata volatile unsigned char  __at(0xFFE2) PWM26T2H;
__xdata volatile unsigned char  __at(0xFFE3) PWM26T2L;
__xdata volatile unsigned char  __at(0xFFE4) PWM26CR;
__xdata volatile unsigned char  __at(0xFFE5) PWM26HLD;
__xdata volatile unsigned short __at(0xFFE8) PWM27T1;
__xdata volatile unsigned char  __at(0xFFE8) PWM27T1H;
__xdata volatile unsigned char  __at(0xFFE9) PWM27T1L;
__xdata volatile unsigned short __at(0xFFEA) PWM27T2;
__xdata volatile unsigned char  __at(0xFFEA) PWM27T2H;
__xdata volatile unsigned char  __at(0xFFEB) PWM27T2L;
__xdata volatile unsigned char  __at(0xFFEC) PWM27CR;
__xdata volatile unsigned char  __at(0xFFED) PWM27HLD;

/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

__xdata volatile unsigned char  __at(0xFE00) CLKSEL;
__xdata volatile unsigned char  __at(0xFE01) CLKDIV;
__xdata volatile unsigned char  __at(0xFE02) HIRCCR;
__xdata volatile unsigned char  __at(0xFE03) XOSCCR;
__xdata volatile unsigned char  __at(0xFE04) IRC32KCR;
__xdata volatile unsigned char  __at(0xFE05) MCLKOCR;
__xdata volatile unsigned char  __at(0xFE06) IRCDB;
__xdata volatile unsigned char  __at(0xFE08) X32KCR;
                                    
__xdata volatile unsigned char  __at(0xFE10) P0PU;
__xdata volatile unsigned char  __at(0xFE11) P1PU;
__xdata volatile unsigned char  __at(0xFE12) P2PU;
__xdata volatile unsigned char  __at(0xFE13) P3PU;
__xdata volatile unsigned char  __at(0xFE14) P4PU;
__xdata volatile unsigned char  __at(0xFE15) P5PU;
__xdata volatile unsigned char  __at(0xFE16) P6PU;
__xdata volatile unsigned char  __at(0xFE17) P7PU;
__xdata volatile unsigned char  __at(0xFE18) P0NCS;
__xdata volatile unsigned char  __at(0xFE19) P1NCS;
__xdata volatile unsigned char  __at(0xFE1A) P2NCS;
__xdata volatile unsigned char  __at(0xFE1B) P3NCS;
__xdata volatile unsigned char  __at(0xFE1C) P4NCS;
__xdata volatile unsigned char  __at(0xFE1D) P5NCS;
__xdata volatile unsigned char  __at(0xFE1E) P6NCS;
__xdata volatile unsigned char  __at(0xFE1F) P7NCS;
__xdata volatile unsigned char  __at(0xFE20) P0SR;
__xdata volatile unsigned char  __at(0xFE21) P1SR;
__xdata volatile unsigned char  __at(0xFE22) P2SR;
__xdata volatile unsigned char  __at(0xFE23) P3SR;
__xdata volatile unsigned char  __at(0xFE24) P4SR;
__xdata volatile unsigned char  __at(0xFE25) P5SR;
__xdata volatile unsigned char  __at(0xFE26) P6SR;
__xdata volatile unsigned char  __at(0xFE27) P7SR;
__xdata volatile unsigned char  __at(0xFE28) P0DR;
__xdata volatile unsigned char  __at(0xFE29) P1DR;
__xdata volatile unsigned char  __at(0xFE2A) P2DR;
__xdata volatile unsigned char  __at(0xFE2B) P3DR;
__xdata volatile unsigned char  __at(0xFE2C) P4DR;
__xdata volatile unsigned char  __at(0xFE2D) P5DR;
__xdata volatile unsigned char  __at(0xFE2E) P6DR;
__xdata volatile unsigned char  __at(0xFE2F) P7DR;
__xdata volatile unsigned char  __at(0xFE30) P0IE;
__xdata volatile unsigned char  __at(0xFE31) P1IE;
__xdata volatile unsigned char  __at(0xFE32) P2IE;
__xdata volatile unsigned char  __at(0xFE33) P3IE;
__xdata volatile unsigned char  __at(0xFE34) P4IE;
__xdata volatile unsigned char  __at(0xFE35) P5IE;
__xdata volatile unsigned char  __at(0xFE36) P6IE;
__xdata volatile unsigned char  __at(0xFE37) P7IE;
                                    
__xdata volatile unsigned char  __at(0xFE60) RTCCR;
__xdata volatile unsigned char  __at(0xFE61) RTCCFG;
__xdata volatile unsigned char  __at(0xFE62) RTCIEN;
__xdata volatile unsigned char  __at(0xFE63) RTCIF;
__xdata volatile unsigned char  __at(0xFE64) ALAHOUR;
__xdata volatile unsigned char  __at(0xFE65) ALAMIN;
__xdata volatile unsigned char  __at(0xFE66) ALASEC;
__xdata volatile unsigned char  __at(0xFE67) ALASSEC;
__xdata volatile unsigned char  __at(0xFE68) INIYEAR;
__xdata volatile unsigned char  __at(0xFE69) INIMONTH;
__xdata volatile unsigned char  __at(0xFE6A) INIDAY;
__xdata volatile unsigned char  __at(0xFE6B) INIHOUR;
__xdata volatile unsigned char  __at(0xFE6C) INIMIN;
__xdata volatile unsigned char  __at(0xFE6D) INISEC;
__xdata volatile unsigned char  __at(0xFE6E) INISSEC;
__xdata volatile unsigned char  __at(0xFE70) RTCYEAR;
__xdata volatile unsigned char  __at(0xFE71) RTCMONTH;
__xdata volatile unsigned char  __at(0xFE72) RTCDAY;
__xdata volatile unsigned char  __at(0xFE73) RTCHOUR;
__xdata volatile unsigned char  __at(0xFE74) RTCMIN;
__xdata volatile unsigned char  __at(0xFE75) RTCSEC;
__xdata volatile unsigned char  __at(0xFE76) RTCSSEC;
                                    
__xdata volatile unsigned char  __at(0xFE80) I2CCFG;
__xdata volatile unsigned char  __at(0xFE81) I2CMSCR;
__xdata volatile unsigned char  __at(0xFE82) I2CMSST;
__xdata volatile unsigned char  __at(0xFE83) I2CSLCR;
__xdata volatile unsigned char  __at(0xFE84) I2CSLST;
__xdata volatile unsigned char  __at(0xFE85) I2CSLADR;
__xdata volatile unsigned char  __at(0xFE86) I2CTXD;
__xdata volatile unsigned char  __at(0xFE87) I2CRXD;
__xdata volatile unsigned char  __at(0xFE88) I2CMSAUX;
                                    
__xdata volatile unsigned char  __at(0xFEA2) TM2PS;
__xdata volatile unsigned char  __at(0xFEA3) TM3PS;
__xdata volatile unsigned char  __at(0xFEA4) TM4PS;
__xdata volatile unsigned char  __at(0xFEA8) ADCTIM;
__xdata volatile unsigned char  __at(0xFEAC) T3T4PS;

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

__xdata volatile unsigned char  __at(0xFD00) P0INTE;
__xdata volatile unsigned char  __at(0xFD01) P1INTE;
__xdata volatile unsigned char  __at(0xFD02) P2INTE;
__xdata volatile unsigned char  __at(0xFD03) P3INTE;
__xdata volatile unsigned char  __at(0xFD04) P4INTE;
__xdata volatile unsigned char  __at(0xFD05) P5INTE;
__xdata volatile unsigned char  __at(0xFD06) P6INTE;
__xdata volatile unsigned char  __at(0xFD07) P7INTE;
__xdata volatile unsigned char  __at(0xFD10) P0INTF;
__xdata volatile unsigned char  __at(0xFD11) P1INTF;
__xdata volatile unsigned char  __at(0xFD12) P2INTF;
__xdata volatile unsigned char  __at(0xFD13) P3INTF;
__xdata volatile unsigned char  __at(0xFD14) P4INTF;
__xdata volatile unsigned char  __at(0xFD15) P5INTF;
__xdata volatile unsigned char  __at(0xFD16) P6INTF;
__xdata volatile unsigned char  __at(0xFD17) P7INTF;
__xdata volatile unsigned char  __at(0xFD20) P0IM0;
__xdata volatile unsigned char  __at(0xFD21) P1IM0;
__xdata volatile unsigned char  __at(0xFD22) P2IM0;
__xdata volatile unsigned char  __at(0xFD23) P3IM0;
__xdata volatile unsigned char  __at(0xFD24) P4IM0;
__xdata volatile unsigned char  __at(0xFD25) P5IM0;
__xdata volatile unsigned char  __at(0xFD26) P6IM0;
__xdata volatile unsigned char  __at(0xFD27) P7IM0;
__xdata volatile unsigned char  __at(0xFD30) P0IM1;
__xdata volatile unsigned char  __at(0xFD31) P1IM1;
__xdata volatile unsigned char  __at(0xFD32) P2IM1;
__xdata volatile unsigned char  __at(0xFD33) P3IM1;
__xdata volatile unsigned char  __at(0xFD34) P4IM1;
__xdata volatile unsigned char  __at(0xFD35) P5IM1;
__xdata volatile unsigned char  __at(0xFD36) P6IM1;
__xdata volatile unsigned char  __at(0xFD37) P7IM1;
__xdata volatile unsigned char  __at(0xFD40) P0WKUE;
__xdata volatile unsigned char  __at(0xFD41) P1WKUE;
__xdata volatile unsigned char  __at(0xFD42) P2WKUE;
__xdata volatile unsigned char  __at(0xFD43) P3WKUE;
__xdata volatile unsigned char  __at(0xFD44) P4WKUE;
__xdata volatile unsigned char  __at(0xFD45) P5WKUE;
__xdata volatile unsigned char  __at(0xFD46) P6WKUE;
__xdata volatile unsigned char  __at(0xFD47) P7WKUE;
__xdata volatile unsigned char  __at(0xFD60) PINIPL;
__xdata volatile unsigned char  __at(0xFD61) PINIPH;

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

__xdata volatile unsigned short __at(0xFC00) PWM3C;
__xdata volatile unsigned char  __at(0xFC00) PWM3CH;
__xdata volatile unsigned char  __at(0xFC01) PWM3CL;
__xdata volatile unsigned char  __at(0xFC02) PWM3CKS;
__xdata volatile unsigned char  __at(0xFC05) PWM3IF;
__xdata volatile unsigned char  __at(0xFC06) PWM3FDCR;
__xdata volatile unsigned short __at(0xFC10) PWM30T1;
__xdata volatile unsigned char  __at(0xFC10) PWM30T1H;
__xdata volatile unsigned char  __at(0xFC11) PWM30T1L;
__xdata volatile unsigned short __at(0xFC12) PWM30T2;
__xdata volatile unsigned char  __at(0xFC12) PWM30T2H;
__xdata volatile unsigned char  __at(0xFC13) PWM30T2L;
__xdata volatile unsigned char  __at(0xFC14) PWM30CR;
__xdata volatile unsigned char  __at(0xFC15) PWM30HLD;
__xdata volatile unsigned short __at(0xFC18) PWM31T1;
__xdata volatile unsigned char  __at(0xFC18) PWM31T1H;
__xdata volatile unsigned char  __at(0xFC19) PWM31T1L;
__xdata volatile unsigned short __at(0xFC1A) PWM31T2;
__xdata volatile unsigned char  __at(0xFC1A) PWM31T2H;
__xdata volatile unsigned char  __at(0xFC1B) PWM31T2L;
__xdata volatile unsigned char  __at(0xFC1C) PWM31CR;
__xdata volatile unsigned char  __at(0xFC1D) PWM31HLD;
__xdata volatile unsigned short __at(0xFC20) PWM32T1;
__xdata volatile unsigned char  __at(0xFC20) PWM32T1H;
__xdata volatile unsigned char  __at(0xFC21) PWM32T1L;
__xdata volatile unsigned short __at(0xFC22) PWM32T2;
__xdata volatile unsigned char  __at(0xFC22) PWM32T2H;
__xdata volatile unsigned char  __at(0xFC23) PWM32T2L;
__xdata volatile unsigned char  __at(0xFC24) PWM32CR;
__xdata volatile unsigned char  __at(0xFC25) PWM32HLD;
__xdata volatile unsigned short __at(0xFC28) PWM33T1;
__xdata volatile unsigned char  __at(0xFC28) PWM33T1H;
__xdata volatile unsigned char  __at(0xFC29) PWM33T1L;
__xdata volatile unsigned short __at(0xFC2A) PWM33T2;
__xdata volatile unsigned char  __at(0xFC2A) PWM33T2H;
__xdata volatile unsigned char  __at(0xFC2B) PWM33T2L;
__xdata volatile unsigned char  __at(0xFC2C) PWM33CR;
__xdata volatile unsigned char  __at(0xFC2D) PWM33HLD;
__xdata volatile unsigned short __at(0xFC30) PWM34T1;
__xdata volatile unsigned char  __at(0xFC30) PWM34T1H;
__xdata volatile unsigned char  __at(0xFC31) PWM34T1L;
__xdata volatile unsigned short __at(0xFC32) PWM34T2;
__xdata volatile unsigned char  __at(0xFC32) PWM34T2H;
__xdata volatile unsigned char  __at(0xFC33) PWM34T2L;
__xdata volatile unsigned char  __at(0xFC34) PWM34CR;
__xdata volatile unsigned char  __at(0xFC35) PWM34HLD;
__xdata volatile unsigned short __at(0xFC38) PWM35T1;
__xdata volatile unsigned char  __at(0xFC38) PWM35T1H;
__xdata volatile unsigned char  __at(0xFC39) PWM35T1L;
__xdata volatile unsigned short __at(0xFC3A) PWM35T2;
__xdata volatile unsigned char  __at(0xFC3A) PWM35T2H;
__xdata volatile unsigned char  __at(0xFC3B) PWM35T2L;
__xdata volatile unsigned char  __at(0xFC3C) PWM35CR;
__xdata volatile unsigned char  __at(0xFC3D) PWM35HLD;
__xdata volatile unsigned short __at(0xFC40) PWM36T1;
__xdata volatile unsigned char  __at(0xFC40) PWM36T1H;
__xdata volatile unsigned char  __at(0xFC41) PWM36T1L;
__xdata volatile unsigned short __at(0xFC42) PWM36T2;
__xdata volatile unsigned char  __at(0xFC42) PWM36T2H;
__xdata volatile unsigned char  __at(0xFC43) PWM36T2L;
__xdata volatile unsigned char  __at(0xFC44) PWM36CR;
__xdata volatile unsigned char  __at(0xFC45) PWM36HLD;
__xdata volatile unsigned short __at(0xFC48) PWM37T1;
__xdata volatile unsigned char  __at(0xFC48) PWM37T1H;
__xdata volatile unsigned char  __at(0xFC49) PWM37T1L;
__xdata volatile unsigned short __at(0xFC4A) PWM37T2;
__xdata volatile unsigned char  __at(0xFC4A) PWM37T2H;
__xdata volatile unsigned char  __at(0xFC4B) PWM37T2L;
__xdata volatile unsigned char  __at(0xFC4C) PWM37CR;
__xdata volatile unsigned char  __at(0xFC4D) PWM37HLD;
__xdata volatile unsigned short __at(0xFC50) PWM4C;
__xdata volatile unsigned char  __at(0xFC50) PWM4CH;
__xdata volatile unsigned char  __at(0xFC51) PWM4CL;
__xdata volatile unsigned char  __at(0xFC52) PWM4CKS;
__xdata volatile unsigned short __at(0xFC53) PWM4TADC;
__xdata volatile unsigned char  __at(0xFC53) PWM4TADCH;
__xdata volatile unsigned char  __at(0xFC54) PWM4TADCL;
__xdata volatile unsigned char  __at(0xFC55) PWM4IF;
__xdata volatile unsigned char  __at(0xFC56) PWM4FDCR;
__xdata volatile unsigned short __at(0xFC60) PWM40T1;
__xdata volatile unsigned char  __at(0xFC60) PWM40T1H;
__xdata volatile unsigned char  __at(0xFC61) PWM40T1L;
__xdata volatile unsigned short __at(0xFC62) PWM40T2;
__xdata volatile unsigned char  __at(0xFC62) PWM40T2H;
__xdata volatile unsigned char  __at(0xFC63) PWM40T2L;
__xdata volatile unsigned char  __at(0xFC64) PWM40CR;
__xdata volatile unsigned char  __at(0xFC65) PWM40HLD;
__xdata volatile unsigned short __at(0xFC68) PWM41T1;
__xdata volatile unsigned char  __at(0xFC68) PWM41T1H;
__xdata volatile unsigned char  __at(0xFC69) PWM41T1L;
__xdata volatile unsigned short __at(0xFC6A) PWM41T2;
__xdata volatile unsigned char  __at(0xFC6A) PWM41T2H;
__xdata volatile unsigned char  __at(0xFC6B) PWM41T2L;
__xdata volatile unsigned char  __at(0xFC6C) PWM41CR;
__xdata volatile unsigned char  __at(0xFC6D) PWM41HLD;
__xdata volatile unsigned short __at(0xFC70) PWM42T1;
__xdata volatile unsigned char  __at(0xFC70) PWM42T1H;
__xdata volatile unsigned char  __at(0xFC71) PWM42T1L;
__xdata volatile unsigned short __at(0xFC72) PWM42T2;
__xdata volatile unsigned char  __at(0xFC72) PWM42T2H;
__xdata volatile unsigned char  __at(0xFC73) PWM42T2L;
__xdata volatile unsigned char  __at(0xFC74) PWM42CR;
__xdata volatile unsigned char  __at(0xFC75) PWM42HLD;
__xdata volatile unsigned short __at(0xFC78) PWM43T1;
__xdata volatile unsigned char  __at(0xFC78) PWM43T1H;
__xdata volatile unsigned char  __at(0xFC79) PWM43T1L;
__xdata volatile unsigned short __at(0xFC7A) PWM43T2;
__xdata volatile unsigned char  __at(0xFC7A) PWM43T2H;
__xdata volatile unsigned char  __at(0xFC7B) PWM43T2L;
__xdata volatile unsigned char  __at(0xFC7C) PWM43CR;
__xdata volatile unsigned char  __at(0xFC7D) PWM43HLD;
__xdata volatile unsigned short __at(0xFC80) PWM44T1;
__xdata volatile unsigned char  __at(0xFC80) PWM44T1H;
__xdata volatile unsigned char  __at(0xFC81) PWM44T1L;
__xdata volatile unsigned short __at(0xFC82) PWM44T2;
__xdata volatile unsigned char  __at(0xFC82) PWM44T2H;
__xdata volatile unsigned char  __at(0xFC83) PWM44T2L;
__xdata volatile unsigned char  __at(0xFC84) PWM44CR;
__xdata volatile unsigned char  __at(0xFC85) PWM44HLD;
__xdata volatile unsigned short __at(0xFC88) PWM45T1;
__xdata volatile unsigned char  __at(0xFC88) PWM45T1H;
__xdata volatile unsigned char  __at(0xFC89) PWM45T1L;
__xdata volatile unsigned short __at(0xFC8A) PWM45T2;
__xdata volatile unsigned char  __at(0xFC8A) PWM45T2H;
__xdata volatile unsigned char  __at(0xFC8B) PWM45T2L;
__xdata volatile unsigned char  __at(0xFC8C) PWM45CR;
__xdata volatile unsigned char  __at(0xFC8D) PWM45HLD;
__xdata volatile unsigned short __at(0xFC90) PWM46T1;
__xdata volatile unsigned char  __at(0xFC90) PWM46T1H;
__xdata volatile unsigned char  __at(0xFC91) PWM46T1L;
__xdata volatile unsigned short __at(0xFC92) PWM46T2;
__xdata volatile unsigned char  __at(0xFC92) PWM46T2H;
__xdata volatile unsigned char  __at(0xFC93) PWM46T2L;
__xdata volatile unsigned char  __at(0xFC94) PWM46CR;
__xdata volatile unsigned char  __at(0xFC95) PWM46HLD;
__xdata volatile unsigned short __at(0xFC98) PWM47T1;
__xdata volatile unsigned char  __at(0xFC98) PWM47T1H;
__xdata volatile unsigned char  __at(0xFC99) PWM47T1L;
__xdata volatile unsigned short __at(0xFC9A) PWM47T2;
__xdata volatile unsigned char  __at(0xFC9A) PWM47T2H;
__xdata volatile unsigned char  __at(0xFC9B) PWM47T2L;
__xdata volatile unsigned char  __at(0xFC9C) PWM47CR;
__xdata volatile unsigned char  __at(0xFC9D) PWM47HLD;
__xdata volatile unsigned short __at(0xFCA0) PWM5C;
__xdata volatile unsigned char  __at(0xFCA0) PWM5CH;
__xdata volatile unsigned char  __at(0xFCA1) PWM5CL;
__xdata volatile unsigned char  __at(0xFCA2) PWM5CKS;
__xdata volatile unsigned char  __at(0xFCA5) PWM5IF;
__xdata volatile unsigned char  __at(0xFCA6) PWM5FDCR;
__xdata volatile unsigned short __at(0xFCB0) PWM50T1;
__xdata volatile unsigned char  __at(0xFCB0) PWM50T1H;
__xdata volatile unsigned char  __at(0xFCB1) PWM50T1L;
__xdata volatile unsigned short __at(0xFCB2) PWM50T2;
__xdata volatile unsigned char  __at(0xFCB2) PWM50T2H;
__xdata volatile unsigned char  __at(0xFCB3) PWM50T2L;
__xdata volatile unsigned char  __at(0xFCB4) PWM50CR;
__xdata volatile unsigned char  __at(0xFCB5) PWM50HLD;
__xdata volatile unsigned short __at(0xFCB8) PWM51T1;
__xdata volatile unsigned char  __at(0xFCB8) PWM51T1H;
__xdata volatile unsigned char  __at(0xFCB9) PWM51T1L;
__xdata volatile unsigned short __at(0xFCBA) PWM51T2;
__xdata volatile unsigned char  __at(0xFCBA) PWM51T2H;
__xdata volatile unsigned char  __at(0xFCBB) PWM51T2L;
__xdata volatile unsigned char  __at(0xFCBC) PWM51CR;
__xdata volatile unsigned char  __at(0xFCBD) PWM51HLD;
__xdata volatile unsigned short __at(0xFCC0) PWM52T1;
__xdata volatile unsigned char  __at(0xFCC0) PWM52T1H;
__xdata volatile unsigned char  __at(0xFCC1) PWM52T1L;
__xdata volatile unsigned short __at(0xFCC2) PWM52T2;
__xdata volatile unsigned char  __at(0xFCC2) PWM52T2H;
__xdata volatile unsigned char  __at(0xFCC3) PWM52T2L;
__xdata volatile unsigned char  __at(0xFCC4) PWM52CR;
__xdata volatile unsigned char  __at(0xFCC5) PWM52HLD;
__xdata volatile unsigned short __at(0xFCC8) PWM53T1;
__xdata volatile unsigned char  __at(0xFCC8) PWM53T1H;
__xdata volatile unsigned char  __at(0xFCC9) PWM53T1L;
__xdata volatile unsigned short __at(0xFCCA) PWM53T2;
__xdata volatile unsigned char  __at(0xFCCA) PWM53T2H;
__xdata volatile unsigned char  __at(0xFCCB) PWM53T2L;
__xdata volatile unsigned char  __at(0xFCCC) PWM53CR;
__xdata volatile unsigned char  __at(0xFCCD) PWM53HLD;
__xdata volatile unsigned short __at(0xFCD0) PWM54T1;
__xdata volatile unsigned char  __at(0xFCD0) PWM54T1H;
__xdata volatile unsigned char  __at(0xFCD1) PWM54T1L;
__xdata volatile unsigned short __at(0xFCD2) PWM54T2;
__xdata volatile unsigned char  __at(0xFCD2) PWM54T2H;
__xdata volatile unsigned char  __at(0xFCD3) PWM54T2L;
__xdata volatile unsigned char  __at(0xFCD4) PWM54CR;
__xdata volatile unsigned char  __at(0xFCD5) PWM54HLD;
__xdata volatile unsigned short __at(0xFCD8) PWM55T1;
__xdata volatile unsigned char  __at(0xFCD8) PWM55T1H;
__xdata volatile unsigned char  __at(0xFCD9) PWM55T1L;
__xdata volatile unsigned short __at(0xFCDA) PWM55T2;
__xdata volatile unsigned char  __at(0xFCDA) PWM55T2H;
__xdata volatile unsigned char  __at(0xFCDB) PWM55T2L;
__xdata volatile unsigned char  __at(0xFCDC) PWM55CR;
__xdata volatile unsigned char  __at(0xFCDD) PWM55HLD;
__xdata volatile unsigned short __at(0xFCE0) PWM56T1;
__xdata volatile unsigned char  __at(0xFCE0) PWM56T1H;
__xdata volatile unsigned char  __at(0xFCE1) PWM56T1L;
__xdata volatile unsigned short __at(0xFCE2) PWM56T2;
__xdata volatile unsigned char  __at(0xFCE2) PWM56T2H;
__xdata volatile unsigned char  __at(0xFCE3) PWM56T2L;
__xdata volatile unsigned char  __at(0xFCE4) PWM56CR;
__xdata volatile unsigned char  __at(0xFCE5) PWM56HLD;
__xdata volatile unsigned short __at(0xFCE8) PWM57T1;
__xdata volatile unsigned char  __at(0xFCE8) PWM57T1H;
__xdata volatile unsigned char  __at(0xFCE9) PWM57T1L;
__xdata volatile unsigned short __at(0xFCEA) PWM57T2;
__xdata volatile unsigned char  __at(0xFCEA) PWM57T2H;
__xdata volatile unsigned char  __at(0xFCEB) PWM57T2L;
__xdata volatile unsigned char  __at(0xFCEC) PWM57CR;
__xdata volatile unsigned char  __at(0xFCED) PWM57HLD;
                                    
__xdata volatile unsigned char  __at(0xFCF0) MD3;
__xdata volatile unsigned char  __at(0xFCF1) MD2;
__xdata volatile unsigned char  __at(0xFCF2) MD1;
__xdata volatile unsigned char  __at(0xFCF3) MD0;
__xdata volatile unsigned char  __at(0xFCF4) MD5;
__xdata volatile unsigned char  __at(0xFCF5) MD4;
__xdata volatile unsigned char  __at(0xFCF6) ARCON;
__xdata volatile unsigned char  __at(0xFCF7) OPCON;

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

__xdata volatile unsigned char  __at(0xFB00) COMEN;
__xdata volatile unsigned char  __at(0xFB01) SEGENL;
__xdata volatile unsigned char  __at(0xFB02) SEGENH;
__xdata volatile unsigned char  __at(0xFB03) LEDCTRL;
__xdata volatile unsigned char  __at(0xFB04) LEDCKS;
__xdata volatile unsigned char  __at(0xFB10) COM0_DA_L;
__xdata volatile unsigned char  __at(0xFB11) COM1_DA_L;
__xdata volatile unsigned char  __at(0xFB12) COM2_DA_L;
__xdata volatile unsigned char  __at(0xFB13) COM3_DA_L;
__xdata volatile unsigned char  __at(0xFB14) COM4_DA_L;
__xdata volatile unsigned char  __at(0xFB15) COM5_DA_L;
__xdata volatile unsigned char  __at(0xFB16) COM6_DA_L;
__xdata volatile unsigned char  __at(0xFB17) COM7_DA_L;
__xdata volatile unsigned char  __at(0xFB18) COM0_DA_H;
__xdata volatile unsigned char  __at(0xFB19) COM1_DA_H;
__xdata volatile unsigned char  __at(0xFB1A) COM2_DA_H;
__xdata volatile unsigned char  __at(0xFB1B) COM3_DA_H;
__xdata volatile unsigned char  __at(0xFB1C) COM4_DA_H;
__xdata volatile unsigned char  __at(0xFB1D) COM5_DA_H;
__xdata volatile unsigned char  __at(0xFB1E) COM6_DA_H;
__xdata volatile unsigned char  __at(0xFB1F) COM7_DA_H;
__xdata volatile unsigned char  __at(0xFB20) COM0_DC_L;
__xdata volatile unsigned char  __at(0xFB21) COM1_DC_L;
__xdata volatile unsigned char  __at(0xFB22) COM2_DC_L;
__xdata volatile unsigned char  __at(0xFB23) COM3_DC_L;
__xdata volatile unsigned char  __at(0xFB24) COM4_DC_L;
__xdata volatile unsigned char  __at(0xFB25) COM5_DC_L;
__xdata volatile unsigned char  __at(0xFB26) COM6_DC_L;
__xdata volatile unsigned char  __at(0xFB27) COM7_DC_L;
__xdata volatile unsigned char  __at(0xFB28) COM0_DC_H;
__xdata volatile unsigned char  __at(0xFB29) COM1_DC_H;
__xdata volatile unsigned char  __at(0xFB2A) COM2_DC_H;
__xdata volatile unsigned char  __at(0xFB2B) COM3_DC_H;
__xdata volatile unsigned char  __at(0xFB2C) COM4_DC_H;
__xdata volatile unsigned char  __at(0xFB2D) COM5_DC_H;
__xdata volatile unsigned char  __at(0xFB2E) COM6_DC_H;
__xdata volatile unsigned char  __at(0xFB2F) COM7_DC_H;
                                    
__xdata volatile unsigned char  __at(0xFB40) TSCHEN1;
__xdata volatile unsigned char  __at(0xFB41) TSCHEN2;
__xdata volatile unsigned char  __at(0xFB42) TSCFG1;
__xdata volatile unsigned char  __at(0xFB43) TSCFG2;
__xdata volatile unsigned char  __at(0xFB44) TSWUTC;
__xdata volatile unsigned char  __at(0xFB45) TSCTRL;
__xdata volatile unsigned char  __at(0xFB46) TSSTA1;
__xdata volatile unsigned char  __at(0xFB47) TSSTA2;
__xdata volatile unsigned char  __at(0xFB48) TSRT;
__xdata volatile unsigned short __at(0xFB49) TSDAT;
__xdata volatile unsigned char  __at(0xFB49) TSDATH;
__xdata volatile unsigned char  __at(0xFB4A) TSDATL;
__xdata volatile unsigned short __at(0xFB50) TSTH00;
__xdata volatile unsigned char  __at(0xFB50) TSTH00H;
__xdata volatile unsigned char  __at(0xFB51) TSTH00L;
__xdata volatile unsigned short __at(0xFB52) TSTH01;
__xdata volatile unsigned char  __at(0xFB52) TSTH01H;
__xdata volatile unsigned char  __at(0xFB53) TSTH01L;
__xdata volatile unsigned short __at(0xFB54) TSTH02;
__xdata volatile unsigned char  __at(0xFB54) TSTH02H;
__xdata volatile unsigned char  __at(0xFB55) TSTH02L;
__xdata volatile unsigned short __at(0xFB56) TSTH03;
__xdata volatile unsigned char  __at(0xFB56) TSTH03H;
__xdata volatile unsigned char  __at(0xFB57) TSTH03L;
__xdata volatile unsigned short __at(0xFB58) TSTH04;
__xdata volatile unsigned char  __at(0xFB58) TSTH04H;
__xdata volatile unsigned char  __at(0xFB59) TSTH04L;
__xdata volatile unsigned short __at(0xFB5A) TSTH05;
__xdata volatile unsigned char  __at(0xFB5A) TSTH05H;
__xdata volatile unsigned char  __at(0xFB5B) TSTH05L;
__xdata volatile unsigned short __at(0xFB5C) TSTH06;
__xdata volatile unsigned char  __at(0xFB5C) TSTH06H;
__xdata volatile unsigned char  __at(0xFB5D) TSTH06L;
__xdata volatile unsigned short __at(0xFB5E) TSTH07;
__xdata volatile unsigned char  __at(0xFB5E) TSTH07H;
__xdata volatile unsigned char  __at(0xFB5F) TSTH07L;
__xdata volatile unsigned short __at(0xFB60) TSTH08;
__xdata volatile unsigned char  __at(0xFB60) TSTH08H;
__xdata volatile unsigned char  __at(0xFB61) TSTH08L;
__xdata volatile unsigned short __at(0xFB62) TSTH09;
__xdata volatile unsigned char  __at(0xFB62) TSTH09H;
__xdata volatile unsigned char  __at(0xFB63) TSTH09L;
__xdata volatile unsigned short __at(0xFB64) TSTH10;
__xdata volatile unsigned char  __at(0xFB64) TSTH10H;
__xdata volatile unsigned char  __at(0xFB65) TSTH10L;
__xdata volatile unsigned short __at(0xFB66) TSTH11;
__xdata volatile unsigned char  __at(0xFB66) TSTH11H;
__xdata volatile unsigned char  __at(0xFB67) TSTH11L;
__xdata volatile unsigned short __at(0xFB68) TSTH12;
__xdata volatile unsigned char  __at(0xFB68) TSTH12H;
__xdata volatile unsigned char  __at(0xFB69) TSTH12L;
__xdata volatile unsigned short __at(0xFB6A) TSTH13;
__xdata volatile unsigned char  __at(0xFB6A) TSTH13H;
__xdata volatile unsigned char  __at(0xFB6B) TSTH13L;
__xdata volatile unsigned short __at(0xFB6C) TSTH14;
__xdata volatile unsigned char  __at(0xFB6C) TSTH14H;
__xdata volatile unsigned char  __at(0xFB6D) TSTH14L;
__xdata volatile unsigned short __at(0xFB6E) TSTH15;
__xdata volatile unsigned char  __at(0xFB6E) TSTH15H;
__xdata volatile unsigned char  __at(0xFB6F) TSTH15L;

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//F900H-F9FFH
/////////////////////////////////////////////////

__xdata volatile unsigned char  __at(0xF930) PWMA_ENO2;
__xdata volatile unsigned char  __at(0xF931) PWMA_IOAUX2;
__xdata volatile unsigned char  __at(0xF932) PWMA_CR3;
__xdata volatile unsigned char  __at(0xF933) PWMA_SR3;
__xdata volatile unsigned char  __at(0xF934) PWMA_CCER3;
__xdata volatile unsigned char  __at(0xF938) PWMA_CCMR1X;
__xdata volatile unsigned char  __at(0xF939) PWMA_CCMR2X;
__xdata volatile unsigned char  __at(0xF93A) PWMA_CCMR3X;
__xdata volatile unsigned char  __at(0xF93B) PWMA_CCMR4X;
__xdata volatile unsigned char  __at(0xF93C) PWMA_CCMR5;
__xdata volatile unsigned char  __at(0xF93D) PWMA_CCMR5X;
__xdata volatile unsigned char  __at(0xF93E) PWMA_CCMR6;
__xdata volatile unsigned char  __at(0xF93F) PWMA_CCMR6X;
__xdata volatile unsigned char  __at(0xF940) PWMA_CCR5H;
__xdata volatile unsigned char  __at(0xF941) PWMA_CCR5L;
__xdata volatile unsigned char  __at(0xF942) PWMA_CCR5X;
__xdata volatile unsigned char  __at(0xF943) PWMA_CCR6H;
__xdata volatile unsigned char  __at(0xF944) PWMA_CCR6L;


/////////////////////////////////////////////////

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     PCA_VECTOR              7       //003BH
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     PWM0_VECTOR             22      //00ABH
#define     PWM0FD_VECTOR           23      //00B3H
#define     I2C_VECTOR              24      //00C3H
#define     PWM1_VECTOR             28      //00E3H
#define     PWM2_VECTOR             29      //00EBH
#define     PWM3_VECTOR             30      //00F3H
#define     PWM4_VECTOR             31      //00FBH
#define     PWM5_VECTOR             32      //0103H
#define     PWM2FD_VECTOR           33      //010BH
#define     PWM4FD_VECTOR           34      //0113H
#define     TKSU_VECTOR             35      //011BH


#endif

