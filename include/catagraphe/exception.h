#ifndef __CATAGRAPHE_EXCEPTION__
#define __CATAGRAPHE_EXCEPTION__

#include <stdexcept>

namespace ctgrph {
	class Exception: public std::runtime_error {
	public:
		Exception(std::string msg): std::runtime_error(msg) { }
	};

	class Date_Display_Exception: public Exception {
	public:
		Date_Display_Exception(std::string fmt, std::string msg):
			Exception("Failed to display date with fmt: `" + fmt +
				  "'. (" + msg + ")") { }
	};

	class Serde_Exception: public Exception {
	public:
		Serde_Exception(std::string type, std::string what):
			Exception("Serde error. Type: `" + type + "'. " + what) 
			{}
	};

	class Core_Init_Exception: public Exception {
	public:
		Core_Init_Exception(std::string what):
			Exception("[Failed to init core]: " + what) { }
	};
}

#endif
