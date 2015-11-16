#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
  /* TODO set input and output pins for the joystick */
    
  /* Example of HW access from C code: turn on joystick LEDs D4-D8
     check efm32gg.h for other useful register definitions
  */
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
  *GPIO_PA_CTRL = 0x2;  /* set high drive strength */
  *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
  *GPIO_PA_DOUT = 0; /* turn on all LEDs (LEDs are active low) */

  *GPIO_PC_MODEL = 0x33333333; // set pins as INPUT
  *GPIO_PC_DOUT = 0xFF; // internal pullup

  *GPIO_EXTIPSELL = 0x22222222; // GPIO_PC bits enable interrupt
  *GPIO_EXTIFALL = 0xFF; // enable falling edge interrupt
  *GPIO_IFC = 0xFFFF; // !!!!!!!!IMPORTANT!!!!!!!!!! clear interrupt flags
  *GPIO_IEN = 0xFF; // enable  interrupts

}



