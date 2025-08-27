/*****************************************************************************

 Project Name       : SDP - SOC Development Project
 Project Code       : ET1035
 Created            : 23-Nov-2024
 Filename           : spi_ws.c
 Purpose            : SPI Interface
 Description        : Transmission with SPI interface
 Author(s)          : Manjunath Inamati
 Email              : manjunathinamati80@gmail.com
    
 See LICENSE for license details.
******************************************************************************/

/*  Include section
 ***************************************************/

#include "spi.h"
#include "stdlib.h"
#include "config.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 8  // Maximum number of hex characters (4 chars)

typedef unsigned char UC;
typedef unsigned int UI;

void main()
{ 
    char str[MAX_INPUT_LEN + 1];  // Buffer for user input (+1 for null-terminator)
    char error;                   // UART error flag
    int i = 0;
    int valid_hex;                // Flag to check valid hex input
    int length;                   // Length of the input string
    UI spi_data = 0;              // Data to be transmitted over SPI
    
    UC control_reg1 = 0x72;  // Control Register 1
    UC control_reg2 = 0x01;  // Control Register 2
    UC baudrate = 0x02;      // Baudrate configuration

    // Initialize UART
    uart_set_baud_rate(UART_0, 115200, 40000000);

    printf("\n\rUART-to-SPI Transmission Program\n\r");

    while (1) {
        printf("\n\rEnter 8-character hexadecimal data to transmit: ");

        // Read user input via UART
        i = 0;
        memset(str, 0, sizeof(str));  // Clear input buffer
        while (1) {
            char ch = uart_getchar(UART_0, &error);
            if (error) {
                printf("\n\rError receiving character.\n\r");
                return;  // Exit on UART error
            }

            // End of input
            if (ch == '\n' || ch == '\r') {  
                str[i] = '\0';  // Null-terminate the string
                break;
            }

            // Store character only if within buffer size
            if (i < MAX_INPUT_LEN) {  
                str[i++] = ch;
                uart_putchar(UART_0, ch, &error);  // Echo back input
            } else {
                printf("\n\rInput too long! Only 4 characters allowed.");
                break;
            }
        }

        length = strlen(str);  // Get the input length
        valid_hex = 1;         // Assume valid input initially

        // Manual validation of each character
        for (int j = 0; j < length; j++) {
            char ch = str[j];
            if (!((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))) {
                valid_hex = 0;  // Invalid hex character found
                break;
            }
        }

        // Convert the string to hexadecimal if valid
        if (valid_hex && length > 0 && length <= 8) {
            spi_data = 0;  // Reset data
            for (int j = 0; j < length; j++) {
                char ch = str[j];
                spi_data <<= 4;  // Shift left by one hex digit
                if (ch >= '0' && ch <= '9') {
                    spi_data += ch - '0';
                } else if (ch >= 'A' && ch <= 'F') {
                    spi_data += ch - 'A' + 10;
                } else if (ch >= 'a' && ch <= 'f') {
                    spi_data += ch - 'a' + 10;
                }
            }

            printf("\n\rTransmitting data: 0x%08X over SPI...", spi_data);
            
            // SPI write operation
            spiWrite(control_reg1, control_reg2, baudrate, spi_data);
            printf("\n\rSPI Transmission Complete.\n\r");

        } else {
            printf("\n\rInvalid data format. Please enter a valid 4-character hexadecimal (e.g., 1A2B).");
        }
    }
}

