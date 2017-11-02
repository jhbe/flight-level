#include <stdint.h>
#include <stdio.h>
#include "gpio.h"

#define GPIO_BASE       0x20200000UL

#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define GPIO_GPLEV0     13
#define GPIO_GPLEV1     14

#define GPIO_GPEDS0     16
#define GPIO_GPEDS1     17

#define GPIO_GPREN0     19
#define GPIO_GPREN1     20

#define GPIO_GPFEN0     22
#define GPIO_GPFEN1     23

#define GPIO_GPHEN0     25
#define GPIO_GPHEN1     26

#define GPIO_GPLEN0     28
#define GPIO_GPLEN1     29

#define GPIO_GPAREN0    31
#define GPIO_GPAREN1    32

#define GPIO_GPAFEN0    34
#define GPIO_GPAFEN1    35

#define GPIO_GPPUD      37
#define GPIO_GPPUDCLK0  38
#define GPIO_GPPUDCLK1  39

volatile unsigned int* gpio = (unsigned int *) GPIO_BASE;

int fsel_register(int gpio_number) {
	int fsel_register;
	if (0 <= gpio_number && gpio_number < 10) {
		fsel_register = GPIO_GPFSEL0;
	} else if (10 <= gpio_number && gpio_number < 20) {
		fsel_register = GPIO_GPFSEL1;
	} else if (20 <= gpio_number && gpio_number < 30) {
		fsel_register = GPIO_GPFSEL2;
	} else if (30 <= gpio_number && gpio_number < 40) {
		fsel_register = GPIO_GPFSEL3;
	} else if (40 <= gpio_number && gpio_number < 50) {
		fsel_register = GPIO_GPFSEL4;
	} else if (50 <= gpio_number && gpio_number < 60) {
		fsel_register = GPIO_GPFSEL5;
	}
	return fsel_register;
}

void gpio_set_input(int gpio_number, bool edge_detect) {
	gpio[fsel_register(gpio_number)] &= ~(7 << ((gpio_number % 10) * 3));

	if (edge_detect) {
		if (gpio_number < 32) {
			gpio[GPIO_GPREN0] |= (1 << gpio_number);
			gpio[GPIO_GPFEN0] |= (1 << gpio_number);
			gpio[GPIO_GPEDS0] = (1 << gpio_number);
		} else {
			gpio[GPIO_GPREN1] |= (1 << (gpio_number - 32));
			gpio[GPIO_GPFEN1] |= (1 << (gpio_number - 32));
			gpio[GPIO_GPEDS1] = (1 << (gpio_number - 32));
		}
	}
}

void gpio_set_output(int gpio_number) {
	uint32_t value = gpio[fsel_register(gpio_number)];
	value &= ~(7 << ((gpio_number % 10) * 3));
	value |= (1 << ((gpio_number % 10) * 3));
	gpio[fsel_register(gpio_number)] = value;
}

void gpio_set_alt(int gpio_number, int alt) {
	int alt_bits;
	switch(alt) {
	case 0: alt_bits = 4; break;
	case 1: alt_bits = 5; break;
	case 2: alt_bits = 6; break;
	case 3: alt_bits = 7; break;
	case 4: alt_bits = 3; break;
	case 5: alt_bits = 2; break;
	}
	uint32_t value = gpio[fsel_register(gpio_number)];
	value &= ~(7 << ((gpio_number % 10) * 3));
	value |= (alt_bits << ((gpio_number % 10) * 3));
	gpio[fsel_register(gpio_number)] = value;
}

void gpio_set_pullupdown(int gpio_number, int mode) {
	volatile int dummy;
	int i;

	gpio[GPIO_GPPUD] = mode;

	//
	// Wait for at least 150 cycles.
	//
	for (i = 0; i < 150; i++) dummy = i;

	if (gpio_number < 32) {
		gpio[GPIO_GPPUDCLK0] = 1 << gpio_number;
	} else {
		gpio[GPIO_GPPUDCLK1] = 1 << (gpio_number - 32);
	}

	//
	// Wait for at least 150 cycles.
	//
	for (i = 0; i < 150; i++) dummy = i;

	gpio[GPIO_GPPUD] = 0;

	gpio[GPIO_GPPUDCLK0] = 0;
	gpio[GPIO_GPPUDCLK1] = 0;
}

void gpio_clear(int gpio_number) {
	if (gpio_number < 32) {
		gpio[GPIO_GPCLR0] = (1 << gpio_number);
	} else {
		gpio[GPIO_GPCLR1] = (1 << (gpio_number - 32));
	}
}

void gpio_set(int gpio_number) {
	if (gpio_number < 32) {
		gpio[GPIO_GPSET0] = (1 << gpio_number);
	} else {
		gpio[GPIO_GPSET1] = (1 << (gpio_number - 32));
	}
}

int gpio_get(int gpio_number) {
	if (gpio_number < 32) {
		return (gpio[GPIO_GPLEV0] & (1 << gpio_number)) ? 1 : 0;
	} else {
		return (gpio[GPIO_GPLEV1] & (1 << (gpio_number - 32))) ? 1 : 0;
	}
}

int gpio_get_edge_detected(int gpio_number) {
	unsigned int value;
	if (gpio_number < 32) {
		value = (gpio[GPIO_GPEDS0] & (1 << (gpio_number - 0))) ? 1 : 0;
		gpio[GPIO_GPEDS0] = (1 << (gpio_number - 0));
	} else {
		value = (gpio[GPIO_GPEDS1] & (1 << (gpio_number - 32))) ? 1 : 0;
		gpio[GPIO_GPEDS1] = (1 << (gpio_number - 32));
	}
	return value;
}
