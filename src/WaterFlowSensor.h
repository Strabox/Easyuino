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

#define PULSE_TIMEOUT 500

namespace Easyuino {

	/** WaterFlowSensor is an API offers the ability to know if it is flowing something through the sensor or not
	using fluid flow meters.
	@see Limitation:			Only allows control 1 water flow sensor per sketch
	@see Devices Supported:		YF-DN40
	@see Devices Tested:		YF-DN40
	*/
	class WaterFlowSensor : public Device {

	private:
		/** Instance used to redirect the interruptions in the pin transparently to the user */
		static WaterFlowSensor* Singleton;

	protected:
		/** Arduino pin connected to the sensor pulse pin */
		uint8_t _sensorPin;

		/** Timestamp with the last time a pulse was detected */
		volatile unsigned long _lastPulseTimestamp;

	public:
		/** Constructor
		@param sensorPin Arduino pin connected to the sensor pulse pin
		*/
		WaterFlowSensor(IN uint8_t sensorPin);

		/** Destructor */
		~WaterFlowSensor();

		bool begin();

		void end();

		/** Checks if there there are flow in the sensor.
		@return isFlowing True: If there is flow. False: Otherwise.
		*/
		bool isFlowing() const;

	protected:
		/** Called by the interruption ISR for each pulse. */
		virtual void pulseHandler(IN unsigned long callTimestamp);
	
	private:
		/** ISR - Binds the interruption event to the right sensor instance that will handle it. */
		static void InterruptCaller();

	};

};

#endif