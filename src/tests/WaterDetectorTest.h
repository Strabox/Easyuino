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
WaterDetectorTest.h
*/
#ifndef _EASYUINO_WATER_DETECTOR_TEST_h
#define _EASYUINO_WATER_DETECTOR_TEST_h

#include "Easyuino.h"
#include "ManualTest.h"

using Easyuino::WaterDetector;

class WaterDetectorTest : public ManualTest {

	private:
		WaterDetector* waterDetector;

	public:
		WaterDetectorTest(Stream &debugStream, uint8_t digitalPin, uint8_t analogPin) : ManualTest(debugStream) {
			waterDetector = new WaterDetector(digitalPin, analogPin);
		}

	protected:
		void testsSetup() {
			waterDetector->begin();
		}

		void tests() {
			unsigned long time = 0;

			testStart("SEE PRINTS");
			time = millis();
			while ((millis() - time) < 20000) {
				_debugStream->println(waterDetector->getWaterStatusRange());
				_debugStream->println(waterDetector->isWaterDetected());
				switch (waterDetector->getWaterStatus())
				{
				case WaterDetector::DRY:
					_debugStream->println("DRY");
					break;
				case WaterDetector::FEW_DROPS:
					_debugStream->println("FEW_DROPS");
					break;
				case WaterDetector::WET:
					_debugStream->println("WET");
					break;
				case WaterDetector::FLOOD:
					_debugStream->println("FLOOD");
					break;
				}
				delay(750);
			}
			testEnd();

			testStart("END => ASSERTS TRUE");
			waterDetector->end();
			_debugStream->println(waterDetector->getWaterStatus() == WaterDetector::WaterStatus::NOT_INITIALIZED);
			_debugStream->println(waterDetector->getWaterStatusRange() == -1);
			_debugStream->println(!waterDetector->isWaterDetected());
			testEnd();

		}

		void afterTestSuite() {
			waterDetector->end();
			delete waterDetector;
			waterDetector = NULL;
		}

};

#endif