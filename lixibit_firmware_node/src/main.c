#include <xc.h>
#include <string.h>
#include "system.h"
#include "sx1278.h"

#define _XTAL_FREQ 8000000

void __interrupt() isr_f(void){
    if(IOCCF2 && IOCCN2){
        IOCCF2 = 0;
    }
}
//  
MAIN_RETURN main(void) {
    
    unsigned char buffer[PAYLOAD_SIZE] = {0};
    unsigned char byte_read = 0;
    unsigned char wait_time = 0;
    unsigned char proc_command = 0;
    unsigned char cmd_arg[4] = {0};
    unsigned char tmr_tmpL = 0;
    unsigned char tmr_tmpH = 0;
    
    unsigned long addr = 0;
    unsigned long temp = 0;

    unsigned short adc_temp = 0;
    unsigned short adc_mois = 0;
    
    unsigned char seconds = 0;
    unsigned char minutes = 0;
    
    SYSTEM_Initialize();

//    while(1){
//        seconds = RTC_read(SECONDS);
//        minutes = RTC_read(MINUTES);
//        byte_read = ACCEL_read(0x0F);
//        wait_time = SX1278_readReg(REGBITRATEMSB);
//        proc_command = SX1278_readReg(0x01);
//    }
        
    // Main routine
    while(1){
        
        PORTBbits.RB4 = 1;
        __delay_ms(25);
        SPI_SS = 1;
        
        SX1278_init();
        ACCEL_init();
        RTC_init();
        
        SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | RXCONTINUOUS);
        
        do{
            byte_read = SX1278_readReg(REGIRQFLAGS);
        }while(!(byte_read & VALIDHEADER));
        
        
        unsigned long n_count = 0;
        unsigned long rssi_avg = 0;
        unsigned char snr_val = 0;
        unsigned char len = 18;

        do{
            rssi_avg += SX1278_readReg(REGRSSIVALUE);
            byte_read = SX1278_readReg(REGIRQFLAGS);
            n_count++;
        }while(!(byte_read & RXDONE));
        
        unsigned char  time_tmp = (unsigned char) byte_read & PAYLOADCRCERROR;
        
        if(!(byte_read & PAYLOADCRCERROR)){

            rssi_avg /= n_count;
            snr_val = SX1278_readReg(REGPKTSNRVALUE);

            SX1278_writeReg(REGIRQFLAGS, 0xFF);

            byte_read = SX1278_readReg(REGFIFORXCURRENTADDR);
            SX1278_writeReg(REGFIFOADDRPTR, byte_read);
            byte_read = SX1278_readReg(REGRXNBBYTES);
            for(unsigned char i = 0; i < byte_read; i++) buffer[i] = SX1278_readReg(REGFIFO);

            addr = 0;
            addr += (unsigned long) buffer[0] << 24;
            addr += (unsigned long) buffer[1] << 16;
            addr += (unsigned long) buffer[2] <<  8;
            addr += (unsigned long) buffer[3] <<  0;

            if (addr == NODE_ADDR){

                proc_command = buffer[4];
                if(proc_command == 0xA3){
                    RESET();
                }
                else if(proc_command == 0x93){
                    wait_time = buffer[5];
                }
                else if(proc_command == 0x83){
                    cmd_arg[0] = buffer[5];
                    cmd_arg[1] = buffer[6];
                    cmd_arg[2] = buffer[7];
                    cmd_arg[3] = buffer[8];
                }
                else if(proc_command == 0x73){
                    cmd_arg[0] = buffer[5];
                    cmd_arg[1] = buffer[6];
                    cmd_arg[2] = buffer[7];
                    cmd_arg[3] = buffer[8];
                }

                // If address matches, retrieve data from the gateway
    //            adc_temp = ADC_temp();
    //            adc_mois = ADC_mois();
                adc_temp = ADC_temp();
                adc_mois = ADC_mois();

                temp = GATEWAY_ADDR;
                buffer[0] = (unsigned char) ((temp >> 24) & 0xFF);
                buffer[1] = (unsigned char) ((temp >> 16) & 0xFF);
                buffer[2] = (unsigned char) ((temp >>  8) & 0xFF);
                buffer[3] = (unsigned char) ((temp >>  0) & 0xFF);
                buffer[4] = len;
                buffer[5] = (unsigned char) ((adc_temp >> 8) & 0xFF);
                buffer[6] = (unsigned char) ((adc_temp >> 0) & 0xFF);
                buffer[7] = (unsigned char) ((adc_mois >> 8) & 0xFF);
                buffer[8] = (unsigned char) ((adc_mois >> 0) & 0xFF);
                buffer[9] = (unsigned char) rssi_avg;
                buffer[10] = (unsigned char) snr_val;
                buffer[11] = (unsigned char) wait_time;
                buffer[12] = ACCEL_read(OUT_X_H);
                buffer[13] = ACCEL_read(OUT_X_L);
                buffer[14] = ACCEL_read(OUT_Y_H);
                buffer[15] = ACCEL_read(OUT_Y_L);
                buffer[16] = ACCEL_read(OUT_Z_H);
                buffer[17] = ACCEL_read(OUT_Z_L);

                SX1278_transmitData(buffer, len);

                SYSTEM_Sleep(wait_time);
            }   
        }
        else{
            SX1278_writeReg(REGIRQFLAGS, 0xFF);
        }
    }
}
