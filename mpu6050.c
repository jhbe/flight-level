#include <cstddef>
#include "i2c.h"

#define MPU6050_ADDR             0x68 // When AD0 == 0

#define MPU6050_SMPRT_DIV          25
#define MPU6050_REG_CONFIG         26
#define MPU6050_REG_GYRO_CONFIG    27
#define MPU6050_REG_ACCEL_CONFIG   28
#define MPU6050_REG_ACCEL_X        59
#define MPU6050_REG_POWER_MGMT_1  107
#define MPU6050_REG_WHO_AM_I      117

void mpu6050_init() {
  i2c1_init(MPU6050_ADDR);
  
  //
  // Ensure we're communicating with an MPU6050 by reading the CHIP ID field. It
  // should be the I2C ADDRESS with the lowest bit always set to zero.
  //
  if (i2c1_readreg(MPU6050_REG_WHO_AM_I, NULL) != MPU6050_ADDR) {
    while (1);
  }
  
  //
  // Clear the SLEEP bit. Disable the temperature sensor. Use the X gyro as the
  // clock source.
  //
  i2c1_writereg(MPU6050_REG_POWER_MGMT_1, 0x09, NULL);
  
  //
  // Set the sample rate to 1kHz by dividing the 1kHz gyro rate by 1.
  //
  i2c1_writereg(MPU6050_SMPRT_DIV, 0x00, NULL);
  
  //
  // Set accelerometers and gyros to 1kHZ with maximum bandwidth. No external
  // sync. This will set the bandwidth of the gyros and accell to about 180Hz.
  //
  i2c1_writereg(MPU6050_REG_CONFIG, 0x01, NULL);
  
  //
  // Set accelerometer range to +-8g. No self test.
  //
  i2c1_writereg(MPU6050_REG_ACCEL_CONFIG, 0x10, NULL);
  
  //
  // Set gyro range to +-500deg/s. No self test.
  //
  i2c1_writereg(MPU6050_REG_GYRO_CONFIG, 0x08, NULL);
}

float toDegPerSec(unsigned char *data) {
  short signed int value = (short int)((data[0] << 8) | data[1]);
  return float(value) * 500 / 32768.0;
}

float toG(unsigned char *data) {
  short signed int value = (short int)((data[0] << 8) | data[1]);
  return (float)value / 4096.0;
}

void mpu6050_read(float& gx, float& gy, float& gz, float& ax, float& ay, float& az, void (* service)(void)) {
  //
  // Read the gyro and accel registers.
  //
  unsigned char data[14];
  i2c1_readregs(MPU6050_REG_ACCEL_X, data, 14, service);
  
  //
  // Convert them to floats of the correct unit given the configuration of the
  // ranges (+-8g and +-500 deg/s).
  //
  ax = toG(&data[0]);
  ay = toG(&data[2]);
  az = toG(&data[4]);
  // Temperature data at offset 6.
  gx = toDegPerSec(&data[8]);
  gy = toDegPerSec(&data[10]);
  gz = toDegPerSec(&data[12]);
}
