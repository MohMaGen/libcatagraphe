#include <catagraphe/date.h>
#include <catagraphe/exception.h>
#include <iterator>
#include <utility>
#include <cstring>
#include <ctime>


namespace ctgrph {

	Date::Date()
	{
		_m_unistd_time = std::time(NULL);
	}

	std::string Date::display(const std::string &fmt) const noexcept(false)
	{	
		if (fmt.length() > 0x80) {
			throw Date_Display_Exception(fmt, "Fortmat to long.");	
		}

		char buf[0x100];
		auto local_time = std::localtime(&_m_unistd_time);
		
		if (strftime(buf, sizeof(buf), fmt.data(), local_time) == 0) {
			throw Date_Display_Exception(fmt, "Invalid format");
		}

		return { buf };
	}

	Bytes Date::serialize(void) const noexcept(true)
	{
		Bytes out (0);	

		Byte* time = (Byte*)&_m_unistd_time;
		std::copy(time, time + sizeof(_m_unistd_time), 
			  std::back_inserter(out));

		return out;
	}

	void Date::deserialize(Const_Bytes_View &in) noexcept(false)
	{
		auto view = in.shift(sizeof(_m_unistd_time));

		_m_unistd_time = *(time_t*)view.begin().base();
	}

}
