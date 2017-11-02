#include "uart.h"
#include "aux.h"
#include "gpio.h"

volatile int dummy;

#define UART_TX_GPIO   14
#define UART_RX_GPIO   15

void uart_init() {
	//
	// ALT5 for GPIO14 (TX) and GPIO15 (RX). ALT5 is the auxiliary UART.
	//
	gpio_set_alt(UART_TX_GPIO, 5);
	gpio_set_alt(UART_RX_GPIO, 5);

	//
	// Enable Auxiliaries.
	//
	aux[AUX_ENABLES] = 1;

	//
	// No interrupts.
	//
	aux[AUX_MU_IER_REG] = 0;

	//
	// Clear FIFO.
	//
	aux[AUX_MU_IIR_REG] = 0xc6;

	//
	// Disable the transmitter.
	//
	aux[AUX_MU_CNTL_REG] = 0;

	//
	// 8 bit mode.
	//
	aux[AUX_MU_LCR_REG] = 3;

	//
	// RTS low, but really don't care.
	//
	aux[AUX_MU_MCR_REG] = 0;

	//
	// 9600 baud. ((2500000000/9600)/8-1=3254
	// 115200 baud. ((2500000000/115200)/8-1=270
	//
	aux[AUX_MU_BAUD_REG] = 270;

	//
	// Enable the transmitter and receiver. No flow control.
	//
	aux[AUX_MU_CNTL_REG] = 3;
}

void uart_putc(char c) {
	while(aux[AUX_MU_STAT_REG] & AUX_MU_STAT_REG_TX_FIFO_FULL);
	aux[AUX_MU_IO_REG] = c;
}

int uart_rx_fifo_not_empty() {
	return (aux[AUX_MU_STAT_REG] & AUX_MU_STAT_REG_RX_FIFO_NOT_EMPTY) ? 1 : 0;
}

unsigned char uart_getc() {
	while (!(aux[AUX_MU_STAT_REG] & AUX_MU_STAT_REG_RX_FIFO_NOT_EMPTY));
	return aux[AUX_MU_IO_REG];
}

int uart_has_overflown() {
	return (aux[AUX_MU_LSR_REG] & AUX_MU_LSR_REG_OVERRUN) ? 1 : 0;
}
