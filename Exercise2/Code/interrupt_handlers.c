#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "dac.h"

#include "efm32gg.h"
void button_interrupt_handler(void);
void changeLEDs(void);
extern uint8_t play_sound;
void handler(void);

void __attribute__ ((interrupt)) LETIMER0_IRQHandler()
{
  uint16_t sample = getSample();
  *DAC0_CH0DATA = sample; //play sample
  *DAC0_CH1DATA = sample;
  *LETIMER0_IFC = 0x1F; // clear interrupt
  *LETIMER0_CMD = 0x4;
  return;
}

/* LETIMER0 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
 /* uint16_t sample = getSample();
  *DAC0_CH0DATA = sample; //play sample
  *DAC0_CH1DATA = sample;
  *TIMER1_IFC = 1; // clear interrupt
  return;*/
}

/* TIMER0 interrupt handler NOT SURE!!!!!!*/
void __attribute__ ((interrupt)) TIMER0_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
 
  *TIMER0_IFC = 1; // clear interrupt
  return;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	handler();


  return;
    /* TODO handle button pressed event, remember to clear pending interrupt */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
	handler();
  return;
    /* TODO handle button pressed event, remember to clear pending interrupt */
}



void __attribute__ ((interrupt)) DMA_IRQHandler() 
{
	while (*DMA_IF == 0) {

}

*DMA_IFC = ~(*DMA_IF); //clear interrupt
  return;
   
}


void handler(){
	// TO-DO: recognize which button was pressed and add action to it
	uint8_t in = ~(*GPIO_PC_DIN);
	if (in == 0x20) { //SW6
	  play_sound = 1;
	}

	if (in == 0x80) { //SW8
	  play_sound = 4;
	}
	
	if (in == 0x10) { //SW5
	  play_sound = 2;
	}
	if (in == 0x40) { //SW7
	  play_sound = 3;
	}
	

	  *GPIO_IFC = ~(*GPIO_PC_DIN); //clear interrupt
}
// for debugging
void changeLEDs(void) 
{
  uint32_t leds_state = *GPIO_PA_DOUT;
  *GPIO_PA_DOUT &= 0xFFFF00FF;  
  leds_state = ~leds_state;
  leds_state &= 0x0000FF00;
  *GPIO_PA_DOUT += leds_state;
}

