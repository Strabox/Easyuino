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
#include "ManualTest.h"

ManualTest::ManualTest(Stream& debugStream) {
	_debugStream = &debugStream;
	_testFinished = false;
}

void ManualTest::runTestsSetup() {
	_testFinished = false;
	testsSetup();
}

void ManualTest::runTests() {
	if (!_testFinished) {
		tests();
		afterTestSuite();
		_testFinished = true;
		_debugStream->print(TEST_FRAMEWORK_TAG);
		_debugStream->println(TEST_SUITE_END_MESSAGE);
	}
}

void ManualTest::beforeTest() { /* Do Nothing */ }

void ManualTest::afterTest() { /* Do Nothing */ }

void ManualTest::afterTestSuite() { /* Do Nothing */ }

void ManualTest::testStart(char * customTestMessage){
	beforeTest();
	if (customTestMessage != NULL) {
		_debugStream->print(TEST_FRAMEWORK_TAG);
		_debugStream->print(TEST_NEW_TEST_MESSAGE);
		_debugStream->println(customTestMessage);
	}
}

void ManualTest::testEnd(unsigned long delayAfterTestOverride) {
	afterTest();
	delay(delayAfterTestOverride);
}
