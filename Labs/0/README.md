# Lab #0 Getting to know AMD-Xilinx Arty Z7 & Vivado

## Questions

### 1. What are the benefits of having Programmable logic on Zynq?

The Zynq-7000 architecture combines a dual-core ARM Cortex-A9 processor with Xilinx 7-series FPGA logic. This programming logic brings flexibility, enabling designers to create custom hardware peripherals and controllers tailored for specific applications.

- Programmable logic allows custom-defined peripherals to be build around ARM cores.

### 2. How many cores does Zynq-7000 have? What are the names of those cores? What does the memory hierarchy look like? What is the main CPU frequency?

- **Cores**: The Zynq-7000 series includes two ARM Cortex-A9 cores.
- **Memory hierarchy**:
    - 512 MB DDR memory controller.
    - The Zynq-7000 includes 8 DMA channels and 4 High Performance AXI3 Slave Ports.
- **CPU frequency**: 650 MHz, though Zynq-7000 has a PS (Processing System) clock input of 50 MHz, used to generate clocks for the subsystems.

### 3. Besides the Zynq FPGA chip, what are the other chips and their functionalities on this board?

- **DDR3 Memory**: 512 MB, which provides memory for both ARM cores and the programmable logic.
- **Quan-SPI Flash (16 MB)**: For storing configuration and boot files.
- **Ethernet PHY (Gigabit Ethernet)**: Enables network connectivity.
- **Power Management (TPS65400 PMU)**: Regulates the board’s power.
- **USB-UART bridge**: Allows for communication with a computer.

### 4. Please list the main interfaces of the Zynq-7000 AP SoC device.

- **DDR3 memory interface**: Provides access to the external DDR3 RAM.
- **Quad-SPI Flash interface**: For booting and configuration storage.
- **Gigabit Ethernet**: Connected via a Realtek PHY supporting 10/100/1000 Mbps speeds.
- **USB OTG Interface**: Facilitates USB host mode, supporting speeds up to 480 Mbps.
- **UART, SPI, I2C, and CAN**: Low-bandwidth communication interfaces.
- **AXI Interface**: High-performance interface connecting the processing system (PS) with programmable logic (PL).

### 5. How is the Arty Z7 board powered?

- **USB power**: Through the USB-JTAG/UART port (J14).
- **External power**: Via a 7V-15V power jack (J18).
- Additionally, the on-board power management unit (TPS65400 PMU) creates the necessary 3.3V, 1.8V, 1.5V, and 1.0V supplies from the main power input.

### 6. What is the Quad SPI Flash? What is its usage on this board?

- **Quad-SPI Flash**: A non-volatile memory with 16 MB capacity.
- **Usage**:
    - **Boot Storage**: The Zynq-7000 AP SoC uses the Quad-SPI Flash to store the bootloader and configuration files. It can boot from this Flash if selected via the JP4 jumper.
    - **Application Storage**: Used to store user applications and firmware updates. This allows the board to boot independently of external devices.

### 7. What is DDR Memory? What is its usage?

- **DDR Memory**: The Arty Z7 includes 512 MB of DDR3 memory with a 16-bit bus running at 525 MHz.
- **Usage**:
    - **Main System Memory**: It is used by the ARM Cortex-A9 processors in the Zynq SoC for running applications and storing data during program execution.
    - **Shared Memory**: The DDR3 memory is also accessible to the programmable logic (PL) and is used for storing and processing large datasets that both the PS and PL can access.

### 8. What are the main custom IP blocks creation methods Xilinx provides?

- **Vivado IP Integrator**: A graphical tool within Vivado that allows designers to connect and create custom IP blocks alongside pre-existing ones.
- **High-Level Synthesis (HLS)**: Designers can write high-level descriptions in C/C++ and convert them into hardware description language (HDL) code that runs on the programmable logic.
- **Block Design**: The graphical user interface in Vivado allows integration and customization of IP blocks, either pre-built or custom-designed, into a block design.

### 9. What is High-Level Synthesis (HLS)? What are the motivations behind HLS?

- **High-Level Synthesis (HLS)**: HLS allows the design of hardware using high-level languages like C or C++, which are then synthesized into RTL (register-transfer level) code that can run on FPGA fabric.
- **Motivations behind HLS**:
    - **Faster Development**: Designing in C/C++ is typically faster and more intuitive than writing hardware descriptions in VHDL or Verilog.
    - **Code Reusability**: HLS allows designers to reuse software algorithms directly.
