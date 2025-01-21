#include <catagraphe/core.h>
#include <cstring>

namespace ctgrph {

	Core::Core(const std::string &db_path, Record_Level default_lvl)
	{
		
	}

	void
	Core::set_default_lvl(Record_Level lvl) noexcept(false)
	{
	}

	void
	Core::create_record(Record_Level lvl, std::string text) noexcept(false)
	{
	}
		
	Core::Const_View
	Core::get_last_records(void) const noexcept(false) {
		return Const_View { _m_records.cbegin(), _m_records.cend() };
	}
	
}
