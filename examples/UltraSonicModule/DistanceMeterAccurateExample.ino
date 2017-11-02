/*
DistanceMeterAccurateExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::DistanceMeterAccurate;  // Necessary in order to use DistanceMeterAccurate API
using Easyuino::TemperatureScale;  // Necessary to use the Temperature Scale options

int triggerPin = 7;  // Arduino pin that connects to Ultrasonic Module trigger pin
int echoPin = 2;     // Arduino pin that connects to Ultrasonic Module echo pin			

DistanceMeterAccurate distanceMeterACC(triggerPin, echoPin);  // Create the DistanceMeterAccurate API object

void setup() {
  Serial.begin(57600);
  distanceMeterACC.begin();  // Initialize the DistanceMeterNonBlock API
}

/*
- Information: You can do the same calls of the DistanceMeterNonBlock API
see DistanceMeterNonBlockExample.ino plus the following ones
*/
void loop() {
  /*
  - This call does the same as updateDistanceNonBlock(); in the DistanceMeterNonBlockExample.ino
  - The litte difference is that we can provide the measurement with the current air temperature.
  Why??? Well because the temperature can change a lot around the world and even during the day which
  affects the sound speed in the air that is used to calculate the distance. 
  See https://en.wikipedia.org/wiki/Speed_of_sound if you have curiosity.
  - The first parameter is the air temperature (If the argument is not provided the
  default temperature used to calculate the sound speed is 20.0 Celsius)
  - The second parameter is the temperature scale which can be KELVIN, CELSIUS or FAHRENHEIT
  (If the argument is not provided the API consider CELSIUS, sorry American users I like you too :) )
  */
  distanceMeterACC.updateDistanceNonBlock(26.7, TemperatureScale::CELSIUS);

  /*
  See DistanceMeterExample.ino for the explanation
  */
  float distanceCentimeters = distanceMeterACC.getDistanceCentimeters();
  Serial.println(distanceCentimeters);

  delay(500);
}