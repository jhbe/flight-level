#ifndef UART_H
#define UART_H

void uart_init();
void uart_putc(char c);

int uart_rx_fifo_not_empty();
unsigned char uart_getc();
int uart_has_overflown();

#endif
