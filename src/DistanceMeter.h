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
DistanceMeter.h
*/
#ifndef _EASYUINO_DISTANCE_METER_h
#define _EASYUINO_DISTANCE_METER_h

#include "Utilities.h"
#include "Device.h"

#define ECHO_TIMEOUT_MICROS 30000UL				// 0.03 Seconds (Time of sound to travel 8 meters plus a small bonus)
#define DELAY_AFTER_TRIGGER_LOW_MICROS 2		// 2 Micro Seconds
#define ECHO_PULSE_DURATION_MICROS 10			// 10 Micro Seconds

#define DEFAULT_AIR_TEMPERATURE_CELSIUS 20.0f	// Default air temperature used 20 Celsius
#define DEFAULT_SOUND_SPEED_CM_PER_SEC 34340.0f	// Sound Speed in air at 20 Celsius cm/sec

namespace Easyuino {

	/*
	DistanceMeter offers an API to interact with an Ultrasonic Sensor (US) to measure distances to objects using sound waves.
	@Physical Devices Supported: 
		- HC-SR03, HC-SR04, HC-SR05
	@Physical Devices Tested: 
		- HC-SR04
	*/
	class DistanceMeter : public Device {

	protected:
		/* Trigger pin used to trigger the echo wave emission in the US */
		uint8_t _triggerPin;
		/* Pin that is set to low by US when emitted echo wave arrives */
		uint8_t _echoPin;
		/* Used to know if it is in a middle of a distance measure  */
		volatile bool _isEchoing;
		/* It contains a cached value of the distance to the object */
		volatile float _distance;

	public:
		DistanceMeter(IN uint8_t triggerPin, IN uint8_t echoPin);

		/* Contructor used when we have US with only one pin for trigger and echo */
		DistanceMeter(IN uint8_t triggerEchoPin);

		~DistanceMeter();

		bool begin();

		void end();

		/*
		Gets the last value that the API measured using the US.
		@return distance (Centimeters) - This value will always be the the most updated valued that the API have.
		*/
		virtual float getDistanceCentimeters();

		/*
		Gets the last value that the API measured using the US.
		@return distance (Inches) - This value will always be the the most updated valued that the API have (Inches).
		*/
		float getDistanceInches();

		/* 
		Updates the distance of the US to the objects.
		Distance value is avaialble using getDistance methods after calling this method.
		ATTENTION: This method blocks while the measuring so the arduino waits for the measure to be concluded,
		if you want a non block update distance method look for DistanceMeterNonBlock API.
		*/
		virtual void updateDistance();

	protected:
		/*
		Execute a block distance measure and calculate the distance based on the sound speed
		@return distance (Centimeters) - Distance measured 
		*/
		float executeUpdateDistanceBlock(IN float soundSpeedCmSec);

	};

};


#endif
