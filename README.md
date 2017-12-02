# Summary

This is a baremetal raspberry pi zero firmware that provides a gyro stabilized
flight for a radio controlled airplane. The raspberry pi zero and an MPU6050
sits between the receiver and the ESC/servos. The MPU6050 gyro and accelerometer
provides the raspberry pi  zero with rotational speeds around the X, Y and Z
axis as well as accelerations along the X, Y and Z axis.

The raspberry pi uses the AUX channel to determine if the remaining four channel
should go straight through unchanged or if the raspberry pi zero shall use the
gyro/accel data to provide a level flight. In the later case the AILE and ELEV
signals are use to slightly alter the flight level to facilitate (slow) turns
and altitude changes.

THRO and RUDD signals always go straight through (support for them in the
raspberry pi zero is to facilitate future drone management).

      +-------+           +----------------+            +-------+
      |  RX   |           | RPI Zero       | ---------> | ESC   |
      |       |           |                |            +-------+
      | AR610 | --THRO--> |                |
      |       | --AILE--> |                |            +-------+
      |       | --ELEV--> |                | ---------> | Servo |
      |       | --RUDD--> |                |            +-------+
      |       | --AUX1--> |                |
      |       | --AUX2--> |                |            +-------+
      |       |           |                | ---------> | Servo |
      |       |           |                |            +-------+
      |       |           |                |
      |       |           |                |            +-------+
      |       |           |                | ---------> | Servo |
      +-------+           +----------------+            +-------+
                                 |      
                                 | I2C
                                 |
                            +-----------+
                            |  MU6050   |      
                            +-----------+
# Usage

## Voltage Levels

The Spektrum AR610 servo signal voltage levels are about 3.0 volts. That is
compatible with the raspberry pi zero. *OTHER RECEIVERS MAY USE 5V AND MUST
NOT BE CONNECTED TO THE RASPBERRY PI ZERO AS-IS; USE LEVEL CONVERTERS*.

## Pins

 P1 Header | Connection
-----------|--------------------
 3         | MPU6050
 5         | MPU6050
 7         | THRO
11         | AILE
12         | Servo 1 / ESC
13         | ELEV
16         | Servo 2
18         | Servo 3
19         | RUDD
21         | GEAR
22         | Servo 4
23         | AUX1

...plus various GND and +5V.

## Mounting

The MPU6050 must be mounted with the X axis to the right, Y axis forward and
Z axis up relative to the airplane.

## Calibration

The raspberry pi zero will enter calibration mode on boot. The green LED will
flash until calibration is complete, at which time it will be turned on.

During calibration the airplane must be still and upright.

# Firmware Design


# TODO

- Passthrough on second Reset.

