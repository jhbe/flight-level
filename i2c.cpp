#include <cstddef>
#include "gpio.h"
#include "i2c.h"

#define I2C0_BASE       0x20205000UL
#define I2C1_BASE       0x20804000UL

#define I2C_C     0
#define I2C_S     1
#define I2C_DLEN  2
#define I2C_A     3
#define I2C_FIFO  4
#define I2C_DIV   5
#define I2C_DEL   6
#define I2C_CLKT  7

volatile unsigned int* i2c0 = (unsigned int *) I2C0_BASE;
volatile unsigned int* i2c1 = (unsigned int *) I2C1_BASE;

#define I2C_C_EN                0x00008000
#define I2C_C_INTR              0x00000400
#define I2C_C_INTT              0x00000200
#define I2C_C_INTD              0x00000100
#define I2C_C_ST                0x00000080
#define I2C_C_CLEAR             0x00000020
#define I2C_C_READ              0x00000001

#define I2C_S_CLKT              0x00000200
#define I2C_S_ERR               0x00000100
#define I2C_S_RXF               0x00000080
#define I2C_S_TXE               0x00000040
#define I2C_S_RXD               0x00000020
#define I2C_S_TXD               0x00000010
#define I2C_S_RXR               0x00000008
#define I2C_S_TXW               0x00000004
#define I2C_S_DONE              0x00000002
#define I2C_S_TA                0x00000001

//
// GPIO pins used by I2C1 in the ALT0 configuration.
//
#define I2C1_GPIO_SDA1    2
#define I2C1_GPIO_SCL1    3

void i2c1_init(unsigned char slaveAddr) {
  //
  // Disable the pull-up/down on the I2C lines.
  //
  gpio_set_pullupdown(I2C1_GPIO_SDA1, GPIO_MODE_NONE);
  gpio_set_pullupdown(I2C1_GPIO_SCL1, GPIO_MODE_NONE);

  //
  // Set the GPIO pins we need for SPI to ALT0.
  //
  gpio_set_alt(I2C1_GPIO_SDA1, 0);
  gpio_set_alt(I2C1_GPIO_SCL1, 0);

  //
  // Store the slave address.
  //
  i2c1[I2C_A] = slaveAddr;

  //
  // Set the speed to just over 400kHz (maximum speed for the MPU6050).
  // The speed is 250MHz divided by the provided value.
  //
  i2c1[I2C_DIV] = 625;

  //
  // Clear the DONE (by writing a one).
  //
  i2c1[I2C_S] = I2C_S_DONE;
}

void i2c1_write(unsigned char *data, int length, void (* service)(void)) {
  //
  // The transfer shall be of this many bytes.
  //
  i2c1[I2C_DLEN] = length;

  //
  // Clear the FIFO and start a write.
  //
  i2c1[I2C_C] = I2C_C_EN | I2C_C_CLEAR | I2C_C_ST;

  // 
  // Loop here until the transfer is done.
  //
  int i = 0;
  while ((i2c1[I2C_S] & I2C_S_DONE) == 0) {
    //
    // Write a byte to the FIFO if it is not full.
    //
    while (i < length && (i2c1[I2C_S] & I2C_S_TXD) != 0) {
      i2c1[I2C_FIFO] = data[i++];
    }
    
    if (service != NULL) {
      service();
    }
  }
  
  //
  // Clear the DONE (by writing a one) for next time.
  //
  i2c1[I2C_S] = I2C_S_DONE;
}

void i2c1_read(unsigned char *data, int length, void (* service)(void)) {
  //
  // The transfer shall be of this many bytes.
  //
  i2c1[I2C_DLEN] = length;

  //
  // Clear the FIFO and start a read.
  //
  i2c1[I2C_C] = I2C_C_EN | I2C_C_READ | I2C_C_CLEAR | I2C_C_ST;

  // 
  // Loop here until the transfer is done.
  //
  int i = 0;
  while ((i2c1[I2C_S] & I2C_S_DONE) == 0) {
    //
    // Read a byte from the FIFO if it is not empty.
    //
    while (i < length && (i2c1[I2C_S] & I2C_S_RXD) != 0) {
      data[i++] = (unsigned char)i2c1[I2C_FIFO];
    }
    
    if (service != NULL) {
      service();
    }
  }
  
  //
  // Clear the DONE (by writing a one) for next time.
  //
  i2c1[I2C_S] = I2C_S_DONE;
}

void i2c1_writereg(unsigned char reg, unsigned char value, void (* service)(void)) {
  unsigned char data[2] = {reg, value};
  i2c1_write(data, 2, service);
}

unsigned char i2c1_readreg(unsigned char reg, void (* service)(void)) {
  unsigned char value;
  i2c1_write(&reg, 1, service);
  i2c1_read(&value, 1, service);
  return value;
}

void i2c1_writeregs(unsigned char reg, unsigned char *data, int length, void (* service)(void)) {
  i2c1_write(&reg, 1, service);
  i2c1_write(data, length, service);
}

void i2c1_readregs(unsigned char reg, unsigned char *data, int length, void (* service)(void)) {
  i2c1_write(&reg, 1, service);
  i2c1_read(data, length, service);
}
