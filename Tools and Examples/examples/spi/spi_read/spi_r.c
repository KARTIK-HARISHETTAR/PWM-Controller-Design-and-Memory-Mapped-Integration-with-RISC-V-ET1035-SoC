/*****************************************************************************

 Project Name       : SDP - SOC Development Project
 Project Code       : ET1035
 Created            : 23-Nov-2024
 Filename           : spi_r.c
 Purpose            : SPI Interface
 Description        : SPI read and UART transmission
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

#define MAX_DATA_LEN 8  // Number of hexadecimal characters for 32-bit data

// Function to convert a nibble (4 bits) to its hex character equivalent
char nibble_to_hex(unsigned char nibble) {
    if (nibble < 10) {
        return '0' + nibble;  // For digits 0-9
    } else {
        return 'A' + (nibble - 10);  // For letters A-F
    }
}

void main() { 
    unsigned int spi_data = 0;    // Variable to store SPI received data
    char error;                   // UART error flag
    UC control_reg1 = 0x62;       // Control Register 1
    UC control_reg2 = 0x00;       // Control Register 2
    UC baudrate = 0x03;           // Baudrate
    char str[MAX_DATA_LEN + 1];   // Buffer for 8-character hexadecimal string (+1 for null terminator)

    // Initialize UART
    uart_set_baud_rate(UART_0, 115200, 40000000);

    printf("\n\rSPI-to-UART Manual Conversion Program\n\r");

        printf("\n\rReading data from SPI...");

        // Perform SPI read operation
        spi_data = spiRead(control_reg1, control_reg2, baudrate);  // SPI read function

        // Manual conversion of spi_data to an 8-character hexadecimal string
        str[0] = nibble_to_hex((spi_data >> 28) & 0xF);  // Top nibble (bits 31–28)
        str[1] = nibble_to_hex((spi_data >> 24) & 0xF);  // Next nibble (bits 27–24)
        str[2] = nibble_to_hex((spi_data >> 20) & 0xF);  // Next nibble (bits 23–20)
        str[3] = nibble_to_hex((spi_data >> 16) & 0xF);  // Next nibble (bits 19–16)
        str[4] = nibble_to_hex((spi_data >> 12) & 0xF);  // Next nibble (bits 15–12)
        str[5] = nibble_to_hex((spi_data >> 8) & 0xF);   // Next nibble (bits 11–8)
        str[6] = nibble_to_hex((spi_data >> 4) & 0xF);   // Next nibble (bits 7–4)
        str[7] = nibble_to_hex(spi_data & 0xF);          // Bottom nibble (bits 3–0)
        str[8] = '\0';                                   // Null-terminate the string

        printf("\n\rReceived SPI Data: 0x%s", str);
        printf("\n\rTransmitting data character-by-character over UART: ");

        // Transmit each character one at a time
        for (int i = 0; i < MAX_DATA_LEN; i++) {
            uart_putchar(UART_0, str[i], &error);  // Send one character
            if (error) {
                printf("\n\rError transmitting character.\n\r");
                return;
            }
        }

        printf("\n\rTransmission Complete.\n\r");
}

