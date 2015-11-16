#include <stdint.h>

// GPIO

#define GPIO_PA_BASE 0x40006000
#define GPIO_PB_BASE 0x40006024
#define GPIO_PC_BASE 0x40006048

#define GPIO_PA_CTRL     ((volatile uint32_t*)(GPIO_PA_BASE + 0x00))
#define GPIO_PA_MODEL    ((volatile uint32_t*)(GPIO_PA_BASE + 0x04))
#define GPIO_PA_MODEH    ((volatile uint32_t*)(GPIO_PA_BASE + 0x08))
#define GPIO_PA_DOUT     ((volatile uint32_t*)(GPIO_PA_BASE + 0x0c))
#define GPIO_PA_DOUTSET  ((volatile uint32_t*)(GPIO_PA_BASE + 0x10))
#define GPIO_PA_DOUTCLR  ((volatile uint32_t*)(GPIO_PA_BASE + 0x14))
#define GPIO_PA_DOUTTGL  ((volatile uint32_t*)(GPIO_PA_BASE + 0x18))
#define GPIO_PA_DIN      ((volatile uint32_t*)(GPIO_PA_BASE + 0x1c))
#define GPIO_PA_PINLOCKN ((volatile uint32_t*)(GPIO_PA_BASE + 0x20))

#define GPIO_PB_CTRL     ((volatile uint32_t*)(GPIO_PB_BASE + 0x00))
#define GPIO_PB_MODEL    ((volatile uint32_t*)(GPIO_PB_BASE + 0x04))
#define GPIO_PB_MODEH    ((volatile uint32_t*)(GPIO_PB_BASE + 0x08))
#define GPIO_PB_DOUT     ((volatile uint32_t*)(GPIO_PB_BASE + 0x0c))
#define GPIO_PB_DOUTSET  ((volatile uint32_t*)(GPIO_PB_BASE + 0x10))
#define GPIO_PB_DOUTCLR  ((volatile uint32_t*)(GPIO_PB_BASE + 0x14))
#define GPIO_PB_DOUTTGL  ((volatile uint32_t*)(GPIO_PB_BASE + 0x18))
#define GPIO_PB_DIN      ((volatile uint32_t*)(GPIO_PB_BASE + 0x1c))
#define GPIO_PB_PINLOCKN ((volatile uint32_t*)(GPIO_PB_BASE + 0x20))

#define GPIO_PC_CTRL     ((volatile uint32_t*)(GPIO_PC_BASE + 0x00))
#define GPIO_PC_MODEL    ((volatile uint32_t*)(GPIO_PC_BASE + 0x04))
#define GPIO_PC_MODEH    ((volatile uint32_t*)(GPIO_PC_BASE + 0x08))
#define GPIO_PC_DOUT     ((volatile uint32_t*)(GPIO_PC_BASE + 0x0c))
#define GPIO_PC_DOUTSET  ((volatile uint32_t*)(GPIO_PC_BASE + 0x10))
#define GPIO_PC_DOUTCLR  ((volatile uint32_t*)(GPIO_PC_BASE + 0x14))
#define GPIO_PC_DOUTTGL  ((volatile uint32_t*)(GPIO_PC_BASE + 0x18))
#define GPIO_PC_DIN      ((volatile uint32_t*)(GPIO_PC_BASE + 0x1c))
#define GPIO_PC_PINLOCKN ((volatile uint32_t*)(GPIO_PC_BASE + 0x20))

#define GPIO_EXTIPSELL ((volatile uint32_t*)(GPIO_PA_BASE + 0x100))
#define GPIO_EXTIPSELH ((volatile uint32_t*)(GPIO_PA_BASE + 0x104))
#define GPIO_EXTIRISE  ((volatile uint32_t*)(GPIO_PA_BASE + 0x108))
#define GPIO_EXTIFALL  ((volatile uint32_t*)(GPIO_PA_BASE + 0x10c))
#define GPIO_IEN       ((volatile uint32_t*)(GPIO_PA_BASE + 0x110))
#define GPIO_IFC       ((volatile uint32_t*)(GPIO_PA_BASE + 0x11c))
#define GPIO_IF        ((volatile uint32_t*)(GPIO_PA_BASE + 0x114))

//Buttons
#define SW5            0x00000010
#define SW6            0x00000020
#define SW7            0x00000040
#define SW8            0x00000080
#define SW1            0x00000000

// CMU

