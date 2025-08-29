# LED Project Demo
<img src="Design/ledproject.jpg" alt="Screenshot" width="50%"/>
<img src="Design/ledproject.jpg" alt="Screenshot" height="300"/>


# Description
This project is a Vivado demo showcasing a PWM-based DC motor and LED control system implemented on the Arty A7 FPGA.

The PWM controller was written in Verilog, simulated using Icarus Verilog + GTKWave, and synthesized in Vivado. It was integrated with the RISC-V ET1035 SoC using port mapping, making it accessible through a memory-mapped register.

When programmed onto the FPGA, the RISC-V processor writes duty cycle values to the PWM register using a C program compiled with the Vega SDK. These values directly update the PWM hardware logic, which controls LED brightness and DC motor speed in real time.

The project demonstrates hardware-software co-design, combining RTL design, embedded programming, SoC integration, and FPGA prototyping.

# PWM Duty Cycle Behavior
| Duty Cycle (%) | LED Brightness  | DC Motor Speed |
| -------------- | --------------- | -------------- |
| 0%             | OFF             | Stopped        |
| 30%            | Dim             | Slow           |
| 50%            | Medium          | Moderate       |
| 70%            | Bright          | Fast           |
| 100%           | Full Brightness | Maximum Speed  |


# Requirements
- **Arty A7** FPGA Board (100T)
- **Vivado 2024.1**([Vivado 2024.1 User Guide](https://hthreads.github.io/classes/embedded-systems/labs/assets/guides/VivadoGuide2024_1.pdf).)
- **VEGA Tools SDK** (for RISC-V ET1035 compilation)
- **Tera Term** (Windows) or **Minicom** (Linux) (for UART bootloader + XMODEM transfer)
- **MicroUSB Cable** (for UART interface)
- **LEDs** and **DC Motor** (connected to FPGA outputs)

# Demo Setup
## Hardware

- Arty A7 board connected to PC via USB.
- PWM output pins connected to an LED and DC motor driver.

## Software

- **Vivado** (run TCL script to generate .xpr)
- **Vega SDK + Makefile** (to build RISC-V .bin)
- **UART Terminal (Tera Term / Minicom)** (for bootloader transfer)

 # Steps to Run the Demo

## 1. Generate Vivado Project from TCL Script

- Open **Vivado 2024.1**.  
- In the **Tcl Console**, run the following command:
> 💡 Example :
```text
source ./scripts/create_project.tcl
```

## 2. Build the Bitstream

- Open the generated project in **Vivado**.  
- Click **Generate Bitstream**.  
- Program the FPGA with the `.bit` file: 
> 💡 Example :
```text
./vivado_proj/ET1035_PWM.runs/impl_1/PWMdemo.bit
```

## 3. Compile RISC-V Program with Makefile

- Navigate to the `Software` folder:  
> 💡 Example :
```text
 cd sw
```
- Ensure the PWM base address (assigned during port mapping in hardware) is correctly defined in:

  - **config.h** → ccontains memory map (e.g., '#define PWM_BASE_ADDR 0x10400000') 
  - **pwm.h** →wraps the PWM register structure with '#define pwm_reg (*((volatile PWM_REG*)(PWM_BASE_ADDR)))'
    

  - **pwm.c** → contains functions (e.g., `pwm_set_duty(int value)`) that write duty cycle values to the mapped register
    > 💡 Example :
    ```text
    typedef struct {
    unsigned int DUTY_CYCLE;
    } PWM_REG;
    #define pwm_reg (*((volatile PWM_REG*)(PWM_BASE_ADDR)))
    ```
- Once configuration files are correct, run:  
 > 💡 Example :
```text
make
```

This compiles all sources (`main.c`, `pwm.c`, `uart.c`) and links them with Vega SDK libraries.  
- The final RISC-V binary will be generated as:  

 > 💡 Example :
```text
    pwm_test.bin
```
## 4. Load Program via UART Bootloader  

- Open a UART terminal (e.g., **Tera Term**/ **Minicom**) at `115200` baud.  
- Reset the FPGA → Bootloader banner will appear.  
- Select **Send File → XMODEM → pwm_test.bin**.  
- The bootloader copies the program into program memory.  
- Execution starts automatically, and **PWM duty cycle control** begins.  

## 5. Observe the Output  

- **LED brightness** changes smoothly as duty cycles update.  
- **DC motor speed** varies in proportion to PWM values.
# Additional Notes
  ## Generating Bitstream and Programming the FPGA
  - Open the project in Vivado 2024.1 by double clicking on the included XPR file found at "<archive extracted location>/vivado_proj/Arty-A7-100-XADC.xpr".
  - In the Flow Navigator panel on the left side of the Vivado window, click Open Hardware Manager.
  - Plug the Arty A7-100T into the computer using a MicroUSB cable.
  - In the green bar at the top of the window, click Open target. Select "Auto connect" from the drop down menu.
  - In the green bar at the top of the window, click Program device.
  - In the Program Device Wizard, enter "<archive extracted location>vivado_proj/Arty-A7-100-XADC.runs/impl_1/XADCdemo.bit" into the "Bitstream file" field. Then click Program.
  - The demo will now be programmed onto the Arty A7-100T. 
