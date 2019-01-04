/*
 * File:   sx1278.c
 * Author: chmunozp
 *
 * Created on December 22, 2017, 12:59 PM
 */

#include <xc.h>
#include <math.h>
#include <string.h>
#include "sx1278.h"
#include "leds.h"

// Radio parameters
double freq = 433000000.0;  // Operation frequency in Hz
double signal_bw = 125.0;   // Signal bandwidth in kHz
unsigned signal_cr = 8;     // Coding rate in 4/X
unsigned signal_sf = 7;     // Spreading factor in bits

/*********************************************************************
* Function: void SX1278_init(void);
*
* Overview: Initializes the SX1278 radio.
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/

void SX1278_init(void){
    
    unsigned char BW_bits;      // Used for configuring the signal bandwidth
    unsigned char CR_bits;      // Used for configuring the data coding rate
    unsigned char SF_bits;      // Used for configuring the signal spreading factor
    
    unsigned char byte_read;    // Used for reading the registers
    
    unsigned long tmp = 0;      // Used for configuring the frequency

    // SPI1 pins TRIS
    TRISD = 0x0008;
    
    // Analog/digital I/O selection
    AD1PCFGL = 0xFFFE;
    AD1PCFGH = 0xFFFF;
    
    // SPI1 configuration I/O
    RPOR12bits.RP25R  =  8; // SCK
    RPINR20bits.SDI1R = 22; // MISO
    RPOR11bits.RP23R  =  7; // MOSI
    RPOR12bits.RP24R  =  0; // NSS
    
    // SPI1 configuration registers
    SPI1CON1 = 0b0000001100111010;
    SPI1CON2 = 0b0000000000000000;
    SPI1STAT = 0b1010000000000000;
       
    // Reset SX1278
    NRESET = 0;
    __delay_us(200);
    NRESET = 1;
    __delay_ms(10);
    
    // Sleep Mode
    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | SLEEP);
    
    // Bandwidth selection
    switch((int)signal_bw*100){
        case 780:
            BW_bits = 0x00; // 7.8 kHz
            break;
        case 1040:
            BW_bits = 0x10; // 10.4 kHz
            break;
        case 1560:
            BW_bits = 0x20; // 15.6 kHz
            break;
        case 2080:
            BW_bits = 0x30; // 20.8 kHz
            break;
        case 3125:
            BW_bits = 0x40; // 31.25 kHz
            break;
        case 4170:
            BW_bits = 0x50; // 41.7 kHz
            break;
        case 6250:
            BW_bits = 0x60; // 62.5 kHz
            break;
        case 12500:
            BW_bits = 0x70; // 125 kHz
            break;
        case 25000:
            BW_bits = 0x80; // 250 kHz
            break;
        case 50000:
            BW_bits = 0x90; // 500 kHz
            break;
        default:
            BW_bits = 0x70; // 125 kHZ
    }
    
    // Coding rate selection
    switch(signal_cr){
        case 5:
            CR_bits = 0x02; // 4/5
            break;
        case 6:
            CR_bits = 0x04; // 4/6
            break;
        case 7:
            CR_bits = 0x06; // 4/7
            break;
        case 8:
            CR_bits = 0x08; // 4/8
            break;
        default:
            CR_bits = 0x02; // 4/5
    }
    
    // Spreading factor selection
    switch(signal_sf){
        case 6:
            SF_bits = 0x60; // 64 chips/symbols
            break;
        case 7:
            SF_bits = 0x70; // 128 chips/symbols
            break;
        case 8:
            SF_bits = 0x80; // 256 chips/symbols
            break;
        case 9:
            SF_bits = 0x90; // 512 chips/symbols
            break;
        case 10:
            SF_bits = 0xA0; // 1024 chips/symbols
            break;
        case 11:
            SF_bits = 0xB0; // 2048 chips/symbols
            break;
        case 12:
            SF_bits = 0xC0; // 4096 chips/symbols
            break;
        default:
            SF_bits = 0x70; // 128 chips/symbols
    }
    
    // Modem configuration
    SX1278_writeReg(REGMODEMCONFIG1, BW_bits | CR_bits);
    SX1278_writeReg(REGMODEMCONFIG2, SF_bits | RXPAYLOADCRCON);
    
    // RX Timeout symbols
    byte_read = SX1278_readReg(REGMODEMCONFIG2);
    SX1278_writeReg(REGMODEMCONFIG2, byte_read | 0x03);
    SX1278_writeReg(REGSYMBTIMEOUTLSB, 0xFF);
    
    // Set radio frequency (433 MHz)
    tmp = (unsigned long) (freq / FSTEP);
    SX1278_writeReg(REGFRFMSB, (tmp >> 16) & 0xFF);
    SX1278_writeReg(REGFRFMID, (tmp >>  8) & 0xFF);
    SX1278_writeReg(REGFRFLSB, (tmp >>  0) & 0xFF);
    
    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | STANDBY);
}

/*********************************************************************
* Function: void SX1278_changeMode(unsigned char data);
*
* Overview: Changes de operation mode of the SX1278 radio.
*
* PreCondition: None
*
* Input: unsigned char mode - the mode of operation desired
*
* Output: None
*
********************************************************************/

