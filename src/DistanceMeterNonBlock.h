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

#include "DistanceMeter.h"

#define MAXIMUM_NUMBER_OF_DM_NON_BLOCK 2	//	WARNING: DON'T change it because it will broke the API

namespace Easyuino {

	/*
	DistanceMeterNonBlock offers an API to interact with an Ultrasonic Sensor (US) to measure distance to objects using sound waves.
	It offers a the same as DistanceMeter API plus updateDistanceNonBlock that allows your application code run while
	the distance is calculated in "background" without stopping your program.
	WARNING: You can ONLY use TWO instances of DistanceMeterNonBlock per sketch due to implementation restrictions.
	So if you want have multiple distance meters you can at maximum TWO DistanceMeterNonBlock and several DistanceMeter.
	@Limitations: 
		- This only allows ONLY 2 instances of DistanceMeterNonBlock per sketch!!!
		- The accuracy of the non-block method is much smaller because it uses interruption mechanism
	@Physical Devices Supported: 
		- HC-SR03, HC-SR04, HC-SR05
	@Physical Devices Tested: 
		- HC-SR04
	*/
	class DistanceMeterNonBlock : public DistanceMeter {

	private:
		/* Necessary to have a static object to allow attach interrupts to specific object methods. */
		static DistanceMeterNonBlock* INSTANCES[MAXIMUM_NUMBER_OF_DM_NON_BLOCK];

		/* Used to know if it is a blocking/non-blocking measure that is ocurring */
		bool _blockingMeasure;

		/* It says if the distance stored has a new value due to an non-blocking measure that occured in background */
		bool _isDirtyDistance;
		
		/* Last time a non-block measure was concluded (only used in non-block measure) */
		volatile unsigned long _lastTimeEcho;
		/* Last time a non-block measure was triggered (only used in non-block measure) */
		volatile unsigned long _lastTimeTrigger;

		/* Used to know if the echo wave was already fully sent this is set to true when US put the
		echo pin at HIGH level (only used in non-block measure) */
		volatile bool _echoSent;

	public:
		DistanceMeterNonBlock(uint8_t triggerPin, uint8_t echoPin);

		DistanceMeterNonBlock(uint8_t triggerEchoPin);

		~DistanceMeterNonBlock();

		bool begin();

		void end();

		float getDistanceCentimeters();

		void updateDistance();

		/* 
		Updates the distance of the US to the objects in a non-blocking way. It means that the call to the method
		will return immediatly and in the "background" the distance measure will ocurr after a while. 
		Depending on the distance to the object the getDistance methods can be called to get the new distance value.
		@return - True: If the distance measure started. False: Otherwise.
		*/
		virtual void updateDistanceNonBlock();

	protected:

		/*
		Execute a non-block distance measure
		*/
		void executeUpdateDistanceNonBlock();

		/*
		Verify if there is a non-block measure on going that has already timeouted
		@return - True: If it timeout. False: Otherwise.
		*/
		bool isUpdateDistanceNonBlockTimeout();

		/*
		Calculates the distance to the object based on the sound speed in air using the last distance value measured!
		@param soundSpeedCmPerSec (cm/sec)	- The sound speed to be taken in account.
		@return	distance (Centimeters)		- The distance to the object.
		*/
		float calculateDistance(float soundSpeedCmPerSec);

	private:
	#pragma region Interrupt Management/Handling Methods
		/* Interrupt handler of the DistanceMeterNonBlock instance that is in charge of the measurement */
		void interruptHandler(unsigned long interruptCallTimeMicros);

		/* Assign a new DistanceMeterNonBlock instance to an available spot */
		static void assignInstance(DistanceMeterNonBlock* dm);

		/* Delete the DistanceMeterNonBlock instance from the available spot */
		static void deleteInstance(DistanceMeterNonBlock* dm);

		/* Attach the interrupt interruptCaller function to the right instance object */
		static void attachInterruptToInstance(DistanceMeterNonBlock* dm);

		/* Necessary to redirect the interrupt to the specific DistanceMeterNonBlock instance */
		static void interruptCaller0();
		static void interruptCaller1();

	#pragma endregion

	};

};

#endif
