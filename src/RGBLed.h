/*
RGBLed.h
*/
#ifndef _EASYUINO_RGB_LED_h
#define _EASYUINO_RGB_LED_h

#include "Device.h"

namespace Easyuino {

	/* RGBLed API allows to easily interact with a RGB led to set its color for example */
	class RGBLed : public Device {
	
	public:

	/* Enum with the types of RGB physical leds */
	enum LED_TYPE {
		COMMON_ANODE,
		COMMON_CATODE
	};

	/* Enum with a set of pre defined colors that the RGBLed API knows how to write */
	enum COLOR {
		RED, GREEN, BLUE, YELLOW, WHITE, ORANGE, PINK, SALMON, VIOLET, AQUA, BROWN, FIREBRICK, DARKGREY, OLIVE,
		SKYBLUE
	};

	private:
		/* The type of the led defined by the enumerate LED_TYPE */
		LED_TYPE _ledType;

		/* The Arduino pin connected do led's red pin */
		uint8_t _redPin;
		/* The Arduino pin connected to led's green pin */
		uint8_t _greenPin;
		/* The Arduino pin connected to led's blue pin */
		uint8_t _bluePin;

	public:
		/* Makes a RGBLed object that exposes the API to interact with a COMMON CATODE RGB led
		@param redPin	- The Arduino pin connected do led's red pin
		@param greenPin - The Arduino pin connected to led's green pin
		@param bluePin	- The Arduino pin connected to led's blue pin
		*/
		RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

		/* Makes a RGBLed object that exposes the API 
		@param redPin	- The Arduino pin connected do led's red pin
		@param greenPin - The Arduino pin connected to led's green pin
		@param bluePin	- The Arduino pin connected to led's blue pin
		@param ledType	- The type of the LED's inners
		*/
		RGBLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, LED_TYPE ledType);

		/* Destroys a RGBLed object that exposes the API and frees the resources*/
		~RGBLed();

	#pragma region Public Device API Methods

		void begin();

		void end();

	#pragma endregion

	#pragma region Public RGBLed API Methods 

		/* Led emits no light when turned off. It can be lit again using setColor methods. */
		void turnOff();

		/* Set the led's color based on the RGB coded 
		@param red		- Red value		(0-255)	
		@param green	- Green value	(0-255)
		@param blue		- Blue value	(0-255)
		*/
		void setColor(uint8_t red, uint8_t green, uint8_t blue);

		/* Set the led's color based on the hexadecimal color code used in web context
		@param hexadecimalCode - String that represents a valid hexadecimal color code (e.g: "#ffffff" to red color)
		*/
		void setColor(char hexadecimalColoCode[8]);

		/* Set the led's color based in a set o pre defined colors
		@param color - Enum value that represents the wanted color
		*/
		void setColor(COLOR color);

	#pragma endregion

	};

};

#endif
