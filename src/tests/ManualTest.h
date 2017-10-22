/*
MIT License

Copyright (c) 2017 André Pires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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