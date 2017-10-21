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
	_debugStream->print(TEST_FRAMEWORK_TAG);
	_debugStream->print(TEST_NEW_TEST_MESSAGE);
	_debugStream->println(customTestMessage);
}

void ManualTest::testEnd() {
	afterTest();
	delay(DELAY_BETWEEN_TESTS);
}
