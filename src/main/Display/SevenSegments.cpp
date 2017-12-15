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
#include "../../SevenSegments.h"

/** Number of 7 segments we have */
#define NUM_OF_7_SEGMENTS 4
/** 7 segments light brigthness [0-7] */
#define DEFAULT_BRIGHTNESS 4

/** Used to initialize the display */
#define INITIALIZE_MASK 136
/** Used to terminate the display */
#define TERMINATE_MASK 128
/** */
#define MINUS_SIGNAL_7_BIT_ENCODING 64
/** */
#define DEACTIVATED_SEGMENT_7_BIT_ENCODING 0

namespace Easyuino {

	/** 7-Segments 7-bits encoding.
	SGFEDCBA = 1 Byte
		 __A__
		|	  |
	   F|     |B
		|__G__|
		|     |
	   E|     |C
		|__D__|	  [S]
	*/

	/** Digits form [0-9] encoded in 7-bits encoding. */
	static const uint8_t PROGMEM digits7BitEncoding[10] {
		63,		// 0
		6,		// 1
		91,		// 2
		79,		// 3
		102,	// 4
		109,	// 5
		125,	// 6
		7,		// 7
		127,	// 8
		111		// 9
	};

	/** Characters form [A-Z] encoded in 7-bits encoding. */
	static const char PROGMEM characters7BitEncoding[26] {
		119,	//A
		127,	//B
		57,		//C
		63,		//D
		121,	//E
		113,	//F
		125,	//G
		118,	//H
		6,		//I
		31,		//J
		121,	//K
		56,		//L
		55,		//M
		116,	//n
		63,		//O
		115,	//P
		103,	//q
		119,	//R
		109,	//S
		7,		//T
		62,		//U
		62,		//V
		1,		//W
		118,	//X
		102,	//Y
		91		//Z
	};

	SevenSegments::SevenSegments(IN uint8_t clkPin, IN uint8_t dataPin) : Device() {
		_clkPin = clkPin;
		_dataPin = dataPin;
	}

	SevenSegments::~SevenSegments() { /* Do Nothing */}

	bool SevenSegments::begin() {
		return begin(DEFAULT_BRIGHTNESS);
	}

	bool SevenSegments::begin(IN uint8_t brightness) {
		if (!_isInitialized) {
			pinMode(_clkPin, OUTPUT);
			pinMode(_dataPin, OUTPUT);
			start();
			sendByte(INITIALIZE_MASK|brightness);
			stop();
			_isInitialized = true;
		}
		return _isInitialized;
	}

	void SevenSegments::end() {
		if (_isInitialized) {
			start();
			sendByte(TERMINATE_MASK);
			stop();
			_isInitialized = false;
		}
	}

	void SevenSegments::setBrightness(IN uint8_t brightness) {
		if (brightness <= 7) {
			start();
			sendByte(INITIALIZE_MASK|brightness);
			stop();
		}
	}

	void SevenSegments::print(IN uint8_t digit, IN uint8_t position) {
		if (position >= 0 && position < NUM_OF_7_SEGMENTS && digit >= 0 && digit <= 9) {
			start();
			sendByte(0x44);
			stop();
			start();
			sendByte(0xC0|position);
			sendByte(pgm_read_word(digits7BitEncoding + digit));
			stop();
		}
	}

	void SevenSegments::print(IN unsigned int num) {
		uint8_t res[NUM_OF_7_SEGMENTS];
		start();
		sendByte(0x40);
		stop();
		start();
		sendByte(0xC0);
		for (int i = 0; i < NUM_OF_7_SEGMENTS; i++) {
			res[(NUM_OF_7_SEGMENTS - 1) - i] = pgm_read_word(digits7BitEncoding + (num % 10));
			num /= 10;
		}
		for (int i = 0; i < NUM_OF_7_SEGMENTS; i++) {
			sendByte(res[i]);
		}
		stop();
	}

	void SevenSegments::print(IN int num) {
		uint8_t res[NUM_OF_7_SEGMENTS];
		start();
		sendByte(0x40);
		stop();
		start();
		sendByte(0xC0);
		if (num >= 0) {
			for (int i = 0; i < NUM_OF_7_SEGMENTS; i++) {
				res[(NUM_OF_7_SEGMENTS - 1) - i] = pgm_read_word(digits7BitEncoding + (num % 10));
				num /= 10;
			}
			for (int i = 0; i < NUM_OF_7_SEGMENTS; i++) {
				sendByte(res[i]);
			}
		}
		else {
			for (int i = 0; i < NUM_OF_7_SEGMENTS - 1; i++) {
				res[(NUM_OF_7_SEGMENTS - 2) - i] = pgm_read_word(digits7BitEncoding + (-num % 10));
				num /= 10;
			}
			sendByte(MINUS_SIGNAL_7_BIT_ENCODING);	// Send minus signal
			for (int i = 0; i < NUM_OF_7_SEGMENTS - 1; i++) {
				sendByte(res[i]);
			}
		}
		stop();
	}

	void SevenSegments::print(IN const char* string) {
		unsigned int stringSize = strlen(string);
		int ctr;
		
		if (stringSize > NUM_OF_7_SEGMENTS) {
			stringSize = NUM_OF_7_SEGMENTS;
		}

		start();
		sendByte(0x40);
		stop();
		start();
		sendByte(0xC0);
		
		for (ctr = 0; ctr < stringSize; ctr++) {
			if (isalpha(string[ctr])) {
				char writableChar = toupper(string[ctr]);
				sendByte(pgm_read_word(characters7BitEncoding + (writableChar -'A')));
			}
			else if (isdigit(string[ctr])) {
				sendByte(pgm_read_word(digits7BitEncoding + (string[ctr] - '0')));
			}
		}

		while (ctr < NUM_OF_7_SEGMENTS) {
			sendByte(DEACTIVATED_SEGMENT_7_BIT_ENCODING);
			ctr++;
		}
		
		stop();
	}

	 
	void SevenSegments::sendByte(IN uint8_t byte) {
		for (uint8_t i = 0; i < 8; i++) {
			digitalWrite(_clkPin, LOW);
			microDelay();
			digitalWrite(_dataPin, (byte & (1 << i)) >> i);
			microDelay();
			digitalWrite(_clkPin, HIGH);
			microDelay();
		}
		// wait for ACK 
		digitalWrite(_clkPin, LOW);
		microDelay();

		pinMode(_dataPin, INPUT);

		digitalWrite(_clkPin, HIGH);
		microDelay();
		bool ack = digitalRead(_dataPin) == 0;
		pinMode(_dataPin, OUTPUT);
	}

	void SevenSegments::start() {	//send start signal
		digitalWrite(_clkPin, HIGH);
		digitalWrite(_dataPin, HIGH);
		microDelay();

		digitalWrite(_dataPin, LOW);
		digitalWrite(_clkPin, LOW);
		microDelay();
	}

	void SevenSegments::stop() {
		digitalWrite(_clkPin, LOW);
		digitalWrite(_dataPin, LOW);
		microDelay();

		digitalWrite(_clkPin, HIGH);
		digitalWrite(_dataPin, HIGH);
		microDelay();
	}

	void SevenSegments::microDelay() {
		delayMicroseconds(5);
	}

}
