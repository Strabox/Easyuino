/*
WaterFlowMeterExample.ino
*/

#include <Easyuino.h>  // Include the library in order to the compiler know you want Easyuino library

using Easyuino::WaterFlowMeter; // Necessary in order to use WaterFlowSensor API

int sensorPin = 2;  // Arduino pin connected to the sensor pin (it should be a pin that support external interruptions https://www.arduino.cc/en/Reference/AttachInterrupt)
float sensorCalibrationFactor = 0.2f; // This calibration factor depends on the sensors (see the images to check where it is written in sensors)

WaterFlowMeter waterFlowMeter(sensorPin, sensorCalibrationFactor);  // Creates the WaterFlowMeter object API

void setup() {
	Serial.begin(9600);
	while (!Serial);  // Necessary for Arduino Leonardo serial monitor use

	/*
	- Initializes the WaterFlowMeter API.
	*/
	waterFlowMeter.begin();
}

/*
- Attention: The WaterFlowMeter API is and extension of the WaterFlowSensor API in
other other words it can do the same and more. Here we only present the extended calls.
*/
void loop() {
	/*
	- Obtains the current flow rate in Liters/Min.
	*/
	float flowingRate = waterFlowMeter.getFlowRateLitersMin();

	Serial.print(F("Rate: "));
	Serial.println(flowingRate);

	delay(100);
}