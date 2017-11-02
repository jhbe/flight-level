#ifndef VECTOR_H
#define VECTOR_H

/**
 * A vector in a three dimensional right-handed coordinate system.
 *
 * Rotation are counter-clockwise when viewing the origin from the
 * positive axis of the rotation angle.
 */
class Vector {
public:
	Vector() {
		m_x = 0.0;
		m_y = 0.0;
		m_z = 1.0;
	}
	Vector(float x, float y, float z) {
		m_x = x;
		m_y = y;
		m_z = z;
	}

	float X() { return m_x; }
	float Y() { return m_y; }
	float Z() { return m_z; }

	/**
	 * Rotates the vector by gz degrees around the Z axis (to the
	 * left if positive Z is up, then by gx degrees around the
	 * X axis (nose up if positive Y is forward and positive X
	 * is to the right) and finally by gy degrees around the
	 * Y axis (rolling right side up if positive Y is forward and
	 * positive X is right).
	 */
	void Rotate(float gx, float gy, float gz);

	/**
	 * Normalizes the length of the vector to one. The vector is
	 * not modified if its length is (very close to) zero.
	 */
	void Normalize(void);

	float Dot(Vector v);
	float Length(void);

	Vector operator*(float s);
	Vector operator+(Vector v);

private:
	float m_x;
	float m_y;
	float m_z;
};

#endif
