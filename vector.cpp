#include <math.h>
#include "vector.h"
#include <stdio.h>

#define PI 3.1415926535897932384626433832795f

void Vector::Rotate(float gx, float gy, float gz) {
	float tmp;

	//
	// Rotate around the Z-axis.
	//
	float cz = cos(gz * PI / 180.0f);
	float sz = sin(gz * PI / 180.0f);
	tmp = m_x * cz - m_y * sz;
	m_y = m_x * sz + m_y * cz;
	m_x = tmp;

	//
	// Rotate around the X-axis.
	//
	float cx = cos(gx * PI / 180.0f);
	float sx = sin(gx * PI / 180.0f);
	tmp = m_y * cx - m_z * sx;
	m_z = m_y * sx + m_z * cx;
	m_y = tmp;

	//
	// Rotate around the Y-axis.
	//
	float cy = cos(gy * PI / 180.0f);
	float sy = sin(gy * PI / 180.0f);
	tmp = m_x * cy + m_z * sy;
	m_z = -m_x * sy + m_z * cy;
	m_x = tmp;
}

void Vector::Normalize(void) {
	float length = Length();

	if (length > 0.00001) {
		m_x /= length;
		m_y /= length;
		m_z /= length;
	}
}

float Vector::Dot(Vector v) {
	return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

float Vector::Length(void) {
	return (float) sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector Vector::operator*(float s) {
	return Vector(m_x * s, m_y * s, m_z * s);
}

Vector Vector::operator+(Vector v) {
	return Vector(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
}
