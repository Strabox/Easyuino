/*
Device.h
*/

#ifndef _EASYUINO_DEVICE_h
#define _EASYUINO_DEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

namespace Easyuino {

	/*
	General class that provides the common API and behaviour for the majority of peripheric/sensors for Arduino
	*/
	class Device {

	protected:
		/* Used to know if the peripherical is initialized and ready to receive requests */
		bool _isInitialized;

	public:
		/* Constructor called by every sub-classes */
		Device();

		/* Destroy all the resources associated with the device (IF EXISTS) */
		~Device();

	#pragma region Public Virtual Common API Methods

		/* Used to put the peripherical ready to receive requests. Normally this have some default behaviour some
		devices have other API method with same name that receives other arguments to a better customization. */
		virtual void begin() = 0;

		/* Used to stop the device. After this the peripherical will not process API requests. */
		virtual void end() = 0;

	#pragma endregion


	#pragma region Public Common API Methods

		/*
		Verify is the periphetical is initialized and ready to use.
		@return	- True: If peripherical is initialzed. False: Otherwise.
		*/
		bool isInitialized() const;

	#pragma endregion

	};

};

#endif
