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
many measurements in small space time would be difficult to calculate due to the small window time.
Arduino goes around loop function much faster than the turbine spings so we need accumulate. (Default/Minimum 1 Sec)*/
#define MIN_TIME_BETWEEN_UPDATES 1000

namespace Easyuino {

	/** WaterFlowMeter API extends the WaterFlowSensor API adding the possiblity to know how much water
	is flowing and how much have flown in total.
	@see Limitation:		This allows ONLY 1 instance of WaterFlowMeter per sketch!!
	@see Devices Supported:	 YF-DN40
	@see Devices Tested:	 YF-DN40
	*/
	class WaterFlowMeter : public WaterFlowSensor {

	private:
		/** Calibration factor that comes with the sensor specs (e.g: 0.2 in case of YF-DN40) */
		float _sensorCalibrationFactor;

		/** The last value calculated by the API. Used to avoid calculate the value multiple times when it didn't change. */
		float _cachedFlowRate;
		/** Used to indicate that _cachedFlowRate is dirty making the API use the new measurements to calculate the value. */
		volatile bool _isDirtyFlowRate;

		/** The last measurement counter for pulses. Used to calculate the value of flow rate. */
		volatile unsigned long _previousMeasurementPulses;
		/** The last measurement exat duration. Used to calculate the value of flow rate. */
		volatile unsigned long _previousMeasurementDuration;

		/** The current pulse counter that is being updated */
		volatile unsigned long _currentMeasurementPulseCounter;
		/** When the current measurement started */
		volatile unsigned long _currentMeasurementInitialTimestamp;

	public:
		/** Constructor
		@param sensorPin				Arduino pin connected to the sensor pulse pin
		@param sensorCalibrationFactor	Calibration factor that comes with the sensor specs, necessary for a good
										calculation of the flow rate and the total amount flowed (e.g: 0.2 in case of YF-DN40)
		*/
		WaterFlowMeter(IN uint8_t sensorPin, IN float sensorCalibrationFactor);

		/** Destructor */
		~WaterFlowMeter();

		bool begin();

		void end();

		/** Returns the current flow rate that is passing through the flow meter.
		@return flowRate (Liters/min) The current flow rate.
		*/
		float getFlowRateLitersMin();

	protected:
		void pulseHandler(IN unsigned long callTimestamp);

	};

};

#endif