#define CMU_BASE2 0x400c8000

#define CMU_HFPERCLKDIV  ((volatile uint32_t*)(CMU_BASE2 + 0x008))
#define CMU_HFCORECLKEN0 ((volatile uint32_t*)(CMU_BASE2 + 0x040))
#define CMU_HFPERCLKEN0  ((volatile uint32_t*)(CMU_BASE2 + 0x044))
#define CMU_CMD          ((volatile uint32_t*)(CMU_BASE2 + 0x024))
#define CMU_OSCENCMD      ((volatile uint32_t*)(CMU_BASE2 + 0x020))
#define CMU_LFCLKSEL     ((volatile uint32_t*)(CMU_BASE2 + 0x028))
#define CMU_LFACLKEN0    ((volatile uint32_t*)(CMU_BASE2 + 0x058))
#define CMU_LFAPRESC0    ((volatile uint32_t*)(CMU_BASE2 + 0x068))

#define CMU2_HFPERCLKEN0_DAC0   (1 << 17)
#define CMU2_HFPERCLKEN0_PRS    (1 << 15)
#define CMU2_HFPERCLKEN0_GPIO   (1 << 13)
#define CMU2_HFPERCLKEN0_TIMER1 (1 << 6)
#define CMU2_HFPERCLKEN0_TIMER0 (1 << 5)
#define CMU2_HFPERCLKEN0_TIMER3 (1 << 8)

#define CMU_HFCORECLKEN0_DMA (1 << 0)


// TIMER3

#define TIMER3_BASE 0x40010C00

#define TIMER3_CTRL ((volatile uint32_t*)(TIMER1_BASE + 0x00))
#define TIMER3_CMD ((volatile uint32_t*)(TIMER1_BASE + 0x04))
#define TIMER3_IEN ((volatile uint32_t*)(TIMER1_BASE + 0x0c))
#define TIMER3_IF ((volatile uint32_t*)(TIMER1_BASE + 0x10))
#define TIMER3_IFC ((volatile uint32_t*)(TIMER1_BASE + 0x18))
#define TIMER3_TOP ((volatile uint32_t*)(TIMER1_BASE + 0x1c))
#define TIMER3_CNT ((volatile uint32_t*)(TIMER1_BASE + 0x24))

// TIMER1

#define TIMER1_BASE 0x40010400

#define TIMER1_CTRL ((volatile uint32_t*)(TIMER1_BASE + 0x00))
#define TIMER1_CMD ((volatile uint32_t*)(TIMER1_BASE + 0x04))
#define TIMER1_IEN ((volatile uint32_t*)(TIMER1_BASE + 0x0c))
#define TIMER1_IF ((volatile uint32_t*)(TIMER1_BASE + 0x10))
#define TIMER1_IFC ((volatile uint32_t*)(TIMER1_BASE + 0x18))
#define TIMER1_TOP ((volatile uint32_t*)(TIMER1_BASE + 0x1c))
#define TIMER1_CNT ((volatile uint32_t*)(TIMER1_BASE + 0x24))

//TIMER0
#define TIMER0_BASE 0x40010000

#define TIMER0_CTRL ((volatile uint32_t*)(TIMER0_BASE + 0x00))
#define TIMER0_CMD ((volatile uint32_t*)(TIMER0_BASE + 0x04))
#define TIMER0_IEN ((volatile uint32_t*)(TIMER0_BASE + 0x0c))
#define TIMER0_IF ((volatile uint32_t*)(TIMER0_BASE + 0x10))
#define TIMER0_IFC ((volatile uint32_t*)(TIMER0_BASE + 0x18))
#define TIMER0_TOP ((volatile uint32_t*)(TIMER0_BASE + 0x1c))
#define TIMER0_CNT ((volatile uint32_t*)(TIMER0_BASE + 0x24))

//LETIMER
#define LETIMER0_BASE 0x40082000

#define LETIMER0_CTRL ((volatile uint32_t*)(LETIMER0_BASE + 0x00))
#define LETIMER0_CMD ((volatile uint32_t*)(LETIMER0_BASE + 0x04))
#define LETIMER0_IEN ((volatile uint32_t*)(LETIMER0_BASE + 0x2c))
#define LETIMER0_IF ((volatile uint32_t*)(LETIMER0_BASE + 0x20))
#define LETIMER0_IFS ((volatile uint32_t*)(LETIMER0_BASE + 0x24))
#define LETIMER0_IFC ((volatile uint32_t*)(LETIMER0_BASE + 0x28))
#define LETIMER0_CNT ((volatile uint32_t*)(LETIMER0_BASE + 0x0c))
#define LETIMER0_COMP0 ((volatile uint32_t*)(LETIMER0_BASE + 0x10))

