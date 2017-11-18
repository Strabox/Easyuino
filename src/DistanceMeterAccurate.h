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
DistanceMeterAccurate.h
*/
#ifndef _EASYUINO_DISTANCE_METER_ACCURATE_h
#define _EASYUINO_DISTANCE_METER_ACCURATE_h

#include "Utilities.h"
#include "DistanceMeterNonBlock.h"

namespace Easyuino {

	enum TemperatureScale : uint8_t {
		CELSIUS, KELVIN, FAHRENHEIT
	};

	/*
	DistanceMeterAccurate offers an API to interact with an Ultrasonic Sensor (US) to measure distance to objects.
	It offers a the same of DistanceMeterNonBlock API plus a possibility to offer the updateDistance and updateDistanceNonBlock
	methods the current air temperature in order to minimize the distance calculation error.
	If you want know more about sound waves velocity dependency with temperature see https://en.wikipedia.org/wiki/Speed_of_sound
	@Limitation: This only allows ONLY 2 instances of DistanceMeterNonBlock/DistanceMeterAccurate per sketch!!!
	@Physical Devices Supported: 
		- HC-SR03, HC-SR04, HC-SR05
	@Physical Devices Tested: 
		- HC-SR04
	*/
	class DistanceMeterAccurate : public DistanceMeterNonBlock {

	private:
		/* Air temperature value collected when the last distance measure was taken */
		float _airTemperature;
		/* The type of scale that matches the provided air temperature */
		TemperatureScale _temperatureScale;

	public:
		DistanceMeterAccurate(IN uint8_t triggerPin, IN uint8_t echoPin);

		DistanceMeterAccurate(IN uint8_t triggerEchoPin);

		~DistanceMeterAccurate();

		float getDistanceCentimeters();

		/** Updates the distance of the US to the objects in a blocking way. Basically if updateDistanceNonBlock
		was not called in the last 3 secs at least the method will block on call and when it finishes the distance
		value can be grabbed by getDistance method. 
		@param airTemperature	- Air temperatures to be used when calculating the distance (good if it is the current temperature)
		@param temperatureScale	- The temperature scale that is being provided (CELSIUS, KELVIN or FAHRENHEIT)
		*/
		void updateDistance(IN float airTemperature = DEFAULT_AIR_TEMPERATURE_CELSIUS, IN TemperatureScale temperatureScale = CELSIUS);

		/* Updates the distance of the US to the objects in a non-blocking way. It means that the call to the method
		will return immediatly and in the "background" the distance measure will ocurr after a while depending on the distance
		to the object the getDistance method can be called to get the new distance value.
		@param airTemperature	- Air temperatures to be used when calculating the distance (good if it is the current temperature)
		@param temperatureScale	- The temperature scale that is being provided (CELSIUS, KELVIN or FAHRENHEIT)
		*/
		void updateDistanceNonBlock(IN float airTemperature = DEFAULT_AIR_TEMPERATURE_CELSIUS, IN TemperatureScale temperatureScale = CELSIUS);

	private:
		/* 
		Calculates the speed of sound based on the air temperature
		@param airTemperature			- Air temperature
		@param temperatureScale			- The scale of the temperature given (CELSIUS, KELVIN or FAHRENHEIT)
		@return soundSpeed	(cm/sec)	- The sound of the speed
		*/
		static float CalculateSoundSpeed(IN float airTemperature = DEFAULT_AIR_TEMPERATURE_CELSIUS, IN TemperatureScale temperatureScale = CELSIUS);

	};

};

#endif
