# Lab #2 Design with High Level Synthesis on Arty Z7 SoC Development Platform

## Contents

### 2 Create and Use Custom IP Blocks Using High-Level Synthesis

- `work/source/Section2/hls_multiplier.cpp`
-  `work/source/Section2/test_hls_multiplier.cpp`
-  `work/source/Section2/hls_rtl_multiplier.c`

- Follow-up Exercises
    - `work/source/Section2_5/hls_alu.cpp`
    - `work/source/Section2_5/test_hls_alu.cpp`
    - `work/source/Section2_5/rtl_alu.sv`
    - `work/source/Section2_5/hls_rtl_alu.c`

### 3 Program the FPGA and Boot Software from the SD Card

### 4 Program Python on Arty Z7

### 5 (Optional) Optimize Your RTL ALU by Pipelining

- `work/source/Section5/div.sv`
- `work/source/Section5/div_testbench.sv`
- `work/source/Section5/rtl_pipe_alu.sv`
- `work/source/Section5/hls_rtl_pipe_alu.c`

### 6 Post-lab Questions

1. What was the resource utilization of the RTL implementation vs. HLS implementation? If they are different, can you guess why there are differences?

    > RTLdesigns are hand-coded at a lower abstraction level, allowing precise control over resource usage. As a result, resource utilization is often optimized for the specific needs of the application, which may lead to more efficient use of hardware.HLS, on the other hand, starts from a higher-level description (e.g., C/C++), and then synthesizes hardware. Due to this higher-level abstraction, HLS tools may generate less optimized hardware since they need to make more generalized decisions during synthesis. Difference may due to the granularity of control and manual optimizations available in RTL but lacking in HLS

2. Imagine that you have to create an IP block implementing ten different sorting algorithms. Would you rather use a hardware description language or High-level Synthesis? Why?

    >  If I had to create an IP block that implements ten different sorting algorithms, I would prefer to use High-Level Synthesis (HLS) rather than a traditional Hardware Description Language (HDL): HLS allows you to design at a higher level of abstraction using languages like C or C++, which significantly speeds up the process of writing and debugging complex algorithms compared to the lower level details of HDLs; What‘s more, HLS can make complex algorithm.Sorting algorithms, by nature, involve a lot of iterative and conditional logic, which is more naturally expressed in a high-level language. Also The HLS approach enables you to write more modular and reusable code.

3. Read more about PYNQ, and answer the following questions:

    - What is a Jupyter notebook? Why do we use it?

        > A Jupyter Notebook is an open-source web application that allows you to create and share documents. It supports a variety of programming languages, with Python being the most commonly used. Jupyter Notebooks have several advantages that make them suitable for many purposes, such as education, research, data analysis, and prototyping hardware designs.

    - What are overlays? What are the benefits of using overlays?

        > Overlays are pre-configured bitstreams or hardware designs that are used to program the programmable logic of an FPGA device, such as the ones found in Zynq chips. Overlays provide several benefits, especially for users who are not experts in hardware design or who are looking to accelerate the development of applications that utilize FPGAs.

    - Please list available overlays on the Arty Z7 board.

        > LED control,audio processing, image control...

    - Comparing part 2 where you design with C/C++ vs. part 4 (PYNQ framework with python), what are the major differences?

        > C/C++withHLS(Part2)involvesdesigning custom hardware using C/C++, synthesizing to RTL, and provides lower-level control.PYNQ with Python (Part 4) offers a high-level interface where you can load pre-built bitstreams, use Python to control the FPGA, and focus on the application-level development rather than hardware design.