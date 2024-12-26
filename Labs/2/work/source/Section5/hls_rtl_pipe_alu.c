#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_alu.h"    // Contains hls_alu macros and functions

// Base Address of the RTL_ALU
Xuint32 *baseaddr_rtl_alu = (Xuint32 *) XPAR_RTL_PIPE_ALU_0_S00_AXI_BASEADDR;

int main() {
    init_platform();

    ////////////////////////////////////////////////////////////////////////////////////////
    // RTL ALU TEST
    xil_printf("Performing a test of the RTL_PIPE_ALU... \r\n");

    for (int i = 0; i < 18; i++) {
        switch (i) {
            case 0:
                xil_printf("TEST #0: ALU_ADD\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000a; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000005; // opb = 5
                *(baseaddr_rtl_alu + 0) = 0x00000000 << 1; // func = ALU_ADD
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 1:
                xil_printf("TEST #1: ALU_SUB\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000a; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000005; // opb = 5
                *(baseaddr_rtl_alu + 0) = 0x00000001 << 1; // func = ALU_SUB
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 2:
                xil_printf("TEST #2: ALU_SLT\r\n");
                *(baseaddr_rtl_alu + 1) = 0xFFFFFFF6; // opa = -10
                *(baseaddr_rtl_alu + 2) = 0x00000005; // opb = 5
                *(baseaddr_rtl_alu + 0) = 0x00000002 << 1; // func = ALU_SLT
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 3:
                xil_printf("TEST #3: ALU_SLTU\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000a; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000014; // opb = 20
                *(baseaddr_rtl_alu + 0) = 0x00000003 << 1; // func = ALU_SLTU
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 4:
                xil_printf("TEST #4: ALU_AND\r\n");
                *(baseaddr_rtl_alu + 1) = 0x00000006; // opa = 6
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x00000004 << 1; // func = ALU_AND
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 5:
                xil_printf("TEST #5: ALU_OR\r\n");
                *(baseaddr_rtl_alu + 1) = 0x00000006; // opa = 6
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x00000005 << 1; // func = ALU_OR
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 6:
                xil_printf("TEST #6: ALU_XOR\r\n");
                *(baseaddr_rtl_alu + 1) = 0x00000006; // opa = 6
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x00000006 << 1; // func = ALU_XOR
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 7:
                xil_printf("TEST #7: ALU_SLL\r\n");
                *(baseaddr_rtl_alu + 1) = 0x00000005; // opa = 5
                *(baseaddr_rtl_alu + 2) = 0x00000001; // opb = 1
                *(baseaddr_rtl_alu + 0) = 0x00000007 << 1; // func = ALU_SLL
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 8:
                xil_printf("TEST #8: ALU_SRL\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000a; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000001; // opb = 1
                *(baseaddr_rtl_alu + 0) = 0x00000008 << 1; // func = ALU_SRL
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 9:
                xil_printf("TEST #9: ALU_SRA\r\n");
                *(baseaddr_rtl_alu + 1) = 0xFFFFFFFC; // opa = -4
                *(baseaddr_rtl_alu + 2) = 0x00000001; // opb = 1
                *(baseaddr_rtl_alu + 0) = 0x00000009 << 1; // func = ALU_SRA
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 10:
                xil_printf("TEST #10: ALU_MUL\r\n");
                *(baseaddr_rtl_alu + 1) = 0x00000005; // opa = 5
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x0000000A << 1; // func = ALU_MUL
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 11:
                xil_printf("TEST #11: ALU_MULH\r\n");
                *(baseaddr_rtl_alu + 1) = 0x000186A0; // opa = 100000
                *(baseaddr_rtl_alu + 2) = 0x000186A0; // opb = 100000
                *(baseaddr_rtl_alu + 0) = 0x0000000B << 1; // func = ALU_MULH
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 12:
                xil_printf("TEST #12: ALU_MULHSU\r\n");
                *(baseaddr_rtl_alu + 1) = 0x000186A0; // opa = 100000
                *(baseaddr_rtl_alu + 2) = 0x000186A0; // opb = 100000
                *(baseaddr_rtl_alu + 0) = 0x0000000C << 1; // func = ALU_MULHSU
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 13:
                xil_printf("TEST #13: ALU_MULHU\r\n");
                *(baseaddr_rtl_alu + 1) = 0x000186A0; // opa = 100000
                *(baseaddr_rtl_alu + 2) = 0x000186A0; // opb = 100000
                *(baseaddr_rtl_alu + 0) = 0x0000000D << 1; // func = ALU_MULHU
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 14:
                xil_printf("TEST #14: ALU_DIV\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000A; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000005; // opb = 5
                *(baseaddr_rtl_alu + 0) = 0x0000000E << 1; // func = ALU_DIV
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 15:
                xil_printf("TEST #15: ALU_DIVU\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000A; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x0000000F << 1; // func = ALU_DIVU
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 16:
                xil_printf("TEST #16: ALU_REM\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000A; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x00000010 << 1; // func = ALU_REM
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            case 17:
                xil_printf("TEST #17: ALU_REMU\r\n");
                *(baseaddr_rtl_alu + 1) = 0x0000000A; // opa = 10
                *(baseaddr_rtl_alu + 2) = 0x00000003; // opb = 3
                *(baseaddr_rtl_alu + 0) = 0x00000011 << 1; // func = ALU_REMU
                while ((*(baseaddr_rtl_alu + 0) & 0x1) == 0);
                xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", *(baseaddr_rtl_alu + 1), *(baseaddr_rtl_alu + 2), *(baseaddr_rtl_alu + 3));
                break;

            default:
                xil_printf("Invalid test case \r\n");
                break;
        }
    }

    xil_printf("End of test RTL_ALU \r\n\n");

    ////////////////////////////////////////////////////////////////////////////////////////
    // HLS ALU TEST
    xil_printf("Performing a test of the HLS_ALU... \r\n");

    int status;
    XHls_alu do_hls_alu;
    XHls_alu_Config *do_hls_alu_cfg;
    do_hls_alu_cfg = XHls_alu_LookupConfig(XPAR_HLS_ALU_0_DEVICE_ID);

    if (!do_hls_alu_cfg) {
        xil_printf("Error loading configuration for do_hls_alu_cfg \r\n");
    }

    status = XHls_alu_CfgInitialize(&do_hls_alu, do_hls_alu_cfg);
    if (status != XST_SUCCESS) {
        xil_printf("Error initializing for do_hls_alu \r\n");
    }

    XHls_alu_Initialize(&do_hls_alu, XPAR_HLS_ALU_0_DEVICE_ID);

    int32_t opa, opb, result;
    unsigned short int func;

    for (int i = 0; i < 18; i++) {
        switch (i) {
            case 0:
                xil_printf("TEST #0: ALU_ADD\r\n");
                opa = 10; opb = 5; func = 0;
                break;

            case 1:
                xil_printf("TEST #1: ALU_SUB\r\n");
                opa = 10; opb = 5; func = 1;
                break;

            case 2:
                xil_printf("TEST #2: ALU_SLT\r\n");
                opa = -10; opb = 5; func = 2;
                break;

            case 3:
                xil_printf("TEST #3: ALU_SLTU\r\n");
                opa = 10; opb = 20; func = 3;
                break;

            case 4:
                xil_printf("TEST #4: ALU_AND\r\n");
                opa = 6; opb = 3; func = 4;
                break;

            case 5:
                xil_printf("TEST #5: ALU_OR\r\n");
                opa = 6; opb = 3; func = 5;
                break;

            case 6:
                xil_printf("TEST #6: ALU_XOR\r\n");
                opa = 6; opb = 3; func = 6;
                break;

            case 7:
                xil_printf("TEST #7: ALU_SLL\r\n");
                opa = 5; opb = 1; func = 7;
                break;

            case 8:
                xil_printf("TEST #8: ALU_SRL\r\n");
                opa = 10; opb = 1; func = 8;
                break;

            case 9:
                xil_printf("TEST #9: ALU_SRA\r\n");
                opa = -4; opb = 1; func = 9;
                break;

            case 10:
                xil_printf("TEST #10: ALU_MUL\r\n");
                opa = 5; opb = 3; func = 10;
                break;

            case 11:
                xil_printf("TEST #11: ALU_MULH\r\n");
                opa = 100000; opb = 100000; func = 11;
                break;

            case 12:
                xil_printf("TEST #12: ALU_MULHSU\r\n");
                opa = 100000; opb = 100000; func = 12;
                break;

            case 13:
                xil_printf("TEST #13: ALU_MULHU\r\n");
                opa = 100000; opb = 100000; func = 13;
                break;

            case 14:
                xil_printf("TEST #14: ALU_DIV\r\n");
                opa = 10; opb = 5; func = 14;
                break;

            case 15:
                xil_printf("TEST #15: ALU_DIVU\r\n");
                opa = 10; opb = 3; func = 15;
                break;

            case 16:
                xil_printf("TEST #16: ALU_REM\r\n");
                opa = 10; opb = 3; func = 16;
                break;

            case 17:
                xil_printf("TEST #17: ALU_REMU\r\n");
                opa = 10; opb = 3; func = 17;
                break;

            default:
                xil_printf("Invalid test case \r\n");
                continue;
        }

        // Write alu inputs to HLS ALU
        XHls_alu_Set_opa(&do_hls_alu, opa);
        XHls_alu_Set_opb(&do_hls_alu, opb);
        XHls_alu_Set_func(&do_hls_alu, func);

        // Start the HLS ALU
        XHls_alu_Start(&do_hls_alu);

        // Wait until done
        while (!XHls_alu_IsDone(&do_hls_alu));

        // Get result
        result = XHls_alu_Get_return(&do_hls_alu);
        xil_printf("opa: 0x%02x, opb: 0x%02x, result: 0x%08x \r\n", opa, opb, result);
    }

    xil_printf("End of test HLS_ALU \r\n");

    cleanup_platform();
    return 0;
}
