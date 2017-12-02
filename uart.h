#ifndef UART_H
#define UART_H

void          uart_init();
void          uart_putc(char c);
bool          uart_rx_fifo_not_empty();
unsigned char uart_getc();
bool          uart_has_overflown();

#endif
