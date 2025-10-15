#ifndef     __FLASH_SONY_H__
#define     __FLASH_SONY_H__

#include <stdint.h>

/*
Sony flash protocols:

Hardware:
Looking into the Sony MI socket, there are a total of 21 pins spaced 0.5mm apart.
From left to right, Pin1-3 are IDs, which can be directly shorted to ground for the flash type.
Pin18-20 are F3 (Clock), F2 (Data), F1 (Sync), and Pin7/Pin15 are logic grounds.
If we include the central standard ISO flash Sync. pin, and the metal hot shoe bases on the left and right side, it can also be considered that the MI interface has a total of 24 pins, and Pin22 is the central standard ISO point, called X of ISO shoe. 

Electrical signal:
The camera provides a 3.15V clock in F3/CLK, active high, low when idle, and the duration of clock pulse also has certain significance.
F2/DAT should be pull-up to high by nearly 5kOhm resistor provided by flash, to transmits data bidirectionally through an open-drain structure by a camera or flash, active high, high when idle.
F2/DAT should be driven low by the flash when it is flashing.
F1/SYNC is driven by camera, 3.15v. It has the same usage as the traditional ISO Sync. pin, but their logic level is exactly the opposite.
F1/SYNC (Pin20) uses a rising edge to trigger the formal flash, while the ISO central point (Pin22) uses the falling edge and requires a pull-up resistor.

Data:
The camera and the flash interact with data in a sequential read and sequential write manner.
The currently known reading sequence (camera read from flash) may consist of 9 to 26 bytes:
*/
typedef struct {
    uint8_t feature;
#define FLASH_SONY_READ_FEATURE_DEF 0x0F // bit 0-3: should be 0x0F, maybe some common features
#define FLASH_SONY_READ_FEATURE_ADI (1<<4)
#define FLASH_SONY_READ_FEATURE_HSS (1<<5)
#define FLASH_SONY_READ_FEATURE_NEW (1<<7) // support 16us clock, FEL, color temperature, and ...
    uint8_t unknown1; 
#define FLASH_SONY_READ_UNKNOWN1_DEF 0xF9 // unknown, seems to be 0xF9 normally
// unknown, some parameters related to zoom
    uint8_t zoom[3];
#define FLASH_SONY_READ_ZOOM_DEF {0xFF, 0xFF, 0xFF}
    uint8_t unknown2; 
#define FLASH_SONY_READ_UNKNOWN2_DEF 0xFD // unknown, seems to be 0xFD normally, older cameras send 0xFF
    uint8_t controlled; 
#define FLASH_SONY_READ_CONTROLLED_ENABLE    0x80 // indicate camera to send flash power level in Flash_Sony_Write.power
#define FLASH_SONY_READ_CONTROLLED_FULL      0x3F // bit0-6:  Flash_Sony_Write.power <= this_value-28, means full_power_level+28, also =log2(Guide_Number)*8+8
    uint8_t mode; 
#define FLASH_SONY_READ_MODE_DEF        0xF2 // bit4-7
#define FLASH_SONY_READ_MODE_CONTROLLED    1 // 1: controled by camera (TTL) 0: manual mode
#define FLASH_SONY_READ_MODE_MOUNTED       4 
#define FLASH_SONY_READ_MODE_BOUNCE        8 
    uint8_t wireless;
#define FLASH_SONY_READ_WIRELESS_DEF      0x50 // bit4-7
#define FLASH_SONY_READ_WIRELESS_CH       0x0C // bit2-3: channel 1-4 number, minus 1
    uint8_t focal;
#define FLASH_SONY_READ_FOCAL_UNKNOWN  0x3F // bit0-5: lens focal length, 0x3F means bounce mode or unknown. 
#define FLASH_SONY_READ_FOCAL_17       0x04
#define FLASH_SONY_READ_FOCAL_24       0x05
#define FLASH_SONY_READ_FOCAL_35       0x07
#define FLASH_SONY_READ_FOCAL_50       0x08
#define FLASH_SONY_READ_FOCAL_85       0x09
    uint8_t power;     // current flash power level (especially in manual mode), =Log2(power_denominator)*16+15, 0x0F=full power, 0x7F=1/128 power
    uint8_t color[12]; // color temperature/white balance? 
#define FLASH_SONY_READ_COLOR_DEF      {0x84, 0xCF, 0x00, 0xA0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88}  
    uint8_t unknown3[3];
#define FLASH_SONY_READ_UNKNOWN3_DEF   {0xFF, 0x0, 0x0C}
} Flash_Sony_Read;

