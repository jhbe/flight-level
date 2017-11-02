#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "pitchandroll.h"
#include <stdio.h>
#include <math.h>

class VectorTest: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(VectorTest);
	CPPUNIT_TEST(testDefault);
	CPPUNIT_TEST(testExplicitConstructor);
	CPPUNIT_TEST(testNormalize);
	CPPUNIT_TEST(testNormalizeZero);
	CPPUNIT_TEST(testRotatePositiveX);
	CPPUNIT_TEST(testRotateNegativeX);
	CPPUNIT_TEST(testRotatePositiveY);
	CPPUNIT_TEST(testRotateNegativeY);
	CPPUNIT_TEST(testRotatePositiveZ);
	CPPUNIT_TEST(testRotateNegativeZ);
	CPPUNIT_TEST(testRotateXThenZ);
	CPPUNIT_TEST_SUITE_END();

public:

	void testDefault() {
		Vector v;

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0, v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0, v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0, v.Z(), 0.001);
	}

	void testExplicitConstructor() {
		Vector v(23.0, 34.0, 45.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 23.0, v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 34.0, v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 45.0, v.Z(), 0.001);
	}

	void testNormalize() {
		Vector v(1.0, 2.0, 3.0);
		v.Normalize();

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0 / sqrt(14), v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 2.0 / sqrt(14), v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 3.0 / sqrt(14), v.Z(), 0.001);
	}

	void testNormalizeZero() {
		Vector v(0.0, 0.0, 0.0);
		v.Normalize();

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0, v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0, v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 0.0, v.Z(), 0.001);
	}

	void testRotatePositiveX() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(45.0, 0.0, 0.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0, v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0 * sqrt(2), v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 * sqrt(2), v.Z(), 0.001);
	}

	void testRotateNegativeX() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(-45.0, 0.0, 0.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0, v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0 * sqrt(2), v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 0.0 * sqrt(2), v.Z(), 0.001);
	}

	void testRotatePositiveY() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(0.0, 45.0, 0.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0 * sqrt(2), v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0, v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 0.0 * sqrt(2), v.Z(), 0.001);
	}

	void testRotateNegativeY() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(0.0, -45.0, 0.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0 * sqrt(2), v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0, v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 * sqrt(2), v.Z(), 0.001);
	}

	void testRotatePositiveZ() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(0.0, 0.0, 45.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0 * sqrt(2), v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0 * sqrt(2), v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0, v.Z(), 0.001);
	}

	void testRotateNegativeZ() {
		Vector v(1.0, 1.0, 1.0);
		v.Rotate(0.0, 0.0, -45.0);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0 * sqrt(2), v.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0 * sqrt(2), v.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0, v.Z(), 0.001);
	}

	void testRotateXThenZ() {
		Vector x(1.0, 0.0, 0.0);
		Vector y(0.0, 1.0, 0.0);
		Vector z(0.0, 0.0, 1.0);

		x.Rotate(45.0, 0.0, 0.0);
		y.Rotate(45.0, 0.0, 0.0);
		z.Rotate(45.0, 0.0, 0.0);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0, x.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0, x.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 0.0, x.Z(), 0.001);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0 / sqrt(2), y.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0 / sqrt(2), y.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 / sqrt(2), y.Z(), 0.001);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0 / sqrt(2), z.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", -1.0 / sqrt(2), z.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 / sqrt(2), z.Z(), 0.001);

		x.Rotate(0.0, 0.0, 90.0);
		y.Rotate(0.0, 0.0, 90.0);
		z.Rotate(0.0, 0.0, 90.0);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 0.0, x.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 1.0, x.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 0.0, x.Z(), 0.001);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", -1.0 / sqrt(2), y.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0 / sqrt(2), y.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 / sqrt(2), y.Z(), 0.001);

		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("X", 1.0 / sqrt(2), z.X(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Y", 0.0 / sqrt(2), z.Y(), 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Z", 1.0 / sqrt(2), z.Z(), 0.001);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
