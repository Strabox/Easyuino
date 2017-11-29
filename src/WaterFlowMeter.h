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
#include "WaterFlowSensor.h"

/** Minimum time between the flow rates update. Necessary to create a window of analysis otherwise
many measurements in small space time would be difficult to calculate due to the small window time. Arduino goes around
loop function faster than the turbine. (Default 1 Sec)*/
#define MIN_TIME_BETWEEN_UPDATES 1000

namespace Easyuino {

	/** WaterFlowMeter API extends the WaterFlowSensor API adding the possiblity to know how much water
	is flowing and how much have flown in total.
	@see Devices Supported:	 YF-DN40
	@see Devices Tested:	 YF-DN40
	*/
	class WaterFlowMeter : public WaterFlowSensor {

	private:
		/** Calibration factor that comes with the sensor (e.g: 0.2 in case of YF-DN40) */
		float _sensorCalibrationFactor;
		/** Timestamp with the last time API checked the flow rate */
		unsigned long _lastCheckTimestamp;
		/** The flow rate calculated when updateFlowRate() was called */
		volatile float _flowRate;

	public:
		/** Constructor
		@param sensorPin				Arduino pin connected to the sensor pulse pin
		@param sensorCalibrationFactor	Calibration factor that comes with the sensor (e.g: 0.2 in case of YF-DN40)
		*/
		WaterFlowMeter(IN uint8_t sensorPin, IN float sensorCalibrationFactor);

		/** Destructor */
		~WaterFlowMeter();

		bool begin();

		void end();

		bool isFlowing();

		/**

		*/
		void updateFlowRate();

		/**

		*/
		float getFlowRate() const;

	};

};

#endif