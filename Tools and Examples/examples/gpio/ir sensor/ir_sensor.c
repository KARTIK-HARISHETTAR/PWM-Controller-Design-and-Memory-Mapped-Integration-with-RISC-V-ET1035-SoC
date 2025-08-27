/*****************************************************************************

 Project Name		: SDP - SOC Development Project
 Project Code		: ET1035
 Created		: 23-Nov-2024
 Filename		: ir_sensor.c
 Purpose		: GPIO interface
 Description		: read IR sensor status and blink led
 Author(s)		: Manjunath Inamati
 Email			: manjunathinamati80@gmail.com
    
 See LICENSE for license details.
******************************************************************************/

/**
 @file ir sensor.c
 @brief Main program for IR Sensor
*/

#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"

void main ()
{
    printf("\n\rObject Detection Using IR Sensor");

    int last_ir_sensor_status = 0; 
    int ir_sensor_status;

    while (1)
    {
        ir_sensor_status = pinRead(PIN_2);  // Read IR sensor status

        if (ir_sensor_status != last_ir_sensor_status) {
            last_ir_sensor_status = ir_sensor_status; // Update the last state

            if (ir_sensor_status == 0) {
                printf("\n\rObject Detected");
                pinSet(PIN_1);
            } else {
                printf("\n\rPath Clear");
                pinClear(PIN_1);
            }
        }
    }
}



