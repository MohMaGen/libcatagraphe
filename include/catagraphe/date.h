#ifndef __CATAGRAPHE_DATE__
#define __CATAGRAPHE_DATE__
#include <cstddef>
#include <string>


namespace ctgrph {
	class Date {
		size_t _m_unistd_time; 
	public:
		Date();

		[[nodiscard("Displayed date must be used!")]]
		std::string
		display(const std::string &fmt) const noexcept(false);
	};
}


#endif
