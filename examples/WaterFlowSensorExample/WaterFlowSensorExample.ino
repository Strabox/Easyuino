/*
WaterFlowSensorExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::WaterFlowSensor; // Necessary in order to use WaterFlowSensor API

int sensorPin = 2;  // Arduino pin connected to the sensor pin (it should be a pin that support external interruptions https://www.arduino.cc/en/Reference/AttachInterrupt)

WaterFlowSensor waterFlowSensor(sensorPin);  // Creates the WaterFlowSensor object API

void setup() {
	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	/*
	- Initializes the WaterFlowSensor API.
	*/
	waterFlowSensor.begin();
}

void loop() {
	/*
	- This API call returns true if it is flowing something through the sensor and false otherwise.
	*/
	bool isFlowing = waterFlowSensor.isFlowing();

	if (isFlowing) {
		Serial.println(F("Flowing!!"));
	}
	else {
		Serial.println(F("Idle"));
	}
}