#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h> // include processor files - each processor file is guarded.

// Accelerometer registers

#define STATUS_REG_AUX  0x07
#define OUT_ADC1_L      0x08
#define OUT_ADC1_H      0x09
#define OUT_ADC2_L      0x0A
#define OUT_ADC2_H      0x0B
#define OUT_ADC3_L      0x0C
#define OUT_ADC3_H      0x0D
#define WHO_AM_I        0x0F
#define CTRL_REG0       0x1E
#define TEMP_CFG_REG    0x1F
#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24
#define CTRL_REG6       0x25
#define REFERENCE       0x26
#define STATUS_REG      0x27
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D
#define FIFO_CTRL_REG   0x2E
#define FIFO_SRC_REG    0x2F
#define INT1_CFG        0x30
#define INT1_SRC        0x31
#define INT1_THS        0x32
#define INT1_DURATION   0x33
#define INT2_CFG        0x34
#define INT2_SRC        0x35
#define INT2_THS        0x36
#define INT2_DURATION   0x37
#define CLICK_CFG       0x38
#define CLICK_SRC       0x39
#define CLICK_THS       0x3A
#define TIME_LIMIT      0x3B
#define TIME_LATENCY    0x3C
#define TIME_WINDOW     0x3D
#define ACT_THS         0x3E
#define ACT_DUR         0x3F

// Real Time Clock registers

#define CONTROL_1       0x00
#define CAP_SEL         0x01
#define R_12_24         0x02
#define CIE             0x04
#define SR              0x10
#define STOP            0x20
#define EXT_TEST        0x80

#define CONTROL_2       0x01
#define COF             0x07
#define TF              0x08
#define HMI             0x10
#define MI              0x20
#define AF              0x40
#define AIE             0x80

#define OFFSET          0x02
#define RAM_Byte        0x03
#define SECONDS         0x04
#define MINUTES         0x05
#define HOURS           0x06
#define DAYS            0x07
#define WEEKDAYS        0x08
#define MONTHS          0x09
#define YEARS           0x0A
#define SECOND_ALARM    0x0B
#define MINUTE_ALARM    0x0C
#define HOUR_ALARM      0x0D
#define DAY_ALARM       0x0E
#define WEEKDAY_ALARM   0x0F
#define TIMER_VALUE     0x10
#define TIMER_MODE      0x11

#define MAIN_RETURN int

#define VDD_SW  PORTBbits.RB4
#define NRESET  PORTBbits.RB3
#define SPI_SS  PORTCbits.RC7


#define _XTAL_FREQ 8000000

void SYSTEM_Initialize(void);
void SYSTEM_Sleep(unsigned char time);
unsigned short ADC_temp(void);
unsigned short ADC_mois(void);

unsigned char RTC_read(unsigned char reg);
void RTC_write(unsigned char reg, unsigned char buf);
void RTC_write_int(unsigned char reg, unsigned char buf);

void RTC_init(void);

unsigned char ACCEL_read(unsigned char reg);
void ACCEL_write(unsigned char reg, unsigned char buf);

void ACCEL_init(void);

#endif