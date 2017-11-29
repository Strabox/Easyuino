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

	/** WaterFlowSensor is an API offers the ability to know if it is flowing something through the sensor or not
	using fluid flow meters.
	@see Devices Supported:	 YF-DN40
	@see Devices Tested:	 YF-DN40
	*/
	class WaterFlowSensor : public Device {

	private:
		/** Instance used to redirect the interruptions in the pin transparently to the user */
		static WaterFlowSensor* Singleton;

	protected:
		/** Arduino pin connected to the sensor pulse pin */
		uint8_t _sensorPin;

		/** Incremented by the sensor each time the "turbine" does a full round */
		volatile uint32_t _pulseCounter;

	public:
		/** Constructor
		@param sensorPin Arduino pin connected to the sensor pulse pin
		*/
		WaterFlowSensor(IN uint8_t sensorPin);

		/** Destructor */
		~WaterFlowSensor();

		bool begin();

		void end();

		//virtual void updateFlow();

		/** Checks if there are flowing in the sensor.
		Attention: Since with snapshot in time is impossible to know if it is flowing a single call to this
		method is useless. You need call it constantly (e.g: every second) in order to the API measure
		if it is really flowing or not.
		@return isFlowing True: If there is flow. False: Otherwise.
		*/
		virtual bool isFlowing();

	protected:
		/** Enable the pin interruption that increments the pulse counter. */
		void enablePulseCounting();
		
		/** Disable the pin interruption that increments the pulse counter. */
		void disablePulseCouning();

	private:
		/** Called by the interruption ISR for each pulse and increments the pulse counter. */
		void countPulses();

		/** Binds the interruption event ISR to the sensor instance that will treat it. */
		static void InterruptCaller();

	};

};

#endif