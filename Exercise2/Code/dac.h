#define SAMPLE_RATE 32768
#define DAC_MIN 1000
#define DAC_MAX 3000
/* The period between sound samples, in clock cycles */
#define SAMPLE_PERIOD 10

uint8_t size_sample1(void);
void setupDAC(void);
void enableDAC(void);
void disableDAC(void);
void sound(uint16_t freq, uint32_t time_milisec);
uint16_t getSample(void);
void play(uint8_t index, uint8_t sound_number);
