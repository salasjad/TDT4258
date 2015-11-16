void button_interrupt_handler(void);
/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler();

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler();

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler();

/* DMA interrupt handler */
void __attribute__ ((interrupt)) DMA_IRQHandler();

/* TIMER0 interrupt handler */
void __attribute__ ((interrupt)) TIMER0_IRQHandler();
