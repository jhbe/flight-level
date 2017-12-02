#ifndef GPIO_H
#define GPIO_H

#define GPIO_MODE_NONE    0x00
#define GPIO_MODE_DOWN    0x01
#define GPIO_MODE_UP      0x02

void gpio_set_input (int gpio_number, bool edge_detect = false);
void gpio_set_output(int gpio_number);
int  gpio_get       (int gpio_number);
void gpio_set       (int gpio_number);
void gpio_clear     (int gpio_number);
void gpio_copy      (int from_gpio_number, int to_gpio_number);

int  gpio_get_edge_detected(int gpio_number);

void gpio_set_alt       (int gpio_number, int alt);
void gpio_set_pullupdown(int gpio_number, int mode);

//extern volatile unsigned int* gpio;

#endif
