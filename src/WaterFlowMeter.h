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
		
		/** The flow rate calculated when updateFlow() was called, if it is called frequently this value will be accurate. */
		float _currentFlowRate;
		/** Accumulates the liters that flowed through the sensor */
		float _totalAmountFlowedLiters;

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

		void updateFlow();

		/** Returns the current flow rate that is passing through the flow meter.
		@return flowRate (Liters/min) The current flow rate.
		*/
		float getFlowRate() const;

		/** Returns the current total amount of liters that flowed throudh the flow meter.
		@return totalAmountFlowed (Liters) The total amount flowed through the meter.
		*/
		float getTotalAmountFlowedLiters() const;

		/** Resets the total amount flowed through the meter putting it at 0. */
		void resetTotalAmountFlowed();

	};

};

#endif