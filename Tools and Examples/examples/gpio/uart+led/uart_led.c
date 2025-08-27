/*****************************************************************************

 Project Name		: SDP - SOC Development Project
 Project Code		: ET1035
 Created		: 23-Nov-2024
 Filename		: uart_led.c
 Purpose		: UART and GPIO interface
 Description		: control led through UART
 Author(s)		: Manjunath Inamati
 Email			: manjunathinamati80@gmail.com
    
 See LICENSE for license details.
******************************************************************************/

/**
 @file led_toggle_pgm.c
 @brief Main program to toggle the LED's
*/


#include "stdlib.h"
#include "config.h"
#include "uart.h"
#include "gpio.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

/** 
 * @brief Toggle LEDs based on UART input commands.
 * @details Reads "on" or "off" from UART to control LEDs.
 * @param[in] No input parameter 
 * @param[out] No output parameter 
 */
void main()
{ 
    char str[6]; 
    char error; 
    int i = 0;

    // Set UART baud rate
    uart_set_baud_rate(UART_0, 115200, 40000000);

    while (1)
    {       
        printf("\n\rEnter status (on/off):\n\r");

        // Read user input from UART
        i = 0;
        memset(str, 0, sizeof(str));  // Clear the buffer before new input

        while (1) {
            char ch = uart_getchar(UART_0, &error);
            if (error) {
                printf("Error receiving character.\n\r");
                return;
            }

            if (ch == '\n' || ch == '\r') {
                str[i] = '\0';  // Null-terminate the string
                break;
            }

            if (i < sizeof(str) - 1) {
                str[i++] = ch;
                uart_putchar(UART_0, ch, &error);  // Echo the character
            }
        }

        // Process the received command
        if (strcmp(str, "on") == 0) {    
            printf("\n\rLEDs ON");
            pinSet(PIN_1);

            // Wait for "off" command to turn off the LED
            while (1) {
                printf("\n\rWaiting for 'off' command to turn off the LED...\n\r");
                i = 0;
                memset(str, 0, sizeof(str));  // Clear the buffer

                while (1) {
                    char ch = uart_getchar(UART_0, &error);
                    if (error) {
                        printf("Error receiving character.\n\r");
                        return;
                    }

                    if (ch == '\n' || ch == '\r') {
                        str[i] = '\0';  // Null-terminate the string
                        break;
                    }

                    if (i < sizeof(str) - 1) {
                        str[i++] = ch;
                        uart_putchar(UART_0, ch, &error);  // Echo the character
                    }
                }

                if (strcmp(str, "off") == 0) {
                    printf("\n\rLEDs OFF");
                    pinClear(PIN_1);
                    break;
                } else {
                    printf("\n\rInvalid command. Use 'off' to turn off the LED.");
                }
            }
        }
        else {
            printf("\n\rInvalid command. Use 'on' or 'off'.");
        }
    }
}





