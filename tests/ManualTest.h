/*
ManualTest.h
*/
#ifndef _MANUAL_TEST_h
#define _MANUAL_TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

#define TEST_FRAMEWORK_TAG "[Test Framework]"
#define TEST_NEW_TEST_MESSAGE "Test: "
#define TEST_SUITE_END_MESSAGE "Test Suite Ended"
#define DELAY_BETWEEN_TESTS 4000		// 4 seconds

/* Base class for a set of tests on Arduino. Used to test Easyuino library components in real sensors/devices */
class ManualTest {

	private:
		bool _testFinished;
		Stream* _debugStream;

	public:
		ManualTest(Stream& debugStream);

		void runTestsSetup();

		void runTests();

	protected:
		virtual void testsSetup() = 0;

		virtual void tests() = 0;

		virtual void beforeTest();

		virtual void afterTest();

		virtual void afterTestSuite();
	
		void testStart(char* str);

		void testEnd();

};

#endif