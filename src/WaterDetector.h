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
WaterDetector.h
*/
#ifndef _EASYUINO_WATER_DETECTOR_h
#define _EASYUINO_WATER_DETECTOR_h

#include "Utilities.h"
#include "Device.h"

/* Levels used to categorize the wetness */
#define DRY_MAX_LEVEL 975
#define FEW_WATER_DROPS_MAX_LEVEL 750
#define WET_MAX_LEVEL 400
#define FLOOD_MAX_LEVEL 0

namespace Easyuino {
	
	/** Categories of how wet is the water sensor */
	enum class WaterStatus : uint8_t {
		DRY = 0, FEW_DROPS = 1, WET = 2, FLOOD = 3, INVALID = 4, NOT_INITIALIZED = 255
	};

	/** RainDetector API is used to detect the amount of water that is touching the sensor. */
	class WaterDetector : public Device {

	private:
		/** Arduino pin connected to digital pin (Normally D0 in sensor board) */
		uint8_t _digitalPin;
		/** Arduino pin connected to analog pin (Normally A0 in sensor board) */
		uint8_t _analogPin;
		/** Digital level that triggers the water sensor */
		uint8_t _digitalPinTriggerLevel;

	public:
		/** Constructor
		@param digitalPin	Arduino pin connected to digital pin (Normally D0 in sensor board)
		@param analogPin	Arduino pin connected to analog pin (Normally A0 in sensor board)
		*/
		WaterDetector(IN uint8_t digitalPin, IN uint8_t analogPin);

		/** Destructor */
		~WaterDetector();

		bool begin();

		/** Initialize the WaterDetector API putting it ready to receive requests.
		@param	digitalPinTriggerLevel The digital level that is triggered in digital pin when water is sensed.
		@return	True: If the device was initialized. False: Otherwise.
		*/
		bool begin(IN uint8_t digitalPinTriggerLevel);

		void end();

		/** Returns an enumerate value depending on how wet is the sensor.
		@return waterStatus	Available options in WaterStatus enumerate.
		*/
		WaterStatus getWaterStatus();

		/** Return a number in [0,1023] depending on dry is the sensor. Used in getWaterStatus() method.
		@return	Number in range [0,1023], 1023 = dry and 0 = flood or -1 if API is not initialized
		*/
		unsigned int getWaterStatusRange();

		/** Used to get the value from the digital pin that is activated when a wet threshold is passed.
		Normally the threshold is set using the potentiometer in the water detector board.
		@return	True: If water threshold detection passed. False: Otherwise.
		*/
		bool isWaterDetected();

	};

};

#endif
