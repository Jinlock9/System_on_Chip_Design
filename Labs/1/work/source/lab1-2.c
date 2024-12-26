#include "xparameters.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_types.h"

// Get device IDs from xparameters.h
#define BTN_ID XPAR_AXI_GPIO_BUTTONS_DEVICE_ID
#define LED_ID XPAR_AXI_GPIO_LED_DEVICE_ID
#define BTN_CHANNEL 1
#define LED_CHANNEL 1
#define BTN_MASK 0b1111
#define LED_MASK 0b1111

int LEDOutput() {
   // XGpio_Config *cfg_ptr;
   XGpio led_device, btn_device;
   u32 data;

   xil_printf("Entered function main\r\n");

   // Initialize LED Device
   XGpio_Initialize(&led_device, LED_ID);


   // Initialize Button Device
   XGpio_Initialize(&btn_device, BTN_ID);


   // Set Button Tristate
   XGpio_SetDataDirection(&btn_device, BTN_CHANNEL, 0xF);

   // Set Led Tristate
   XGpio_SetDataDirection(&led_device, LED_CHANNEL, 0x0);


   while (1) {
      data = XGpio_DiscreteRead(&btn_device, BTN_CHANNEL);
      XGpio_DiscreteWrite(&led_device, LED_CHANNEL, data & LED_MASK);
   }

   return XST_SUCCESS; /* Should be unreachable */
}

int main() {
   int Status;
   xil_printf("Start!!\r\n");
   /* Execute the LED output. */
   Status = LEDOutput();
   if (Status != XST_SUCCESS) {
      xil_printf("GPIO output to the LEDs failed!\r\n");
   }

   return 0;
}
