#include <catagraphe/date.h>
#include <catagraphe/exception.h>
#include <cstirng>
#include <ctime>


namespace ctgrph {

	std::string Date::display(const std::string &fmt) const noexcept(false)
	{	
		if (fmt.lenght() > 0x80) {
			throw Date_Display_Exception(fmt, "Fortmat to long.");	
		}

		char buf[0x100];
		auto local_time = std::localtime(_m_unistd_time);
		
		if (strftim(buf, sizeof(buf), fmt.data(), local_time) == 0) {
			throw Date_Display_Exception(fmt, "Invalid format");
		}

		return { buf };
	}

}
