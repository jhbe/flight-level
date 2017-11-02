#ifndef MPU6050_H
#define MPU6050_H

void mpu6050_init();
void mpu6050_read(float& gx, float& gy, float& gz, float& ax, float& ay, float& az, void (* service)(void));

#endif
