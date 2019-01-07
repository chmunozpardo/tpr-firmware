// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "sx1278.h"

#include <xc.h>
#include <stdlib.h>
#include <string.h>
#include <libpic30.h>

#include "system.h"

#include "usb.h"
#include "usb_device_hid.h"

#include "app_device_custom_hid.h"

MAIN_RETURN main(void) {
    
    CLKDIVbits.RCDIV0 = 0;
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();

    while(1)
    {
        SYSTEM_Tasks();

        #if defined(USB_POLLING)
            // Interrupt or polling method.  If using polling, must call
            // this function periodically.  This function will take care
            // of processing and responding to SETUP transactions
            // (such as during the enumeration process when you first
            // plug in).  USB hosts require that USB devices should accept
            // and process SETUP packets in a timely fashion.  Therefore,
            // when using polling, this function should be called
            // regularly (such as once every 1.8ms or faster** [see
            // inline code comments in usb_device.c for explanation when
            // "or faster" applies])  In most cases, the USBDeviceTasks()
            // function does not take very long to execute (ex: <100
            // instruction cycles) before it returns.
            USBDeviceTasks();
        #endif

        //Application specific tasks
        APP_DeviceCustomHIDTasks();

    }//end while
    
    return 0;
}
