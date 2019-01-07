
// PIC18F26K42 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator Selection (XT (crystal oscillator) above 100 kHz, below 8 MHz; PFM set to medium power)
#pragma config RSTOSC = EXTOSC  // Reset Oscillator Selection (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = OFF       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = OFF     // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTC = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

// CONFIG5H

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "system.h"

/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  None
*
* Output: None
*
********************************************************************/
void SYSTEM_Initialize(void){
    
    while(!EXTOR);
    
    ANSELA = 0b00111100;
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;
     
    TRISA = 0b11111100;
    TRISB = 0b11000010;
    TRISC = 0b00100100;
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    
    ODCONA = 0b00000000;
    ODCONB = 0b00000000;
    ODCONC = 0b00011011;
    
    // ADC Configuration
    ADCON0 = 0b00000100;
    ADCON1 = 0b00000000;
    ADCON2 = 0b01100010;
    ADCON3 = 0b00000000;
    ADCLK = 0b00000001;
    ADREF = 0b00000000;
    ADPCH = 0b00000010;
    ADPREL = 00;
    ADPREH = 00;
    ADACQL = 255;
    ADACQH = 31;
    ADCAP = 10;
    ADACT = 0;
    ADCP = 0;
    ADRPT = 64;
    
    // SPI Configuration
    RB2PPS = 0b00011110;
    RB0PPS = 0b00011111; 
    RC7PPS = 0b00000000;
    SPI1SDIPPS = 0x09;
    
    SPI1CON0 = 0b00000010;
    SPI1CON1 = 0b01000100;
    SPI1CON2 = 0b00000011;
    SPI1CLK = 0x00;
    SPI1BAUD = 15;
    SPI1TCNTL = 0;
    SPI1TCNTH = 0;
    SPI1TWIDTH = 0;
    
    // RTC Configuration
    RC0PPS = 0x21;
    RC1PPS = 0x22;
    I2C1SCLPPS = 0x10;
    I2C1SDAPPS = 0x11;
    I2C1CON0 = 0b00000100;
    I2C1CON1 = 0b10000000;
    I2C1CON2 = 0b00000001;
    I2C1CLK = 0b00000011;
    
    // ACCEL Configuration
    RC4PPS = 0x23;
    RC3PPS = 0x24;
    I2C2SCLPPS = 0x14;
    I2C2SDAPPS = 0x13;
    I2C2CON0 = 0b00000100;
    I2C2CON1 = 0b10000000;
    I2C2CON2 = 0b00100001;
    I2C2CLK = 0b00000000;
    
    // Interrupts Configuration
    INTCON1 = 0b10000000;
    PIE0 = 0b10000000;
    
    IOCCN2 = 1;
    IOCIP = 0;
    INTCON0 = 0b00000000;

    IDLEN = 0;
    VREGPM = 1;
    
    GIE = 0;
    
}

unsigned short ADC_temp(){
    
    unsigned short out_L = 0;
    
    ADPCH = 0b00000010;
    ADON = 1;
    
    while(1){
        GO_nDONE = 1;

        while(GO_nDONE);
        if(ADRPT == ADCNT)
            break;
    }

    out_L = (unsigned short)ADFLTR;
    ADACLR = 1;
    while(ACLR);
    
    ADON = 0;
    
    return out_L;
}

unsigned short ADC_mois(){
    
    unsigned short out_L = 0;
    
    ADPCH = 0b00000101;
    
    ADON = 1;
    
    while(1){
        GO_nDONE = 1;
        while(GO_nDONE);
        if(ADRPT == ADCNT)
            break;
    }

    out_L = (unsigned short)ADFLTR;
    ADACLR = 1;
    while(ACLR);
    
    ADON = 0;
    
    return out_L;
}

unsigned char RTC_read(unsigned char reg){
    
    unsigned char buf;
    
    I2C1CON0bits.EN = 1;
    
    // I2C Write
    I2C1ADB1 = 0b10100010 + 0x00;
    I2C1CNT = 1;
    
    I2C1CON0bits.S = 1;
    I2C1TXB = reg;
    while(!I2C1STAT1bits.TXBE);
    while(!I2C1PIRbits.PCIF);
    
    I2C1PIR = 0;
    I2C1ERR = 0;
    
    // I2C Read
    I2C1ADB1 = 0b10100010 + 0x01;
    I2C1CNT = 1;
    I2C1CON0bits.S = 1;
    while(I2C1STAT1bits.RXBF);
    while(!I2C1PIRbits.PCIF);
    
    buf = I2C1RXB;
    
    I2C1PIR = 0;
    I2C1ERR = 0;
    
    I2C1CON0bits.EN = 0;
    
    return buf;
}

