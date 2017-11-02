#ifndef PITCHANDROLL_H
#define PITCHANDROLL_H

#include "vector.h"

/**
 * The purpose of this class is to calculate the pitch and roll after a number
 * of rotations around the X, Y and Z axis. The class also accepts a vector
 * describing "up" and a weight. The purpose of the "up" vector is to address
 * the drift caused by the rotations not being zero for a true zero rotation.
 * 
 * The coordinate system is a ENU fixed on the platform (aircraft); it is not
 * earth referenced:
 * 
 *       | Positive direction | Positive rotation
 *     --|--------------------|-------------------------------------------
 *     X | Right              | Nose down
 *     Y | Forward            | Right side down
 *     Z | Up                 | Counter clockwise when seen from above
 * 
 * Units are degrees and degrees per second.
 * 
 */
class PitchAndRoll {
public:
  PitchAndRoll();
  
  /**
   * Provide rotations around the axis of the platform.
   * 
   * @param gx Pitch in deg/s. Positive when nose up.
   * @param gy Roll in deg/s. Positive when right side down.
   * @param gz Yaw in deg/s. Positive CCW.
   * @param dt The time in seconds since the last Put. May not be negative.
   */
  void Put(float gx, float gy, float gz, float dt);
  
  /**
   * Adjust the perception of "up" by a weighted vector. A weight of zero has
   * no impact. A weight of one will reset the perception of "up" with the
   * provided vector.
   * 
   * @param x X value of the "up" vector.
   * @param y Y value of the "up" vector.
   * @param z Z value of the "up" vector.
   * @param gain The weight to attach to the provided vector. Must be in the
   *             range 0.0 - 1.0 inclusive. Values outside this range will be
   *             clamped.
   */
  void Adjust(float x, float y, float z, float weight);
  
  float Roll();
  float Pitch();
  
private:
  void Calculate();
  
private:
  /*
   * Normalized vector in the platform coordinate system pointing to earth "up".
   */
  Vector m_up;
  
  float m_roll;  // Degrees, positive right side down
  float m_pitch; // Degrees, positive nose up.
};

#endif
