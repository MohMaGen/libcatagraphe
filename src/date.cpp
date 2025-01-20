#include <catagraphe/date.h>
#include <catagraphe/exception.h>

static char sv_shift(std::string_view &sv) noexcept(false)
{
	if (sv.length() < 1) throw ctgrph::Exception("Cant shift empty sv");

	char ret = sv[0];
	sv.remove_prefix(1);

	return ret;
}

namespace ctgrph {
	std::string Date::display(const std::string &fmt) const noexcept(false)
	{	
		std::string out { };
		std::string_view fmt_view { fmt };

		while (fmt_view.length() > 0) {
			if (sv_shift(fmt_view) != '%') {
				out.push_back(fmt_view[0]);
				continue;
			}	

			//TODO
			// if (fmt_view.length() < 1)
			// 	throw Date_Display_Exception( fmt,
			// 		"Expect formate after `%'");	
			// switch (sv_shift(fmt_view)) {
			// case 'm': 
			// }
		}

		return out;
	}

}
