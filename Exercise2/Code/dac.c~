#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "dac.h"
#include "timer.h"
#include "sounds.h"

uint16_t dac_addition = 0; // step between 2 samples (43700 times per second)
uint16_t dac_value = DAC_MIN; 
uint32_t samples_in_period = 0;
uint16_t index = 0;
uint32_t number_of_periods = 0;
uint32_t period = 0;
uint8_t finished = 1;

uint16_t freq1[10] = {10, 11, 12, 13, 400, 500, 600, 700, 800, 900};
uint32_t time1[10] = {10, 11, 500, 600, 300, 220, 654, 325, 568, 895};

uint16_t freq2[10] = {260, 330, 392, 440, 330, 392, 260, 440, 260, 440};
uint32_t time2[10] = {200, 200, 200, 200, 300, 220, 654, 325, 568, 895};

uint16_t freq3[10] = {350, 260, 440, 350, 260, 392, 350, 440, 392, 350};
uint32_t time3[10] = {210, 321, 500, 600, 300, 220, 654, 325, 568, 895};

uint16_t freq4[10] = {310, 260, 440, 330, 392, 350, 330, 260, 440, 310};
uint32_t time4[10] = {310, 111, 500, 600, 300, 220, 654, 325, 568, 895};


void setupDAC()
{
  /*
    TODO enable and set up the Digital-Analog Converter
    
    1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0
    2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL
    3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL
    4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt
  */

  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0;
  *DAC0_CTRL = 0x50010;
  disableDAC();
}

void enableDAC()
{
  *DAC0_CH0CTRL = 1;
  *DAC0_CH1CTRL = 1;
}

void disableDAC()
{
  *DAC0_CH0CTRL = 0;
  *DAC0_CH1CTRL = 0;
}

void play(uint8_t index, uint8_t sound_number)
{
	if (sound_number == 1) {
  	uint16_t freq = freq1[index];
  	uint32_t time_milisec = time1[index];
 	sound(freq, time_milisec);
	}

	if (sound_number == 2) {
  	uint16_t freq = freq2[index];
  	uint32_t time_milisec = time2[index];
 	sound(freq, time_milisec);
	}

	if (sound_number == 3) {
  	uint16_t freq = freq3[index];
  	uint32_t time_milisec = time3[index];
 	sound(freq, time_milisec);
	}

	if (sound_number == 4) {
  	uint16_t freq = freq4[index];
  	uint32_t time_milisec = time4[index];
 	sound(freq, time_milisec);
	}
}

// play sound with frequeny freq for time time_milisec
// waits to finish playing of the last sound, then plays this sound
void sound(uint16_t freq, uint32_t time_milisec)
{
  finished = 0; // reseting value
  // calculating 
  samples_in_period = (SAMPLE_RATE / freq);
  dac_addition = (DAC_MAX - DAC_MIN) / samples_in_period;
  number_of_periods = SAMPLE_RATE * time_milisec / samples_in_period;
  number_of_periods /= 1000;
  // reset values to default
  period = 0;
  index = 0;
  dac_value = DAC_MIN;

  // start playing
  enableDAC();
  startLETimer();
  //startTimer(SAMPLE_PERIOD);
}

// get one sample to play 
uint16_t getSample()
{
  // controls time of playing
  if (number_of_periods > period) 
  {
    // controls end of one period (one sawtooth)
    if((index >= samples_in_period) || (dac_value >= DAC_MAX))
    {
      index = 0;
      dac_value = DAC_MIN;
      period++;
    }
    else
    {
      dac_value += dac_addition;
    }
  }
  // stop playing sound
  else
  { 
    finished = 1;
    stopLETimer();
    disableDAC();
    //stopTimer();
    return 0;
  }
  index++;
  return dac_value;
}
