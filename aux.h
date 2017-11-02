#ifndef AUX_H_
#define AUX_H_

#define AUX_IRQ          0  // Interrupt Status
#define AUX_ENABLES      1  // Enables
#define AUX_MU_IO_REG   16  // Mini UART I/O Data
#define AUX_MU_IER_REG  17  // Mini UART Interrupt Enable
#define AUX_MU_IIR_REG  18  // Mini UART Interrupt Identify
#define AUX_MU_LCR_REG  19  // Mini UART Line Control
#define AUX_MU_MCR_REG  20  // Mini UART Modem Control
#define AUX_MU_LSR_REG  21  // Mini UART Line Status
#define AUX_MU_MSR_REG  22  // Mini UART Modem Status
#define AUX_MU_SCRATCH  23  // Mini UART Scratch
#define AUX_MU_CNTL_REG 24  // Mini UART Extra Control
#define AUX_MU_STAT_REG 25  // Mini UART Extra Status
#define AUX_MU_BAUD_REG 26  // Mini UART Baud rate

#define AUX_MU_STAT_REG_TX_FIFO_FULL       0x20
#define AUX_MU_STAT_REG_RX_FIFO_NOT_EMPTY  0x01

#define AUX_MU_LSR_REG_OVERRUN             0x02

extern volatile unsigned int* aux;

#endif /* AUX_H_ */
