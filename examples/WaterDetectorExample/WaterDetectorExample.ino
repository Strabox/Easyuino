/*
WaterDetectorExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::WaterDetector; // Necessary in order to use WaterDetector
using Easyuino::WaterStatus;   // Necessary for some methods calls

int digitalPin = 7;  // Arduino pin that connects to the digital pin of the sensor (normally called D0)
int analogPin = 6;   // Arduino pin that conencts to the analog pin of the sensor (normally called A0)

WaterDetector waterDetector(digitalPin, analogPin);  // Create the WaterDetector object that exposes the API to use

void setup() {
	/*
	Initialize the serial monitor
	*/
	Serial.begin(9600);
	/*
	- Initialize the WaterDetector API
	- The first parameter is the digital level (HIGH or LOW) that appear in the digital pin when 
	the water touches the sensor and the amount of it is above the pre-defined threshold set by the
	potentiometer of the board. This is necessary because some sensor versions use HIGH others LOW.
	*/
	waterDetector.begin(LOW);  // Equivalent to: waterDetector.begin(); which is the common configuration
}

void loop() {
	/*
	This API call will return true when water is detected in the sensor and false otherwise.
	*/
	bool res = waterDetector.isWaterDetected();
	Serial.println(res);

	delay(2000);

	/*
	This API call will return a set of results (see C++ enumerates) that you can compare to see
	how much water is touching the sensor.
	WARNING: This reading is independent from the above one because the above one is controlled by
	the physical potentiometer and digital pin of the sensor. On the other hand the 
	getWaterStatus uses the analog pin to decide how "wet" :) the sensor is.
	*/
	WaterStatus status = waterDetector.getWaterStatus();
	
	if (status == WaterStatus::DRY) {
		Serial.println("Sensor is dry!");
	}
	else if (status == WaterStatus::FEW_DROPS) {
		Serial.println("Sensor has a few drops in it!");
	}
	else if (status == WaterStatus::WET) {
		Serial.println("Sensor is wet!");
	}
	else if (status == WaterStatus::FLOOD) {
		Serial.println("Sensor is flooded!");
	}
	else if (status == WaterStatus::INVALID) {
		Serial.println("Sensor had a strange invalid reading!");
	}
	else {
		Serial.println("Begin method was not called!");
	}

	delay(2000);

	/*
	This API call is more advanced basically it gives you a number from [0,1023] to describe how "wet"
	:) the sensor is. 1023 is when the sensor is completely dry and 0 when is completely flooded.
	Note: The method getWaterStatus is based on this call.
	*/
	unsigned int howWet = waterDetector.getWaterStatusRange();
	Serial.println(howWet);

	delay(2000);

	/*
	This API call will terminate the sensing ability of the water detector and all the requests
	after this one will be invalid. If you want use the sensor again you must call the begin
	method again.
	*/
	waterDetector.end();
}