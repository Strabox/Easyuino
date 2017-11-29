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
DistanceMeterNonBlock.h
*/
#ifndef _EASYUINO_DISTANCE_METER_NON_BLOCK_h
#define _EASYUINO_DISTANCE_METER_NON_BLOCK_h

#include "Utilities.h"
#include "DistanceMeter.h"

/** ATTENTION: DON'T change it because it will broke the API due to the compiled link between
interruption functions and the instances */
#define MAXIMUM_NUMBER_OF_DM_NON_BLOCK 2

namespace Easyuino {

	/** DistanceMeterNonBlock offers an API to interact with an Ultrasonic Module to measure distance in a non-block way.
	It offers a the same as DistanceMeter API plus updateDistanceNonBlock() that allows your application code run while
	the distance is calculated in "background" without stopping your program.
	@see Limitation:		This allows ONLY 2 instances of DistanceMeterNonBlock per sketch!!
	@see Limitation:		The accuracy of the non-block method is much smaller because it uses interruption mechanism
	@see Devices Supported:	HC-SR03, HC-SR04, HC-SR05
	@see Devices Tested:	HC-SR04
	*/
	class DistanceMeterNonBlock : public DistanceMeter {

	private:
		/** Necessary to have a static object to allow attach interrupts to specific object methods */
		static DistanceMeterNonBlock* INSTANCES[MAXIMUM_NUMBER_OF_DM_NON_BLOCK];

		/** Used to know if it is a blocking/non-blocking measure that is ocurring */
		bool _blockingMeasure;

		/** Distance stored has a new value due to an non-blocking measure that occured in background. 
		The distance is indirectly measured in _lastTimeEcho and _lastTimeTrigger */
		bool _isDirtyDistance;

		/** Used to know if the echo wave was already sent this is set to true when Ultrasonic Module 
		put the echo pin at HIGH level (only used in non-block measure) */
		volatile bool _echoSent;

		/** Last time a non-block measure was triggered (only used in non-block measure) */
		volatile unsigned long _lastTimeTrigger;
		/** Last time a non-block measure was concluded (only used in non-block measure) */
		volatile unsigned long _lastTimeEcho;

	public:
		/** Constructor
		@param triggerPin	Arduino pin connected to the trigger pin of the Ultrasonic Module
		@param echoPin		Arduino pin connected to the echo pin of the Ultrasonic Module
		*/
		DistanceMeterNonBlock(IN uint8_t triggerPin, IN uint8_t echoPin);

		/** Contructor used with Ultrasonic Modules that have only one pin for trigger and echo 
		@param triggerEchoPin	Arduino pin connected to the trigger&echo pin of the Ultrasonic Module
		*/
		DistanceMeterNonBlock(IN uint8_t triggerEchoPin);

		/** Destructor */
		~DistanceMeterNonBlock();

		bool begin();

		void end();

		float getDistanceCentimeters();

		void updateDistance();

		/** Updates the distance of the Ultrasonic Module to the objects in a non-blocking way. This means that
		the call to the method will return immediatly and in the "background" the distance measure will ocurr after a while. 
		When the measurement is concluded and you call getDistanceCentimeters() or getDistanceInches() the new distance value
		will be returned. While the measurement is on going the distance will be from the last measurement.
		*/
		virtual void updateDistanceNonBlock();

	protected:

		/** Execute a non-block distance measurement */
		void executeUpdateDistanceNonBlock();

		/** Verify if there is a non-block measuremenet on going that has already timeouted
		@return True: If it timeout. False: Otherwise.
		*/
		bool isUpdateDistanceNonBlockTimeout();

		/** Calculates the distance to the object based on the sound speed in air using the last distance value measured!
		@param soundSpeedCmPerSec (Cm/Sec)	The sound speed to be taken in account during the calculation
		@return	distance (Centimeters)		The new calculated distance
		*/
		float calculateDistance(IN float soundSpeedCmPerSec);

	private:
	#pragma region Interrupt Management/Handling Methods
		/** Interrupt handler of the DistanceMeterNonBlock instance that is in charge of the measurement */
		void interruptHandler(IN unsigned long interruptCallTimeMicros);

		/** Assign a new DistanceMeterNonBlock instance to an available spot */
		static void assignInstance(IN DistanceMeterNonBlock* dm);

		/** Delete the DistanceMeterNonBlock instance from the available spot */
		static void deleteInstance(IN DistanceMeterNonBlock* dm);

		/** Attach the interrupt interruptCaller function to the right instance object */
		static void attachInterruptToInstance(IN DistanceMeterNonBlock* dm);

		/** Necessary to redirect the interrupt to the specific DistanceMeterNonBlock instance */
		static void interruptCaller0();
		static void interruptCaller1();

	#pragma endregion

	};

};

#endif
