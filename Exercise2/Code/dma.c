#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


extern uint16_t freq1[10];
/* function to setup the PRS */
void setupDMA(uint16_t period)
{
  

  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_PRS; // enable clock for PRS
  *CMU_HFCORECLKEN0 |= 0x1 ; // enable DMA clock
  *(PRS_CH0_CTRL+16) |= 0x1C ; // select TIMER0 as input to PRS channel 0 (16 is the offset for SOURCESEL)
  *PRS_CH0_CTRL |= 1; // the trigger will be TIMER0 overflows (SIGSEL)
  *channel_cfg = 0x3; //enable ping-pong mode

  *(DMA_CTRLBASE+4) = (int) DAC0_CH0DATA + 12; //destination end pointer
  *(DMA_CTRLBASE+8) = (int) channel_cfg; //control 

  *(DMA_CTRLBASE + *(DMA_ALTCTRLBASE)+0x004) = (int) DAC0_CH0DATA + 12 ;//destination end pointer
  *(DMA_CTRLBASE + *(DMA_ALTCTRLBASE)+0x008) = (int) channel_cfg ; //control 

  *DMA_CONFIG = 1; //enable DMA
  *DMA_CHUSEBURSTS=1 ; //Disable the single requests for channel 0 (i.e., do not react to data available, wait for buffer full)
  *DMA_CHREQMASKC=1 ; //Enable buffer-full requests for channel 0
  *DMA_CHALTC=1 ; //Use the primary data structure for channel 0
  *DMA_CHENS=1 ; //Enable channel 0

  *(DAC0_CH0CTRL+4) |= 0 ; //select PRS channel 0 as input to start the conversion
  *(DAC0_CH1CTRL+4) |= 0 ;
  *(DAC0_CH1CTRL+2) |= 1 ; //enable DAC conversions on both channels to be started by a high PRS input signal.

  *DMA_IEN |= 1; //enable interrupt from DMA channel 0

  *DMA_CTRLBASE = (int) &freq1 ;//source end pointer. We should change this value each time we want to play another frequency (next cell of the array), we should therfore do this in the main and not in this setup
  *(DMA_CTRLBASE + *(DMA_ALTCTRLBASE)) = (int) &freq1 ;//source pointer. For each odd step, the alternate source address is getting the frequency of the next sound we want to play (because of ping-pong mode), and vice versa for even number : the primary source address will read the next sound we want to play 
  
}


void play_dma (int play_sound) {

	if(play_sound != 0){
		*DMA_CTRLBASE = (int) &freq1[0] ;
  		*(DMA_CTRLBASE + *(DMA_ALTCTRLBASE)) = (int) &freq1[1] ;
		for (int i = 2; i<9; i++){
			if (i % 2 == 0) {
        		*DMA_CTRLBASE = (int) &freq1[i] ;
			}
			if (i % 2 == 1) {
  			*(DMA_CTRLBASE + *(DMA_ALTCTRLBASE)) = (int) &freq1[i] ;
        		}
		}
        }  
      	play_sound = 0; // clear flag
		
	}

