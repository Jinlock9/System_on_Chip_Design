# Lab #1 Getting Started with Arty Z7 SoC Development Platform

## Contents

### 2 Build a basic ZYNQ system on the Arty Z-7 board

### 3 Build a basic ZYNQ system with peripherals

- `work/source/lab1-2.c`

### 4 Create and use custom IP blocks in Verilog

- `work/source/divider.c`
- `work/source/rtl_divider.v`

### 5 (Optional) Create an FIR filter by MATLAB HDL Coder

### 6 Tcl exercises

1. Average

    ```tcl
    proc avg {numbers} {
        set sum 0
        set count [llength $numbers]
        foreach num $numbers {
            set sum [expr {$sum + $num}]
        }
        return [expr {$sum / $count}]
    }
    ```

2. Factorial

    ```tcl
    proc factorial {n} {
        if {$n <= 1} {
            return 1
        } else {
            return [expr {$n * [factorial [expr {$n- 1}]]}]
        }
    }
    ```
3. Two-fer

    ```tcl
    proc two-fer {{filename "main.c"}} {return "C source: $filename"}
    ```

### 7 Post-lab questions

1. What is a bare metal test?

    > A bare metal test refers to testing a system without an operating system (OS). It runs directly on the hardware, utilizing the hardware’s own capabilities, such as the processor and memory, without the intervention of a complex OS. It’s a method used to test the hardware components, like the Zynq Processing System (PS) and custom IP blocks, by executing code straight on the device to verify their functionality. This type of testing is often used in embedded systems or microcontroller development to verify that the hardware and low-level software components work correctly.

2. How does the Zynq PS communicate with the IP blocks we created in this lab?

    > In this lab, the IP blocks are connected to the AXI bus, making them accessible to the PS. The Zynq PS communicates with the custom IP blocks through the AXI (Advanced eXtensible Interface) protocol. In particular, the AXI4-Lite interface is used in this lab to enable communication between the PS and the custom peripherals. The AXI interface is a memory-mapped bus system that allows data transfer between the PS and the FPGA fabric.

3. Summarize the main features of AXI from the reading material

    >  The first is the high-performance interface: AXI is designed to support high-performance communication between the processing system and the programmable logic. Also, it supports multiple master and slave devices, allowing flexible connections between different processing elements and memory or peripheral blocks. This enables a wide range of system designs. AXI supports burst data transactions and low-latency communication, which can significantly improve the performance of data transfers. The last feature: it allows transactions to be processed out of order, which improves the efficiency of resource usage by overlapping multiple operations.