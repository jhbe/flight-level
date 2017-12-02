#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "stddev.h"
#include <stdio.h>

class StdDevTest: public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(StdDevTest);
	CPPUNIT_TEST(testDefault);
	CPPUNIT_TEST(testReset);
	CPPUNIT_TEST(testPositiveValues);
	CPPUNIT_TEST(testAllValues);
	CPPUNIT_TEST(testSpecificValues);
	CPPUNIT_TEST(testLargeNegativeValues);
	CPPUNIT_TEST_SUITE_END();

public:
	StdDev *sd;

	void setUp() {
		sd = new StdDev(10);
	};

	void tearDown() {
		delete sd;
	};

	void testDefault() {
		CPPUNIT_ASSERT(!sd->Valid());
	}

	void testReset() {
		while (!sd->Valid()) {
			sd->Put(0.0);
		}
		sd->Reset();
		CPPUNIT_ASSERT(!sd->Valid());
	}

	void testPositiveValues() {
		while (!sd->Valid()) {
			sd->Put((float)rand() / (float)RAND_MAX);
		}
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, sd->Get(), 0.5);

	}

	void testAllValues() {
		while (!sd->Valid()) {
			sd->Put(1.0 * (float)rand() / (float)RAND_MAX - 1.0);
		}
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sd->Get(), 1.0);
	}

	void testSpecificValues() {
		sd->Put(1.0);
		sd->Put(2.0);
		sd->Put(3.0);
		sd->Put(4.0);
		sd->Put(5.0);
		sd->Put(6.0);
		sd->Put(7.0);
		sd->Put(8.0);
		sd->Put(9.0);
		CPPUNIT_ASSERT(!sd->Valid());
		sd->Put(10.0);
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.02765, sd->Get(), 0.001);

	    for (int i = 0; i < 10; i++) {
	    	sd->Put(15.0);
	    }
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sd->Get(), 0.001);
	}

	void testLargeNegativeValues() {
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		sd->Put(-3.906);
		CPPUNIT_ASSERT(!sd->Valid());
		sd->Put(-3.906);
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sd->Get(), 0.001);

	    for (int i = 0; i < 10; i++) {
	    	sd->Put(15.0);
	    }
		CPPUNIT_ASSERT(sd->Valid());
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sd->Get(), 0.001);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(StdDevTest);
