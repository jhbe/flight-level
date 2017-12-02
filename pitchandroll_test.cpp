#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "pitchandroll.h"
#include <stdio.h>

class PitchAndRollTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(PitchAndRollTest);
  CPPUNIT_TEST(testDefault);
  CPPUNIT_TEST(testZeroPut);
  CPPUNIT_TEST(testRoll);
  CPPUNIT_TEST(testPitch);
  CPPUNIT_TEST(testYaw);
  CPPUNIT_TEST(testYawAndPitch);
  CPPUNIT_TEST(testDtPut);
  CPPUNIT_TEST(testZeroAdjust);
  CPPUNIT_TEST(testRollAdjust);
  CPPUNIT_TEST(testPitchAdjust);
  CPPUNIT_TEST(testPartialAdjust);
  CPPUNIT_TEST(testNegativeWeightAdjust);
  CPPUNIT_TEST(testLargeWeightAdjust);
  CPPUNIT_TEST_SUITE_END();

public:

  void setUp() {
  };

  void tearDown() {
  };

  void testDefault() {
    PitchAndRoll pr;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }

  void testZeroPut() {
    PitchAndRoll pr;

    pr.Put(0.0, 0.0, 0.0, 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);

    pr.Put(0.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }

  void testRoll() {
    PitchAndRoll pr;

    pr.Put(0.0, 30.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(30.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);

    pr.Put(0.0, -30.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }

  void testPitch() {
    PitchAndRoll pr;

    pr.Put(60.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(60.0, pr.Pitch(), 0.001);

    pr.Put(-60.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);

    pr.Put(-45.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-45.0, pr.Pitch(), 0.001);

    pr.Put(45.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }

  void testYawAndPitch() {
    PitchAndRoll pr;

    pr.Put(45.0, 0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(45.0, pr.Pitch(), 0.001);
    pr.Put(0.0, 0.0, 90.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-45.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);

    pr.Put(0.0, 0.0, -180.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(45.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);

  }

  void testYaw() {
    PitchAndRoll pr;

    pr.Put(0.0, 0.0, 45.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }

  void testDtPut() {
    PitchAndRoll pr;

    pr.Put(90.0, 0.0, 0.0, 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(9.0, pr.Pitch(), 0.001);

    pr.Put(90.0, 0.0, 0.0, 0.9);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(90.0, pr.Pitch(), 0.001);
  }


  void testMultiple() {
    PitchAndRoll pr;

    //
    // Start pointing north with zero roll and pitch.
    // Pitch straight up, roll 90 deg CCW then pitch down.
    // Should now be pointing east with zero roll and pitch.
    //
    pr.Put( 90.0,   0.0, 0.0, 1.0);
    pr.Put(  0.0, -90.0, 0.0, 1.0);
    pr.Put(-90.0,   0.0, 0.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }
  
  void testZeroAdjust() {
    PitchAndRoll pr;
    pr.Adjust(1.0, 1.0, 1.0, 0.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
  }
  
  void testRollAdjust() {
    PitchAndRoll pr;
    pr.Adjust(1.0, 0.0, 1.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-45.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Pitch(), 0.001);
    
    PitchAndRoll pr2;
    pr2.Adjust(-1.0, 0.0, 1.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(45.0, pr2.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr2.Pitch(), 0.001);
  }
  
  void testPitchAdjust() {
    PitchAndRoll pr;
    pr.Adjust(0.0, 1.0, 1.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(45.0, pr.Pitch(), 0.001);

    PitchAndRoll pr2;
    pr2.Adjust(0.0, -1.0, 1.0, 1.0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, pr2.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-45.0, pr2.Pitch(), 0.001);
  }
  
  void testPartialAdjust() {
    PitchAndRoll pr;
    pr.Adjust(1.0, 1.0, 0.0, 0.5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Roll", -35.264385, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Pitch", 30.0, pr.Pitch(), 0.001);
  }
  
  void testNegativeWeightAdjust() {
    PitchAndRoll pr;
    pr.Adjust(1.0, 1.0, 0.0, -0.5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Roll", 0.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Pitch", 0.0, pr.Pitch(), 0.001);
  }
  
  void testLargeWeightAdjust() {
    PitchAndRoll pr;
    pr.Adjust(-1.0, 0.0, 0.0, 10.5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Roll", 90.0, pr.Roll(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Pitch", 0.0, pr.Pitch(), 0.001);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PitchAndRollTest);