void SX1278_changeMode(unsigned char mode){
    
    unsigned char byte_read = 0x00;
    
    // Repeat until operation mode is changed
    do{
        SX1278_writeReg(REGOPMODE, mode);
        byte_read = SX1278_readReg(REGOPMODE);
    }while(byte_read != mode);
}

/*********************************************************************
* Function: void SX1278_changeFreq(unsigned char *buf);
*
* Overview: Changes de operation mode of the SX1278 radio.
*
* PreCondition: None
*
* Input: unsigned char mode - the mode of operation desired
*
* Output: None
*
********************************************************************/

void SX1278_changeFreq(unsigned char *buf){
    
    unsigned char *freq_tmp = (unsigned char *)&freq;
    
    freq_tmp[0] = buf[0];
    freq_tmp[1] = buf[1];
    freq_tmp[2] = buf[2];
    freq_tmp[3] = buf[3];
    
    unsigned long tmp = (unsigned long) (freq / FSTEP);
    SX1278_writeReg(REGFRFMSB, (tmp >> 16) & 0xFF);
    SX1278_writeReg(REGFRFMID, (tmp >>  8) & 0xFF);
    SX1278_writeReg(REGFRFLSB, (tmp >>  0) & 0xFF);
    
}

/*********************************************************************
* Function: SX1278_writeReg(unsigned char reg, unsigned char data);
*
* Overview: Writes to a register of the SX1278 radio.
*
* PreCondition: None
*
* Input: unsigned char reg - the register to be written.
*        unsigned char data - the data to be written in the register.
*
* Output: None
*
********************************************************************/

void SX1278_writeReg(unsigned char reg, unsigned char data){
    
    unsigned char spi_data = 0;
    
    SPI_SS = 0;

    SPI1BUF = reg | W_REG;
    while(1) if (SPI1STATbits.SPIRBF == 1) break;
    spi_data = SPI1BUF;

    SPI1BUF = data;
    while(1) if (SPI1STATbits.SPIRBF == 1) break;
    spi_data = SPI1BUF;
    
    SPI_SS = 1;
}

/*********************************************************************
* Function: void SX1278_readReg(unsigned char reg);
*
* Overview: Reads a register of the SX1278 radio.
*
* PreCondition: None
*
* Input: unsigned char reg - the register to be read.
*
* Output: unsigned char - the value returned by the radio.
*
********************************************************************/

unsigned char SX1278_readReg(unsigned char reg){
    
    unsigned char spi_data = 0;
    
    SPI_SS = 0;

    SPI1BUF = reg | R_REG;
    while(1) if (SPI1STATbits.SPIRBF == 1) break;
    spi_data = SPI1BUF;

    SPI1BUF = 0x00FF;
    while(1) if (SPI1STATbits.SPIRBF == 1) break;
    spi_data = SPI1BUF;
    
    SPI_SS = 1;
    
    return spi_data;
}

/*********************************************************************
* Function: void SX1278_transmitData(unsigned char* buf, unsigned long nodeAddr,
 *                                   unsigned long gateAddr);
*
* Overview: Uses the SX1278 radio to transmit data to a node of the network.
*
* PreCondition: None
*
* Input: unsigned char* buf - buffer data received from the node.
*        unsigned long nodeAddr - address of the node to communicate with.
*        unsigned long gateAddr - address of the device used as gateway.
* Output: unsigned char - the value returned by the radio.
*
********************************************************************/

