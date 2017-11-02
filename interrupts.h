#ifndef INTERRUPTS_H
#define INTERRUPTS_H

void enable_interrupts();
void enable_gpio_interrupts();
void enable_timer_interrupts(int channel);
bool interrupt_pending(int irq_number);

extern volatile unsigned int* interrupts;

#endif
