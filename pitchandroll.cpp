#include <math.h>
#include "pitchandroll.h"

PitchAndRoll::PitchAndRoll() {
	m_up = Vector(0.0, 0.0, 1.0);
	m_roll = 0.0;
	m_pitch = 0.0;
}

void PitchAndRoll::Put(float gx, float gy, float gz, float dt) {
	m_up.Rotate(-gx * dt, -gy * dt, -gz * dt);
	m_up.Normalize();

	Calculate();
}

void PitchAndRoll::Adjust(float x, float y, float z, float weight) {
	if (weight < 0.0) {
		weight = 0.0;
	} else if (weight > 1.0) {
		weight = 1.0;
	}

	m_up.Normalize();

	Vector v(x, y, z);
	v.Normalize();
	m_up = m_up * (1.0 - weight) + v * weight;
	m_up.Normalize();

	Calculate();
}

float PitchAndRoll::Roll() {
	return m_roll;
}

float PitchAndRoll::Pitch() {
	return m_pitch;
}

/**
 * Calculates m_roll and m_pitch given m_up.
 */
void PitchAndRoll::Calculate() {
	/*
	 * The pitch is the angle between the up vector and the up vector projected on
	 * the XZ plane. Both vectors are normalized, so no need to divide by the
	 * product of the lengths of the vectors before acos().
	 *
	 * If the length of the projected vector is (very close to) zero, then the
	 * pitch is either 90 or -90 deg.
	 *
	 * If m_up.Y == 0, then the dot product may be slightly greater than one
	 *, which will cause acos() to generate a nan or crash.
	 *
	 * The pitch is negative if the up vector Y component is negative.
	 */
	Vector v(m_up.X(), 0.0, m_up.Z());
	v.Normalize();

	if (v.Length() > 0.0001) {
		float dot = m_up.Dot(v);
		if (dot < 1.0) {
			m_pitch = 180.0 / M_PI * acos(dot);
		} else {
			m_pitch = 0.0;
		}
	} else {
		m_pitch = 90.0;
	}
	if (m_up.Y() < 0.0) {
		m_pitch *= -1.0;
	}

	/*
	 * The roll is the angle between the Z axis and the projected vector. The
	 * roll is negative if the up vector X component is positive.
	 *
	 * If the projected vector was of zero length and the pitch therefore is 90
	 * or -90, then the roll cannot be calculated and will be assumed to be
	 * zero.
	 *
	 * If m_up == Z axis, then the dot product may generate a number slightly
	 * greater than one, which will cause acos() to generate a NaN or crash.
	 */
	if (v.Length() > 0.0001) {
		float dot = v.Dot(Vector(0.0, 0.0, 1.0));
		if (dot < 1.0) {
			m_roll = 180.0 / M_PI * acos(dot);
		} else {
			m_roll = 0.0;
		}
		if (m_up.X() > 0.0) {
			m_roll *= -1.0;
		}
	} else {
		m_roll = 0.0;
	}
}