/* 
Data in writing sequence (camera write flash):
The currently known writing sequence (camera write to flash) may consist of 9 to 14 bytes:
*/
typedef struct {
    uint8_t aperture; // =16*Log2(f_denominator_num)+16
    uint8_t exposure;
#define FLASH_SONY_WRITE_EXPOSURE_P 0x0
#define FLASH_SONY_WRITE_EXPOSURE_A 0x40
#define FLASH_SONY_WRITE_EXPOSURE_M 0x80
#define FLASH_SONY_WRITE_EXPOSURE_S 0xC0
#define FLASH_SONY_WRITE_EXPOSURE_LEVEL 0x3F // bit0-5: ISO and EV, =24+(Log2(ISO/100)-EV)*4
    uint8_t focal;    // lens focal length nearly =16*log2(focal_length_in_mm/4.44) 
    uint8_t unknown1; // normally 0xFF
    uint8_t func1;    // normally 0xA6 when connected
#define FLASH_SONY_WRITE_FUNC1_CONNECTED   0x02
#define FLASH_SONY_WRITE_FUNC1_ILLUMINATOR 0x10
    uint8_t func2; // normally 0xFD 
#define FLASH_SONY_WRITE_FUNC2_HSS 0x80 
    uint8_t func3; // normally 0x40 
#define FLASH_SONY_WRITE_FUNC3_HSS 0x80 
    uint8_t func4; // normally 0x40     
    uint8_t func5; // normally 0x6F     
#define FLASH_SONY_WRITE_FUNC5_NO_AF      0x04 // 0=AF-ing/AF-locked, 1=normal
#define FLASH_SONY_WRITE_FUNC5_WIRELESS_N 0x01 // 0=wireless, 1=on top
    uint8_t power; 
#define FLASH_SONY_WRITE_POWER_VALID 0xC0  // bit 7 & 6 comes together
#define FLASH_SONY_WRITE_POWER_LEVEL 0x3F  // signed, -32 to 31, =4*log2(flash_power/base_power), pre_flash_level~=min(full_power_level-16, 8*log2(F_aperture)-16), base power is a full-flash of GN5.657, also 100 lumen¡¤s @35mm
    uint8_t shuttle;  // 
#define FLASH_SONY_WRITE_SHUTTLE_NO_HSS 0x80
#define FLASH_SONY_WRITE_SHUTTLE_VALID  0x40
#define FLASH_SONY_WRITE_SHUTTLE_SPEED  0x3F // bit0-5: =4-Log2(time_in_second)*4, 0 if >2s or Bulb or uncertain
    uint8_t unknown2[3];  // normally {0x75, 0x80, 0x0}
} Flash_Sony_Write;

/*
Communication:
In a typical scene, similar to the scene of lens access, the camera accesses the flash every 20ms, alternately reading or writing.
The reading sequence uses a 90us high-level clock pulse as preamble, and the writing sequence uses a 170us pulse as preamble.
For reading or writing, sequence begins nearly 500us after preamble, and consists of multiple bytes, with a clock cycle of approximately 30us (80us in older model, 16us with newest feature), and the duty cycle of clock is about 50%, and data is provided on rising edge, sampled on the falling edge, LSB first, and each byte are approximately 270us apart, and the total number of bytes varies according to the features of the camera and flash.
A flashing sequence uses a 270us clock pulse as preamble, without fixed period, but there is an interval of about 3 ms from the last writing sequence with important instruction, and the clock pulse that arrives immediately afterwards (within nearly 13ms), either 90us or 270us width, instructs whether it is a pre-flash or an formal flash.
There should be a delay before pre-flash and flash to ensure that the camera or other devices, such as wireless equipment, are ready, and this delay can currently only be estimated based on experience to be approximately over 200us.

The communication process can be described using a state machine, with following states.
*/
#define FLASH_SONY_COMM_OFFLINE   0 // clock is not driven by camera, high-level, or timeout when clock is high-level
#define FLASH_SONY_COMM_IDLE0     1 // clock is driven to low-level by camera, or timeout when clock is low-level
#define FLASH_SONY_COMM_IDLE1     2 // preamble pulse comes
#define FLASH_SONY_COMM_READ0     3 // in reading sequence
#define FLASH_SONY_COMM_READ1     4 // in reading sequence
#define FLASH_SONY_COMM_WRITE0    5 // in writing sequence
#define FLASH_SONY_COMM_WRITE1    6 // in writing sequence
#define FLASH_SONY_COMM_FLASH0    7 // in flashing sequence
#define FLASH_SONY_COMM_FLASH1    8 // in flashing sequence
#define FLASH_SONY_COMM_SYNC      9 // waiting for F1/Sync trigger

