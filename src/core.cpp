#include <catagraphe/core.h>
#include <algorithm>
#include <cstring>

namespace ctgrph {
	Bytes Record::serialize(void) const noexcept(true)
	{
		Bytes out (0);			

		Byte *lvl_b = (Byte*)&lvl;
		std::copy(lvl_b, lvl_b + sizeof(lvl),
			  std::back_inserter(out));

		auto date_b = date.serialize();
		std::copy(date_b.begin(), date_b.end(),
			  std::back_inserter(out));
		
		std::copy(text.begin(), text.end(),
			  std::back_inserter(out));
		
		out.push_back(0);

		return out;
	}

	void Record::deserialize(Const_Bytes_View &in) noexcept(false)
	{
	}


	Core::Core(const std::string &db_path, Record_Level default_lvl):
		_m_records(0), _m_default_lvl{ default_lvl }
	{
		
	}

	void
	Core::set_default_lvl(Record_Level lvl) noexcept(false)
	{
		_m_default_lvl = lvl;
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