void RTC_write(unsigned char reg, unsigned char buf){
    
    I2C1CON0bits.EN = 1;
    
    // I2C Write
    I2C1ADB1 = 0b10100010 + 0x00;
    I2C1CNT = 2;
    
    I2C1CON0bits.S = 1;
    I2C1TXB = reg;
    while(!I2C1STAT1bits.TXBE);
    
    I2C1TXB = buf;
    while(!I2C1STAT1bits.TXBE);
    while(!I2C1PIRbits.PCIF);
    
    I2C1PIR = 0;
    I2C1ERR = 0;
    
    I2C1CON0bits.EN = 0;
}

void RTC_init(void){
    
    RTC_write(CONTROL_1, 0b00000001);
    RTC_write(CONTROL_2, 0b10000000);
    RTC_write(OFFSET, 0b00000000);
    RTC_write(SECONDS, 0x00);
    RTC_write(MINUTES, 0x00);
    RTC_write(HOURS, 0x00);
    RTC_write(DAYS, 0x03);
    RTC_write(WEEKDAYS, 0x01);
    RTC_write(MONTHS, 0x10);
    RTC_write(YEARS, 0x18);
    RTC_write(TIMER_VALUE, 0x00);
    RTC_write(TIMER_MODE, 0b00011110);
}

unsigned char ACCEL_read(unsigned char reg){
    
    unsigned char buf;
    
    I2C2CON0bits.EN = 1;
    
    // I2C Write
    I2C2ADB1 = 0b00110010 + 0x00;
    I2C2CNT = 1;
    
    I2C2CON0bits.S = 1;
    I2C2TXB = reg;
    while(!I2C2STAT1bits.TXBE);
    while(!I2C2PIRbits.PCIF);
    
    I2C2PIR = 0;
    I2C2ERR = 0;
    
    // I2C Read
    I2C2ADB1 = 0b00110010 + 0x01;
    I2C2CNT = 1;
    I2C2CON0bits.S = 1;
    while(I2C2STAT1bits.RXBF);
    while(!I2C2PIRbits.PCIF);
    
    buf = I2C2RXB;
    
    I2C2PIR = 0;
    I2C2ERR = 0;
    
    I2C2CON0bits.EN = 0;
    
    return buf;
}

void ACCEL_write(unsigned char reg, unsigned char buf){
    
    I2C2CON0bits.EN = 1;
    
    // I2C Write
    I2C2ADB1 = 0b00110010 + 0x00;
    I2C2CNT = 2;
    
    I2C2CON0bits.S = 1;
    I2C2TXB = reg;
    while(!I2C2STAT1bits.TXBE);
    
    I2C2TXB = buf;
    while(!I2C2STAT1bits.TXBE);
    while(!I2C2PIRbits.PCIF);
    
    I2C2PIR = 0;
    I2C2ERR = 0;
    
    I2C2CON0bits.EN = 0;
}

void ACCEL_init(void){

    ACCEL_write(CTRL_REG1, 0x77);     // 0b01110111
    ACCEL_write(CTRL_REG2, 0x90);     // 0b10001111
    ACCEL_write(CTRL_REG3, 0xE0);     // 0b00000000
    ACCEL_write(CTRL_REG4, 0x08);     // 0b00001000
    ACCEL_write(CTRL_REG5, 0x08);     // 0b00000010
    ACCEL_write(CTRL_REG6, 0x00);     // 0b11100000
    ACCEL_write(REFERENCE, 10);       // 0b00001010
    ACCEL_write(INT1_CFG, 0x00);      // 0b00111111
    ACCEL_write(INT1_THS, 63);        // 0b00011110
    ACCEL_write(INT1_DURATION, 80);   // 0b00001000
    ACCEL_write(CLICK_CFG, 0x2A);     // 0b00101010
    ACCEL_write(CLICK_THS, 63);       // 0b00001010
}

void SYSTEM_Sleep(unsigned char time){
    //PORTBbits.RB4 = 0;
    if(time == 0)
        return;
    GIE = 1;
    RTC_write(TIMER_VALUE, time);
    SLEEP();
}