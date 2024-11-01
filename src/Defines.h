#ifndef OSFLIB_DEFINES_H
#define OSFLIB_DEFINES_H

namespace osflib {

	typedef unsigned int Id;
	
	#define EmptyId 0
	
	enum Results {
		Success = 0,
		Error,
		QuantityOverflow,
		NotFound,
		OutOfBounds
	};
}

#endif