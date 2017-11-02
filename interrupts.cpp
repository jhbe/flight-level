#include "interrupts.h"

#define INTERRUPT_BASE       0x2000B200UL

#define INTERRUPT_PENDB    0
#define INTERRUPT_PEND1    1
#define INTERRUPT_PEND2    2
#define INTERRUPT_FIQCTRL  3
#define INTERRUPT_EN1      4
#define INTERRUPT_EN2      5
#define INTERRUPT_ENB      6
#define INTERRUPT_DIS1     7
#define INTERRUPT_DIS2     8
#define INTERRUPT_DISB     9

#define INTERRUPT_GPIO0   49
#define INTERRUPT_GPIO1   50
#define INTERRUPT_GPIO2   51
#define INTERRUPT_GPIO3   52

volatile unsigned int* interrupts = (unsigned int *) INTERRUPT_BASE;

extern "C" void enable_irq();

void enable_interrupts() {
	enable_irq();
}

void enable_gpio_interrupts() {
	interrupts[INTERRUPT_EN2] = 1 << (INTERRUPT_GPIO0 - 32);
}

void enable_timer_interrupts(int channel) {
	interrupts[INTERRUPT_EN1] = (1 << channel);
}

bool interrupt_pending(int irq_number) {
	unsigned int value;
	if (irq_number < 32) {
		value = (interrupts[INTERRUPT_PEND1] & (1 << (irq_number - 0))) != 0;
	} else {
		value = (interrupts[INTERRUPT_PEND2] & (1 << (irq_number - 32))) != 0;
	}
	return value;
}
