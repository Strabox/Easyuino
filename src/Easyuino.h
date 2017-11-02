﻿/*
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
 Name:		Easyuino.h
 Created:	10/13/2017 12:40:16 AM
 Author:	André
 Editor:	http://www.visualmicro.com
*/

#ifndef _EASYUINO_h
#define _EASYUINO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
	#include "GSMService.h"	
	#include "SMS.h"
	
	#include "Relay.h"
	#include "RelayNamed.h"

	#include "DistanceMeter.h"
	#include "DistanceMeterNonBlock.h"
	#include "DistanceMeterAccurate.h"
	#include "DistanceMeterPrintable.h"

	#include "RGBLed.h"
	#include "WaterDetector.h"

	#include "Utilities.h"
#endif

