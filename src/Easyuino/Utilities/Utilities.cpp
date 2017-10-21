#include "../../Utilities.h"

#define EXTRA_SAFE_BYTES_MALLOC 1

namespace Easyuino {

	void* Utilities::EasyMalloc(unsigned int sizeInBytes) {
		void* resPtr = NULL;
		resPtr = (void*)malloc(sizeInBytes + EXTRA_SAFE_BYTES_MALLOC);
		if (resPtr == NULL) {
			return NULL;
		}
		else {
			memset(resPtr, NULL, sizeInBytes + EXTRA_SAFE_BYTES_MALLOC);
			return resPtr;
		}
	}

}