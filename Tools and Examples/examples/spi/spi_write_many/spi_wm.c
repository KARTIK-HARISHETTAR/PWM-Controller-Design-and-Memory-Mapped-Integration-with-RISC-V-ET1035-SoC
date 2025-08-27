/*****************************************************************************

 Project Name		: SDP - SOC Development Project
 Project Code		: ET1035
 Created		: 23-Nov-2024
 Filename		: spi_wm.c
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
#include "delay.h"
void main()
{
    UC control_reg1 = 0x72;  // Control Register 1
    UC control_reg2 = 0x01;  // Control Register 2
    UC baudrate = 0x02;      // Baudrate
    UI data1 = 0x50000000;   // data to transmit
    UI data2 = 0x12345678;   // data to transmit
    UI data3 = 0x1200FF08;   // data to transmit

    // Transmit data
    printf("Starting SPI transmission...\n");

    printf("Transmitting Data1\n");
    spiWrite(control_reg1, control_reg2, baudrate, data1);
    delayMilliseconds(2000); 
    printf("Transmitting Data2\n");
    spiWrite(control_reg1, control_reg2, baudrate, data2);
    delayMilliseconds(2000);
    printf("Transmitting Data3\n");
    spiWrite(control_reg1, control_reg2, baudrate, data3);
    
    printf("\n\rTransmission complete.");
    while (1);
}
