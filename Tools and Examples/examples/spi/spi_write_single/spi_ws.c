/*****************************************************************************

 Project Name		: SDP - SOC Development Project
 Project Code		: ET1035
 Created		: 23-Nov-2024
 Filename		: spi_ws.c
 Purpose		: SPI Interface
 Description		: transmission with spi interface
 Author(s)		: Manjunath Inamati
 Email			: manjunathinamati80@gmail.com
    
 See LICENSE for license details.
******************************************************************************/

/*  Include section
 ***************************************************/

#include "spi.h"
#include "stdlib.h"
#include "config.h"
void main()
{
    UC control_reg1 = 0x72;  // Control Register 1
    UC control_reg2 = 0x01;  // Control Register 2
    UC baudrate = 0x02;      // Baudrate
    UI data = 0x40000000;   // data to transmit

    // Transmit data
    printf("Starting SPI transmission...\n");

    spiWrite(control_reg1, control_reg2, baudrate, data);
    
    printf("\n\rTransmission complete.");
    while (1);
}
