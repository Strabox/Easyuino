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

#include "Device.h"

namespace Easyuino {

	/*
	DistanceMeter offers an API to interact with an Ultrasonic Sensor (US) to measure distance to objects.
	It offers a block and non-block way to measure the distance to the objects.
	*/
	class DistanceMeter : public Device {

	private:
		/* Trigger pin used to trigger the echo wave emission in the US */
		uint8_t _triggerPin;
		/* Pin that is set to low by US when emitted echo wave arrives */
		uint8_t _echoPin;
		/* Used to know if it is a blocking/non-blocking measure that is ocurring*/
		bool _blockingMeasure;

		/* Counter that stores the time when the echo wave was set (only in non-block measure) */
		volatile unsigned long _timeTrigger;
		/* Used to know if it is in a middle of a distance measure (only in non-block measure) */
		volatile bool _isEchoing;
		/* Used to know if the echo wave was already fully sent this is set to true whe US put the 
		echo pin at HIGH level (only in non-block measure) */
		volatile bool _echoSent;

		/* It says if the distance stored has a new value due to an non-blocking measure */
		bool _isDirtyDistance;
	protected: 
		/* It contains a cached value of the distance to the object */
		volatile float _distance;

	private:
		/* Last time a non-block measure was triggered */
		volatile unsigned long _lastTimeTrigger;
		/* Last time a non-block measure was concluded */
		volatile unsigned long _lastTimeEcho;

		/* Necessary to have a static object to allow attach interrupts to specific object methods.
		This only allows a single instance of DistanceMeter per sketch.*/
		static DistanceMeter* singleton;

	public:
		DistanceMeter(uint8_t triggerPin, uint8_t echoPin);

		~DistanceMeter();

	#pragma region Public Device API Methods

		void begin();

		void end();

	#pragma endregion 

	#pragma region Public DistanceMeter API Methods

		/* Updates the distance of the US to the objects in a non-blocking way. It means that the call to the method
		will return immediatly and in the "background" the distance measure will ocurr after a while depeding on the distance
		to the object the getDistance method can be called to get the new distance value.
		*/
		void updateDistanceNonBlock();

		/* Updates the distance of the US to the objects in a blocking way. Basically if updateDistanceNonBlock
		was not called in the last 3 secs at least the method will block on call and when it finishes the distance
		value can be grabbed by getDistance method. */
		void updateDistanceBlock();

		/* Gets the last value that the API measured using the US device.
		@return distance - This value will always be the the most updated valued that the API have.
		*/
		float getDistance();

	#pragma endregion 

	private:

		void interruptHandler();

		static void InterruptCaller();

	};

};


#endif
