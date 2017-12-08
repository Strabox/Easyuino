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

/** Minimum time between the flow rates update. Necessary to create a window of analysis otherwise
many measurements in small space time would be difficult to calculate due to the small window time. 
Arduino goes around loop function much faster than the turbine spings so we need accumulate. (Default/Min 1 Sec)*/
#define MIN_TIME_BETWEEN_UPDATES 1000

namespace Easyuino {

	/** WaterFlowSensor is an API offers the ability to know if it is flowing something through the sensor or not
	using fluid flow meters.
	@see Limitation:		This allows ONLY 1 instance of WaterFlowSensor per sketch!!
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
		volatile unsigned long _pulseCounter;

		/** It is updated by the updateFlow() method and is True if there is flow and False otherwise */
		bool _isFlowing;

		/** Timestamp with the last time API checked the flow */
		unsigned long _lastFlowUpdateTimestamp;

	public:
		/** Constructor
		@param sensorPin Arduino pin connected to the sensor pulse pin
		*/
		WaterFlowSensor(IN uint8_t sensorPin);

		/** Destructor */
		~WaterFlowSensor();

		bool begin();

		void end();

		/** Used to verify how flow is since the last call. This method should be called frequently in order
		to have a up-to-date and reliable view of how the sensor is behaving. A good place to put it is in the
		end of loop function.
		*/
		virtual void updateFlow();

		/** Checks if there there are flow detected in the sensor.
		@return isFlowing True: If there is flow. False: Otherwise.
		*/
		bool isFlowing() const;

	protected:
		/** Enable the pin interruption that increments the pulse counter. */
		void enablePulseCounting();
		
		/** Disable the pin interruption that increments the pulse counter. */
		void disablePulseCounting();

	private:
		/** Called by the interruption ISR for each pulse and increments the pulse counter. */
		void countPulses();

		/** Binds the interruption event ISR to the sensor instance that will handle it. */
		static void InterruptCaller();

	};

};

#endif