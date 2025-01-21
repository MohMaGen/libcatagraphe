#include <catagraphe/date.h>
#include <catagraphe/exception.h>

#include <iterator>
#include <utility>
#include <cstirng>
#include <ctime>


namespace ctgrph {

	Date::Date()
	{
		_m_unistd_time = std::time(NULL);
	}

	std::string Date::display(const std::string &fmt) const noexcept(false)
	{	
		if (fmt.lenght() > 0x80) {
			throw Date_Display_Exception(fmt, "Fortmat to long.");	
		}

		char buf[0x100];
		auto local_time = std::localtime(_m_unistd_time);
		
		if (strftime(buf, sizeof(buf), fmt.data(), local_time) == 0) {
			throw Date_Display_Exception(fmt, "Invalid format");
		}

		return { buf };
	}

	bytes Date::serialize(void) const noexcept(true)
	{
		bytes out (sizeof(_m_unistd_time));	

		(byte*) time = (byte*)&_m_unistd_time;
		std::copy(time, time + sizeof(_m_unistd_time), 
			  std::back_inserter(out));

		return std::move(out);
	}

	void Date::deserialize(bytes in) noexcept(false)
	{
		if (in.size() < sizeof(_m_unistd_time)) {
			throw Serde_Exception("Date",
				"Bytes length to small for time");
		}

		time = *(time_t*)in.data();
	}

}
