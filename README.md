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
- Arty A7 FPGA Board (100T)
- Vivado 2024.1 or later([Vivado 2024.1 User Guide](https://hthreads.github.io/classes/embedded-systems/labs/assets/guides/VivadoGuide2024_1.pdf).)
- VEGA Tools SDK (for RISC-V ET1035 compilation)
- Tera Term (Windows) or Minicom (Linux) (for UART bootloader + XMODEM transfer)
- MicroUSB Cable (for UART interface)
- LEDs and DC Motor (connected to FPGA outputs)

# Demo Setup
## Hardware

- Arty A7 board connected to PC via USB.
- PWM output pins connected to an LED and DC motor driver.

## Software

- Vivado (run TCL script to generate .xpr)
- Vega SDK + Makefile (to build RISC-V .bin)
- UART Terminal (Tera Term / Minicom) (for bootloader transfer)

 # Steps to Run the Demo

## 1. Generate Vivado Project from TCL Script

- Open **Vivado 2018.2** (or later).  
- In the Tcl Console, run the following command:
ex - source ./scripts/create_project.tcl


## 2. Build the Bitstream

- Open the generated project in **Vivado**.  
- Click **Generate Bitstream**.  
- Program the FPGA with the `.bit` file: 
ex - ./vivado_proj/ET1035_PWM.runs/impl_1/PWMdemo.bit

## 3. Compile RISC-V Program with Makefile

- Navigate to the `sw/` folder:  
ex - cd sw
- Ensure the PWM base address (assigned during port mapping in hardware) is correctly defined in:

  - **config.h** → contains memory map  
    > 💡 Example :
    #define PWM_BASE_ADDR 0x10400000 
    ```

  - **pwm.h** → wraps the PWM register structure  
    ```c
    #define pwm_reg (*((volatile PWM_REG*)(PWM_BASE_ADDR)))
    ```

  - **pwm.c** → contains functions (e.g., `pwm_set_duty(int value)`) that write duty cycle values to the mapped register
- **Example:**  

```c
#define PWM_BASE_ADDR 0x10400000  

typedef struct {
    unsigned int DUTY_CYCLE;
} PWM_REG;

#define pwm_reg (*((volatile PWM_REG*)(PWM_BASE_ADDR)))
- Once configuration files are correct, run:  

```bash
make
This compiles all sources (`main.c`, `pwm.c`, `uart.c`) and links them with Vega SDK libraries.  
- The final RISC-V binary will be generated as:  

```bash
pwm_test.bin

## 4. Load Program via UART Bootloader  

1. Open a UART terminal (e.g., **Tera Term**) at `115200` baud.  
2. Reset the FPGA → Bootloader banner will appear.  
3. Select **Send File → XMODEM → pwm_test.bin**.  
4. The bootloader copies the program into program memory.  
5. Execution starts automatically, and **PWM duty cycle control** begins.  

## 5. Observe the Output  

- **LED brightness** changes smoothly as duty cycles update.  
- **DC motor speed** varies in proportion to PWM values.  

