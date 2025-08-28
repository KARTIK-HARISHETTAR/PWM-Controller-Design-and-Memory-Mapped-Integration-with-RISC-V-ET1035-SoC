# Description
This project is a Vivado demo showcasing a PWM-based DC motor and LED control system implemented on the Arty A7 FPGA.

The PWM controller was written in Verilog, simulated using Icarus Verilog + GTKWave, and synthesized in Vivado. It was integrated with the RISC-V ET1035 SoC using port mapping, making it accessible through a memory-mapped register.

When programmed onto the FPGA, the RISC-V processor writes duty cycle values to the PWM register using a C program compiled with the Vega SDK. These values directly update the PWM hardware logic, which controls LED brightness and DC motor speed in real time.

The project demonstrates hardware-software co-design, combining RTL design, embedded programming, SoC integration, and FPGA prototyping.
