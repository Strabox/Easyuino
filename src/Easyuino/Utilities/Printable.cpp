#include "../../Printable.h"

namespace Easyuino {

	Stream & operator<<(Stream & stream, const Printable & printable) {
		char *tempRes = printable.toString();
		stream.print(tempRes);
		free(tempRes);
		return stream;
	}

};