/*
Since it is currently unknown how Sony determines the total number of bytes transmitted, using a timeout is a good method. 
Considering the observed real timing, 1ms is a good choice. A practical state machine can be:
Any state --(timeout, clk==0)--> FLASH_SONY_COMM_IDLE0, no timeout, release dat
Any state --(timeout, clk==1)--> FLASH_SONY_COMM_OFFLINE, no timeout, release dat
FLASH_SONY_COMM_OFFLINE --(clk->0)--> FLASH_SONY_COMM_IDLE0, no timeout
FLASH_SONY_COMM_IDLE0 --(clk->1)--> FLASH_SONY_COMM_IDLE1, set timeout
FLASH_SONY_COMM_IDLE1 --(clk->0, 60us<=time_elapsed<130us)--> FLASH_SONY_COMM_READ0, set timeout, reset read sequence
FLASH_SONY_COMM_IDLE1 --(clk->0, 130us<=time_elapsed<220us)--> FLASH_SONY_COMM_WRITE0, set timeout, reset write sequence
FLASH_SONY_COMM_IDLE1 --(clk->0, 220us<=time_elapsed<320us)--> FLASH_SONY_COMM_FLASH0, no timeout
FLASH_SONY_COMM_IDLE1 --(clk->0, elsewise)--> FLASH_SONY_COMM_IDLE0, no timeout
FLASH_SONY_COMM_READ0 --(clk->1)--> FLASH_SONY_COMM_READ1, drive dat to send 1 bit, set timeout
FLASH_SONY_COMM_READ1 --(clk->0)--> FLASH_SONY_COMM_READ0, set timeout
FLASH_SONY_COMM_WRITE0 --(clk->1)--> FLASH_SONY_COMM_WRITE1, set timeout
FLASH_SONY_COMM_WRITE1 --(clk->0)--> FLASH_SONY_COMM_WRITE0, read 1 bit from dat, set timeout
FLASH_SONY_COMM_FLASH0 --(clk->1)--> FLASH_SONY_COMM_FLASH1, set timeout
FLASH_SONY_COMM_FLASH1 --(clk->0, 60us<=time_elapsed<130us)--> FLASH_SONY_COMM_IDLE0, no timeout, delay 200us, pre-flash
FLASH_SONY_COMM_FLASH1 --(clk->0, 220us<=time_elapsed<320us)--> FLASH_SONY_COMM_SYNC, no timeout
FLASH_SONY_COMM_FLASH1 --(clk->0, elsewise)--> FLASH_SONY_COMM_IDLE0, no timeout
FLASH_SONY_COMM_SYNC --(clk->1)-->FLASH_SONY_COMM_IDLE1, set timeout
FLASH_SONY_COMM_SYNC --(F1/Sync triggered)-->FLASH_SONY_COMM_SYNC, no timeout, delay , flash

Following is the implementation of this state machine.
*/
typedef struct {
    uint8_t          state;
    union {
        Flash_Sony_Read  read;
        uint8_t          rbytes [sizeof(Flash_Sony_Read)];
    };
    uint8_t              rlen; // total bytes camera read at last time
    union {
        Flash_Sony_Write write;
        uint8_t          wbytes [sizeof(Flash_Sony_Write)];
    };
    uint8_t              wlen; // total bytes camera writen at last time
    // help paramters, no need to read or write outside
    uint8_t _rwbyte;
    uint8_t _rwidx;
    uint8_t _rwbit;
} Flash_Sony_Data;

