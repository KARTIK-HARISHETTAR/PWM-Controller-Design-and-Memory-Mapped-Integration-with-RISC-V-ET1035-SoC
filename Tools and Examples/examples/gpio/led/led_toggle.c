/*****************************************************************************

 Project Name		: SDP - SOC Development Project
 Project Code		: ET1035
 Created		: 23-Nov-2024
 Filename		: led_toggle.c
 Purpose		: GPIO interface
 Description		: toggle led
 Author(s)		: Manjunath Inamati
 Email			: manjunathinamati80@gmail.com
    
 See LICENSE for license details.
******************************************************************************/

/*  Include section
*
*
***************************************************/

/**
 @file led_toggle_pgm.c
 @brief Main program to toggle the LED's
*/


#include "stdlib.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"

/** 
 * @brief Toggle leds LD5,LD6 & LD7.
 * @details Toggle LEDs at finite intervals.
 * @param[in] No input parameter 
 * @param[Out] No output parameter 
*/
void main ()
{
    while (1)
    {
        printf("\r\nON LED");
        digitalSet(0x4001);
        delayMilliseconds(2000);                   // Delay for 2000 microseconds (2 ms)

        printf("\r\nOFF LED");
        digitalClear(0x4001);
        delayMilliseconds(2000);                  // Delay for 2000 microseconds (2 ms)
    }
	
}