void SX1278_transmitData(unsigned char* buf, unsigned long nodeAddr, unsigned long gateAddr, unsigned char cmd, unsigned char *arg){
    
    unsigned char i = 0;
    unsigned char byte_read = 0;
    unsigned char length_rx = 0;
    
    unsigned long tmp = 0;
    
//    signed long fei_corr = 0;
//    
//    double freq_corr = 0;
//    double ppm_corr = 0;
        
    // Standby mode
    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | STANDBY);

    // FIFO setup
    SX1278_writeReg(REGPAYLOADLENGTH, PAYLOAD_SIZE);
    SX1278_writeReg(REGFIFORXBASEADDR, 0x00);
    SX1278_writeReg(REGFIFOTXBASEADDR, 0x80);
    SX1278_writeReg(REGFIFOADDRPTR, 0x80);

    // Set node address
    buf[0] = (nodeAddr >> 24) & 0xFF;
    buf[1] = (nodeAddr >> 16) & 0xFF;
    buf[2] = (nodeAddr >>  8) & 0xFF;
    buf[3] = (nodeAddr >>  0) & 0xFF;
    buf[4] = cmd;
    buf[5] = arg[0];
    buf[6] = arg[1];
    buf[7] = arg[2];
    buf[8] = arg[3];

    // Write address to TX FIFO
    for(i = 0; i < PAYLOAD_SIZE; i++) SX1278_writeReg(REGFIFO, buf[i]);

    // Transmit mode
    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | TX);

    // Check transmission (TXDONE)
    do{
        byte_read = SX1278_readReg(REGIRQFLAGS);
    }while(!(byte_read & TXDONE));

    // Clear flags
    SX1278_writeReg(REGIRQFLAGS, 0xFF);

    // Receive mode
    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | RXSINGLE);

    // Check reception (RXDONE or TXTIMEOUT)
    do{
        byte_read = SX1278_readReg(REGIRQFLAGS);
    }while(!(byte_read & (VALIDHEADER | RXDONE | RXTIMEOUT)));
    
    // Clean buffer for received data
    memset(buf, 0, PAYLOAD_SIZE + PAYLOAD_OVERHEAD);
    
    // If data reception succeed, process information
    if(byte_read & VALIDHEADER){ // Data received in time
        
        unsigned long n_count = 0;
        unsigned long rssi_avg = 0;
        
        do{
            rssi_avg += SX1278_readReg(REGRSSIVALUE);
            byte_read = SX1278_readReg(REGIRQFLAGS);
            n_count++;
        }while(!(byte_read & RXDONE));
        
        rssi_avg /= n_count;
        
        // Read FIFO
        byte_read = SX1278_readReg(REGFIFORXCURRENTADDR);
        SX1278_writeReg(REGFIFOADDRPTR, byte_read);
        length_rx = SX1278_readReg(REGRXNBBYTES);
        for(i = 0; i < length_rx; i++) buf[i + 1] = SX1278_readReg(REGFIFO);
        
        // Node address to unsigned long
        tmp += (unsigned long) buf[1] << 24;
        tmp += (unsigned long) buf[2] << 16;
        tmp += (unsigned long) buf[3] <<  8;
        tmp += (unsigned long) buf[4] <<  0;

        // Check node address
        if (tmp == gateAddr){ // Gateway address is correct
            
            // Read packet information
            buf[length_rx + 1] = SX1278_readReg(REGPKTSNRVALUE);
            buf[length_rx + 2] = SX1278_readReg(REGPKTRSSIVALUE);
            buf[length_rx + 3] = byte_read;
            buf[length_rx + 4] = SX1278_readReg(REGFEIMSB);
            buf[length_rx + 5] = SX1278_readReg(REGFEIMID);
            buf[length_rx + 6] = SX1278_readReg(REGFEILSB);
            buf[length_rx + 7] = rssi_avg;
            
            // Standby mode
            SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | STANDBY);
            
//            // FEI registers to signed long
//            fei_corr += (signed long)(buf[length_rx + 6] & 0x00FF) <<  0;
//            fei_corr += (signed long)(buf[length_rx + 5] & 0x00FF) <<  8;
//            fei_corr += (signed long)(buf[length_rx + 4] & 0x0007) << 16;
//            fei_corr -= (signed long)(buf[length_rx + 4] & 0x0008) << 16;
//
//            // Calculate frequency and drift error
//            freq_corr = fei_corr * (pow(2,24)/FXOSC) * (signal_bw/500.0);
//            ppm_corr = (freq_corr / freq) * 1000000.0 * 0.95;
//
//            // Compensate frequency error
//            freq -= freq_corr;
//            tmp = (unsigned long) (freq/FSTEP);
//            SX1278_writeReg(REGFRFMSB, (tmp >> 16) & 0xFF);
//            SX1278_writeReg(REGFRFMID, (tmp >>  8) & 0xFF);
//            SX1278_writeReg(REGFRFLSB, (tmp >>  0) & 0xFF);
//
//            // Compensate drift error
//            tmp = (unsigned long) ppm_corr;
//            SX1278_writeReg(REGPPMCORRECTION, tmp & 0xFF);
        }
        else{  // Gateway address is not correct
            memset(buf, 0, PAYLOAD_SIZE + PAYLOAD_OVERHEAD);
            buf[0] = 1;
        }
    }
    // If data reception is not succeed, clean information
    else if(byte_read & RXTIMEOUT){ // Timeout in receiving data
        memset(buf, 0, PAYLOAD_SIZE + PAYLOAD_OVERHEAD);
        buf[0] = 2;
        buf[1] = byte_read;
        buf[PAYLOAD_SIZE + PAYLOAD_OVERHEAD - 1] = SX1278_readReg(REGRSSIVALUE);
        
        // Standby mode
        SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | STANDBY);
    }
    
    __delay_ms(200);
}