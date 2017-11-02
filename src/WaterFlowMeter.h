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
WaterFlowMeter.h
*/
#ifndef _EASYUINO_WATER_FLOW_METER_h
#define _EASYUINO_WATER_FLOW_METER_h

#include "Utilities.h"
#include "Device.h"

namespace Easyuino {

	/*
	Water flow meter used to 
	*/
	class WaterFlowMeter : public Device {

	private:
		/* */
		static WaterFlowMeter* Singleton;

		/* */
		uint8_t _sensorPin;

		/* */
		float _sensorCalibration;

		unsigned long _lastCheckTimestamp;
		/* */
		volatile uint16_t _pulseCounter;
		/* */
		float _flowRate;

	public:
		WaterFlowMeter(IN uint8_t sensorPin);

		~WaterFlowMeter();

		bool begin();

		void end();

		void updateFlowRate();

		bool isFlowing();

		float getFlowRate();

	private:
		void countPulses();

		static void InterruptCaller();

	};

};

#endif