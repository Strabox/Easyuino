/*
DistanceMeterAccurateExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::DistanceMeterAccurate;  // Necessary in order to use DistanceMeterAccurate API
using Easyuino::TemperatureScale;  // Necessary to use the Temperature Scale options

int triggerPin = 7;  // Arduino pin that connects to Ultrasonic Module trigger pin
int echoPin = 2;     // Arduino pin that connects to Ultrasonic Module echo pin	(it should be a pin that support external interruptions https://www.arduino.cc/en/Reference/AttachInterrupt)		
float currentAirTemperature = 26.7f;  // The current air temperature to be considered when measuring the distance

DistanceMeterAccurate distanceMeterACC(triggerPin, echoPin);  // Create the DistanceMeterAccurate API object

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

  distanceMeterACC.begin();  // Initialize the DistanceMeterNonBlock API
}

/*
- This API is an extension to DistanceMeterNonBlock API. You can do the sam as DistanceMeterNonBlock plus the following calls.
*/
void loop() {
  /*
  - This call does the same as updateDistanceNonBlock() in the DistanceMeterNonBlockExample.ino
  - The difference is that we can provide the measurement with the current air temperature.
  Why??? Well because the temperature can change a lot around the world and even during the day, which
  affects the sound speed in the air that is used to calculate the distance. 
  See https://en.wikipedia.org/wiki/Speed_of_sound if you have curiosity.
  - The first parameter is the air temperature (If the argument is not provided the
  default temperature used to calculate the sound speed is 20.0 Celsius)
  - The second parameter is the temperature scale which can be KELVIN, CELSIUS or FAHRENHEIT
  (If the argument is not provided the API consider CELSIUS, sorry American users I like you too :) )
  */
  distanceMeterACC.updateDistanceNonBlock(currentAirTemperature, TemperatureScale::CELSIUS);

  /*
  See DistanceMeterExample.ino for the explanation
  */
  float distanceCentimeters = distanceMeterACC.getDistanceCentimeters();
  Serial.println(distanceCentimeters);

  delay(300);
}