/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"
#include "sx1278.h"

#include <string.h>

#include "system.h"


/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #else defined(__XC8)
        unsigned char ReceivedDataBuffer[64] @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;
unsigned char rx_status = 0;
unsigned char debug_tmp = 0;

/** DEFINITIONS ****************************************************/
typedef enum
{
    COMMAND_TRANSMIT = 0x67,
    COMMAND_RECEIVER = 0x68,
    COMMAND_CONFIG = 0xA5,
} CUSTOM_HID_DEMO_COMMANDS;

/** FUNCTIONS ******************************************************/

/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize(){
    USBInHandle = 0;
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,(uint8_t*)&ReceivedDataBuffer[0],64);
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks(){   

    if( USBGetDeviceState() < CONFIGURED_STATE ){
        return;
    }

    if( USBIsDeviceSuspended()== true ){
        return;
    }
    
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false){   
        switch(ReceivedDataBuffer[0]){
            case COMMAND_TRANSMIT:{
                unsigned char buffer[PAYLOAD_SIZE + PAYLOAD_OVERHEAD] = {0};
                unsigned long addr = 0;
                unsigned long gate = 0xAA55135B;
                unsigned char cmd = 0;
                unsigned char arg[4] = {0};
                addr += ((unsigned long) ReceivedDataBuffer[1] << 24);
                addr += ((unsigned long) ReceivedDataBuffer[2] << 16);
                addr += ((unsigned long) ReceivedDataBuffer[3] <<  8);
                addr += ((unsigned long) ReceivedDataBuffer[4] <<  0);
                cmd = ReceivedDataBuffer[5];
                arg[0] = ReceivedDataBuffer[6];
                arg[1] = ReceivedDataBuffer[7];
                arg[2] = ReceivedDataBuffer[8];
                arg[3] = ReceivedDataBuffer[9];
                SX1278_transmitData(buffer, addr, gate, cmd, arg);
                if(!HIDTxHandleBusy(USBInHandle)){
                    ToSendDataBuffer[0] = 0x67;
                    buffer[60] = debug_tmp;
                    unsigned char i = 0;
                    for(i = 0; i < PAYLOAD_SIZE + PAYLOAD_OVERHEAD; i++){
                        ToSendDataBuffer[i + 1] = buffer[i];
                    }
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0], 64);
                }
                else{
                    debug_tmp = 1;
                }
                break;
            }
            case COMMAND_RECEIVER:{
                unsigned char buffer[PAYLOAD_SIZE + PAYLOAD_OVERHEAD] = {0};
                if(rx_status == 0){
                    rx_status = 1;
                    SX1278_writeReg(REGIRQFLAGS, 0xFF);
                    SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | RXCONTINUOUS);
                }
                else if(rx_status == 1){
                    unsigned char byte_read = SX1278_readReg(REGIRQFLAGS);
                    if((byte_read & RXDONE) && !(byte_read & VALIDHEADER)){
                    
                        unsigned char length_rx = 0;

                        unsigned long tmp = 0;
                        unsigned long gate = 0xAA55135B;
                        unsigned char i = 0;

                        byte_read = SX1278_readReg(REGFIFORXCURRENTADDR);
                        SX1278_writeReg(REGFIFOADDRPTR, byte_read);
                        length_rx = SX1278_readReg(REGRXNBBYTES);
                        for(i = 0; i < length_rx; i++) buffer[i + 1] = SX1278_readReg(REGFIFO);

                        tmp += (unsigned long) buffer[1] << 24;
                        tmp += (unsigned long) buffer[2] << 16;
                        tmp += (unsigned long) buffer[3] <<  8;
                        tmp += (unsigned long) buffer[4] <<  0;

                        if (tmp == gate){ // Gateway address is correct

                            // Read packet information
                            buffer[length_rx + 1] = SX1278_readReg(REGPKTSNRVALUE);
                            buffer[length_rx + 2] = SX1278_readReg(REGPKTRSSIVALUE);
                            buffer[length_rx + 3] = SX1278_readReg(REGIRQFLAGS);
                            buffer[length_rx + 4] = SX1278_readReg(REGFEIMSB);
                            buffer[length_rx + 5] = SX1278_readReg(REGFEIMID);
                            buffer[length_rx + 6] = SX1278_readReg(REGFEILSB);
                            buffer[length_rx + 7] = rx_status;

                            // Standby mode
                            SX1278_changeMode(LONGRANGEMODE | LOWFREQUENCYMODEON | STANDBY);
                        }
                        else{  // Gateway address is not correct
                            memset(buffer, 0, PAYLOAD_SIZE + PAYLOAD_OVERHEAD);
                            buffer[0] = 1;
                        }
                        rx_status = 0;
                    }
                }
                if(!HIDTxHandleBusy(USBInHandle)){
                    ToSendDataBuffer[0] = 0x68;
                    buffer[0] = rx_status;
                    unsigned char i = 0;
                    for(i = 0; i < PAYLOAD_SIZE + PAYLOAD_OVERHEAD; i++){
                        ToSendDataBuffer[i + 1] = buffer[i];
                    }
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
                break;
            }
            case COMMAND_CONFIG:{
                unsigned char buffer[PAYLOAD_SIZE + PAYLOAD_OVERHEAD] = {0};
                buffer[0] = ReceivedDataBuffer[1];
                buffer[1] = ReceivedDataBuffer[2];
                buffer[2] = ReceivedDataBuffer[3];
                buffer[3] = ReceivedDataBuffer[4];
                SX1278_changeFreq(buffer);
                if(!HIDTxHandleBusy(USBInHandle)){
                    ToSendDataBuffer[0] = 0xA5;
                    unsigned char i = 0;
                    for(i = 0; i < PAYLOAD_SIZE + PAYLOAD_OVERHEAD; i++){
                        ToSendDataBuffer[i + 1] = buffer[i];
                    }
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
                break;
            }
        }
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer[0], 64);
    }
}