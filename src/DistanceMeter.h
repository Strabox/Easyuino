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

/** 0.03 Seconds (Time of sound to travel 8 meters plus a small bonus) */
#define ECHO_TIMEOUT_MICROS 30000UL
/** 2 Micro Seconds */
#define DELAY_AFTER_TRIGGER_LOW_MICROS 2
/** 10 Micro Seconds */
#define ECHO_PULSE_DURATION_MICROS 10

/** Default air temperature used to measurements: 20 Celsius */
#define DEFAULT_AIR_TEMPERATURE_CELSIUS 20.0f
/** Sound Speed in air at 20 Celsius: 34340.0 cm/sec */
#define DEFAULT_SOUND_SPEED_CM_PER_SEC 34340.0f

namespace Easyuino {

	/** Used to represent the at least supported Ultrasonic Module models 
	enum UltrasonicModule : uint8_t {
		HC_SR03, 
		HC_SR04, 
		HC_SR05
	};
	*/

	/** DistanceMeter offers a simple API to interact with an Ultrasonic Module to measure distances to objects.
	@see Devices Supported:	 HC-SR03, HC-SR04, HC-SR05
	@see Devices Tested:	 HC-SR04
	*/
	class DistanceMeter : public Device {

	protected:
		/** Arduino pin used to trigger the echo wave emission */
		uint8_t _triggerPin;
		/** Arduino pin that is set to LOW by when reflected echo wave arrives */
		uint8_t _echoPin;
		/** Used to know if it is in a middle of a measurement */
		volatile bool _isEchoing;
		/** It contains a cached value of the last distance measured. Avoid calculate all the time. */
		volatile float _distance;

	public:
		/** Constructor
		@param triggerPin	Arduino pin connected to the trigger pin of the Ultrasonic Module
		@param echoPin		Arduino pin connected to the echo pin of the Ultrasonic Module
		*/
		DistanceMeter(IN uint8_t triggerPin, IN uint8_t echoPin);

		/** Contructor used with Ultrasonic Modules that have only one pin for trigger and echo 
		@param triggerEchoPin	Arduino pin connected to the trigger&echo pin of the Ultrasonic Module
		*/
		DistanceMeter(IN uint8_t triggerEchoPin);

		/** Destructor */
		~DistanceMeter();

		bool begin();

		void end();

		/** Gets the last value that the API measured using the Ultrasonic Module
		@return distance (Centimeters) The most recent measurement the API have done
		*/
		virtual float getDistanceCentimeters();

		/** Gets the last value that the API measured using the US.
		@return distance (Inches) The most recent measurement the API have done
		*/
		float getDistanceInches();

		/** Updates the distance of the Ultrasonic Module to the objects in a blocking way.
		The new distance value is available using getDistanceCentimeters() or getDistanceInches() method after calling this method.
		@warning This method blocks while the measurement is on going, so the arduino waits 
		for the measure to be concluded, if you want a non block update distance method look for DistanceMeterNonBlock API
		*/
		virtual void updateDistance();

	protected:
		/** Execute a block distance measurement and calculates the distance based on the sound speed
		@param soundSpeed (Cm/Sec) Sound speed to introduce in the calculation
		@return distance (Centimeters) The new distance measured 
		*/
		float executeUpdateDistanceBlock(IN float soundSpeed);

	};

};


#endif
