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
WaterFlowSensor.h
*/
#ifndef _EASYUINO_WATER_FLOW_SENSOR_h
#define _EASYUINO_WATER_FLOW_SENSOR_h

#include "Utilities.h"
#include "Device.h"

namespace Easyuino {

	/*
	WaterFlowSensor is an API that uses a water flow sensor to know if it is flowing something through
	the sensor or not. If needed know the flow rate there is the WaterFlowMeter API.
	*/
	class WaterFlowSensor : public Device {

	private:
		/* Instance used to redirect the interruptions in the pin transparently to the user */
		static WaterFlowSensor* Singleton;

	protected:
		/* Arduino pin connected to the sensor cable */
		uint8_t _sensorPin;

		/* Incremented by the sensor each time the "fan" does a full path */
		volatile uint32_t _pulseCounter;

	public:
		WaterFlowSensor(IN uint8_t sensorPin);

		~WaterFlowSensor();

		bool begin();

		void end();

		/*
		Checks if it is flowing something or not.
		ATTENTION: Since a snapshot in time is impossible to know if it is flowing a single call to this
		method is useless. You need call it constantly (e.g: every 3 second) in order to the API know how
		it is going.
		@return - True: If there are something flowing. False: Otherwise.
		*/
		virtual bool isFlowing();

	protected:
		/*
		Used to enable the pin interruption that increments the pulse counter
		*/
		void enablePulseCounting();
		
		/*
		Used to disable the pin interruption that increments the pulse counter
		*/
		void disablePulseCouning();

	private:
		/*
		Called by the interruption ISR for each pulse and increments the pulse counter
		*/
		void countPulses();

		/*
		Static method bind to handle the sensor pin interruption redirecting the call to
		the Singleton instance
		*/
		static void InterruptCaller();

	};

};

#endif