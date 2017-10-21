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
	#include "OLEDlcd.h"
	#include "SevenSegments.h"	

	#include "Relay.h"
	#include "RelayNamed.h"

	#include "DistanceMeter.h"
	#include "DistanceMeterPrintable.h"

	#include "RGBLed.h"
	#include "InfraRedReceiver.h"
	#include "RainDetector.h"
	#include "Utilities.h"
#endif

