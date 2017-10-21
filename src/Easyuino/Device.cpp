#include "Device.h"

namespace Easyuino {

	Device::Device() {
		_isInitialized = false;
	}

	Device::~Device() { /* Do Nothing */ }

	bool Device::isInitialized() const {
		return _isInitialized;
	}

};