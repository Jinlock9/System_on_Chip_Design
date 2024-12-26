#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for peripheral RTL_DIVIDER

// we will use the Base Address of the RTL_DIVIDER
Xuint32 *baseaddr_p = (Xuint32 *) XPAR_RTL_DIVIDER_0_S00_AXI_BASEADDR;

int main() {
    init_platform();
    xil_printf("Performing a test of the RTL_DIVIDER...\r\n");

    // Write multiplier inputs to register 0
    *(baseaddr_p + 0) = 0x00080003;
    xil_printf("Wrote to register 0: 0x%08x\r\n", *(baseaddr_p + 0));

    // Read multiplier output from register 1 and 2
    xil_printf("Read from register 1 - DIV: 0x%08x\r\n", *(baseaddr_p + 1));
    xil_printf("Read from register 2 - MOD: 0x%08x\r\n", *(baseaddr_p + 2));

    xil_printf("End of test\r\n");

    cleanup_platform();
    return 0;
}