// NVIC

#define ISER0 ((volatile uint32_t*)0xe000e100)
#define ISER1 ((volatile uint32_t*)0xe000e104)
#define ICER0 ((volatile uint32_t*)0xe000e180)
#define ICER1 ((volatile uint32_t*)0xe000e184)
#define ISPR0 ((volatile uint32_t*)0xe000e200)
#define ISPR1 ((volatile uint32_t*)0xe000e204)
#define ICPR0 ((volatile uint32_t*)0xe000e280)
#define ICPR1 ((volatile uint32_t*)0xe000e284)
#define IABR0 ((volatile uint32_t*)0xe000e300)
#define IABR1 ((volatile uint32_t*)0xe000e304)

// IPR

#define IPR_BASE  0xe000e400

#define IPR0 ((volatile uint32_t*)(IPR_BASE + 0x00))
#define IPR1 ((volatile uint32_t*)(IPR_BASE + 0x04))
#define IPR2 ((volatile uint32_t*)(IPR_BASE + 0x08))
#define IPR3 ((volatile uint32_t*)(IPR_BASE + 0x0c))

// EMU

#define EMU_BASE2 0x400c6000

#define EMU_CTRL ((volatile uint32_t*)(EMU_BASE2 + 0x000))
#define EMU_LOCK ((volatile uint32_t*)(EMU_BASE2 + 0x008))


// DAC0

#define DAC0_BASE2 0x40004000

#define DAC0_CTRL     ((volatile uint32_t*)(DAC0_BASE2 + 0x000))
#define DAC0_CH0CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x008))
#define DAC0_CH1CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x00c))
#define DAC0_IEN      ((volatile uint32_t*)(DAC0_BASE2 + 0x010))
#define DAC0_IF       ((volatile uint32_t*)(DAC0_BASE2 + 0x014))
#define DAC0_IFS      ((volatile uint32_t*)(DAC0_BASE2 + 0x018))
#define DAC0_IFC      ((volatile uint32_t*)(DAC0_BASE2 + 0x01c))
#define DAC0_CH0DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x020))
#define DAC0_CH1DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x024))
#define DAC0_COMBDATA ((volatile uint32_t*)(DAC0_BASE2 + 0x028))

// DMA

#define DMA_BASE 0x400c2000

#define DMA_STATUS         ((volatile uint32_t*)(DMA_BASE + 0x0000))
#define DMA_CONFIG         ((volatile uint32_t*)(DMA_BASE + 0x0004))
#define DMA_CTRLBASE       ((volatile uint32_t*)(DMA_BASE + 0x0008))
#define DMA_ALTCTRLBASE    ((volatile uint32_t*)(DMA_BASE + 0x000c))
#define DMA_CHUSEBURSTS    ((volatile uint32_t*)(DMA_BASE + 0x0018))
#define DMA_CHUSEBURSTC    ((volatile uint32_t*)(DMA_BASE + 0x001c))
#define DMA_CHREQMASKC     ((volatile uint32_t*)(DMA_BASE + 0x0024))
#define DMA_CHENS          ((volatile uint32_t*)(DMA_BASE + 0x0028))
#define DMA_CHALTC         ((volatile uint32_t*)(DMA_BASE + 0x0034))
#define DMA_IF             ((volatile uint32_t*)(DMA_BASE + 0x1000))
#define DMA_IFC            ((volatile uint32_t*)(DMA_BASE + 0x1008))
#define DMA_IEN            ((volatile uint32_t*)(DMA_BASE + 0x100c))
#define DMA_CH0_CTRL       ((volatile uint32_t*)(DMA_BASE + 0x1100))



#define channel_cfg ((volatile uint32_t*)(0xe0100000)) //defines control block in memory

// PRS

#define PRS_BASE 0x400cc000

#define PRS_CH0_CTRL ((volatile uint32_t*)(PRS_BASE + 0x010))

// System Control Block

#define SCR          ((volatile uint32_t*)0xe000ed10)
#define SYSTICK_CTRL ((volatile uint32_t*)0xe000e010)
#define SYSTICK_LOAD ((volatile uint32_t*)0xe000e014)

