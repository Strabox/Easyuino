/*
DistanceMeterExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::DistanceMeter;  // Necessary in order to use DistanceMeter API

int triggerPin = 7;  // Arduino pin that connects to Ultrasonic Module trigger pin
int echoPin = 2;	 // Arduino pin that connects to Ultrasonic Module echo pin			

DistanceMeter distanceMeter(triggerPin, echoPin);  // Create the DistanceMeter API object

void setup() {
	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	distanceMeter.begin();  // Initialize the DistanceMeter API
}

void loop() {
	/*
	- This call makes the Ultrasonic Module update its distance to the closer object.
	- To get the distance measure you need call getDistanceCentimeters(); or getDistanceInches();
	presented below.
	- Info: The Arduino will wait when you call this in order to let the Ultrasonic Module make the measurement.
	So the next instructions will only execute when the measurement is done. Measurement can take tens of miliseconds.
	*/
	distanceMeter.updateDistance();

	/*
	- This call will return the last distance measurement the Ultrasonic Module did.
	- The distance value will be in centimeters
	*/
	float distanceCentimeters = distanceMeter.getDistanceCentimeters();
	Serial.print("Centimeters: ");
	Serial.println(distanceCentimeters);

	/*
	- This call will return the last distance measurement the Ultrasonic Module did.
	- The distance value will be in inches.
	*/
	float distanceInches = distanceMeter.getDistanceInches();
	Serial.print("Inches: ");
	Serial.println(distanceInches);

	delay(300);
}