/*
Called when F3/CLK is in rising/falling edge.
data: an instance of Flash_Sony_Data
clk: an expression to get current F3/CLK logical level
dat: an expression to get current F2/DAT logical level
time_lt_60us, time_lt_130us, time_lt_220us, time_lt_330us : expressions to check if time elapsed over 60us, 130us, 220us, 330us after last timer_start
timer_start: a procedure to start a timer, the timer should get timeout in 1ms, and make FLASH_SONY_COMM_TIMEOUT called
timer_stop: a procedure to stop the timer
dat_set0, dat_set1: set logical value of F2/DAT to 0 and 1, and dat_set1 also release the F2/DAT to pull-up state
prepare: a procedure to be call when a flash sequence preamble comes, and there's 13ms to complete the preparation work
delay: a procedure to delay 200us before pre-flash
preflash: a procedure to fire pre-flash
*/
#define FLASH_SONY_COMM_CLK(data, clk, dat, \
    time_lt_60us, time_lt_130us, time_lt_220us, time_lt_330us, timer_start, timer_stop, \
    dat_set0, dat_set1, prepare, delay, preflash \
    ) do { \
    register uint8_t _state=(data).state; /* snapshot of (data).state */  \
    if (clk) { \
        if (_state == FLASH_SONY_COMM_READ0) { \
            if ((data)._rwbyte & (data)._rwbit) dat_set1; \
            else dat_set0; \
            if (((data)._rwbit <<= 1) == 0) { \
                register uint8_t rwidx = (data)._rwidx; \
                if (rwidx < sizeof((data).read)-1) (data)._rwbyte = (data).rbytes[(data)._rwidx = rwidx+1]; \
                else (data)._rwbyte = 0xFF; \
                (data)._rwbit = 1; \
            } \
            (data).state = FLASH_SONY_COMM_READ1; \
        } else if (_state == FLASH_SONY_COMM_WRITE0) { \
            (data).state = FLASH_SONY_COMM_WRITE1; \
        } else if (_state == FLASH_SONY_COMM_FLASH0) { \
            (data).state = FLASH_SONY_COMM_FLASH1; \
        } else { \
            (data).state = FLASH_SONY_COMM_IDLE1; \
        } \
        timer_start; \
    } else { \
        timer_stop; \
        if (_state == FLASH_SONY_COMM_READ1) { \
            (data).state = FLASH_SONY_COMM_READ0; \
            timer_start; \
        } else if (_state == FLASH_SONY_COMM_WRITE1) { \
            if (dat) (data)._rwbyte |= (data)._rwbit; \
            if (((data)._rwbit <<= 1) == 0) { \
                register uint8_t rwidx = (data)._rwidx; \
                if (rwidx < sizeof((data).write)) { \
                    (data).wbytes[rwidx] = (data)._rwbyte; \
                    (data)._rwidx = rwidx + 1; \
                } \
                (data)._rwbyte = 0; \
                (data)._rwbit = 1; \
            } \
            (data).state = FLASH_SONY_COMM_WRITE0; \
            timer_start; \
        } else if (_state == FLASH_SONY_COMM_FLASH1) { \
            if ((time_lt_130us) && !(time_lt_60us)) { \
                dat_set0; \
                delay; \
                preflash; \
                dat_set1; \
                (data).state = FLASH_SONY_COMM_IDLE0; \
            } else if ((time_lt_330us) && !(time_lt_220us)) { \
                (data).state = FLASH_SONY_COMM_SYNC; \
            } else { \
                (data).state = FLASH_SONY_COMM_IDLE0; \
            } \
        } else if (_state == FLASH_SONY_COMM_IDLE1) { \
            if (time_lt_130us) { \
                if (time_lt_60us) { \
                    (data).state = FLASH_SONY_COMM_IDLE0; \
                } else { \
                    (data)._rwbyte = (data).rbytes[0]; \
                    (data)._rwidx = 0; \
                    (data)._rwbit = 1; \
                    (data).state = FLASH_SONY_COMM_READ0; \
                    timer_start; \
                } \
            } else if (time_lt_220us) { \
                (data)._rwbyte = 0; \
                (data)._rwidx = 0; \
                (data)._rwbit = 1; \
                (data).state = FLASH_SONY_COMM_WRITE0; \
                timer_start; \
            } else if (time_lt_330us) { \
                (data).state = FLASH_SONY_COMM_FLASH0; \
                prepare; \
            } else { \
                (data).state = FLASH_SONY_COMM_IDLE0; \
            } \
        } else { \
            (data).state = FLASH_SONY_COMM_IDLE0; \
        } \
    } \
} while (0)

/*
Called when timer started get timeout.
data: an instance of Flash_Sony_Data
clk: an expression to get current F3/CLK logical level
dat_set1: set logical value of F2/DAT to 1, also release the F2/DAT to pull-up state
timer_stop: a procedure to stop the timer
*/
#define FLASH_SONY_COMM_TIMEOUT(data, clk, dat_set1, timer_stop) do { \
    timer_stop; \
    dat_set1; \
    if ((data).state == FLASH_SONY_COMM_WRITE0) (data).wlen = (data)._rwidx; \
    else if ((data).state == FLASH_SONY_COMM_READ0) (data).rlen = (data)._rwidx; \
    if (clk) (data).state = FLASH_SONY_COMM_OFFLINE; \
    else (data).state = FLASH_SONY_COMM_IDLE0; \
} while (0)

/*
Called when F1/SYNC is triggered.
data: an instance of Flash_Sony_Data
dat_set0, dat_set1: set logical value of F2/DAT to 0 and 1, and dat_set1 also release the F2/DAT to pull-up state
delay: a procedure to delay 200us before flash
flash: a procedure to fire formal flash
*/
#define FLASH_SONY_COMM_FIRE(data, dat_set0, dat_set1, delay, flash) do { \
    if ((data).state == FLASH_SONY_COMM_SYNC) { \
        dat_set0; \
        delay; \
        flash; \
        dat_set1; \
    } \
} while (0)

#endif
