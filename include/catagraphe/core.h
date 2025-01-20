#ifndef __CATAGRAPHE_H__
#define __CATAGRAPHE_H__
#include <type_traits>
#include <string>
#include <vector>
#include <span>
#include <catagraphe/date.h>

namespace ctgrph {

enum class Record_Level: size_t {
	Text = 0, Debug, Info, Warning, Error
};


struct Record {
	Record_Level lvl;
	Date date; 
	std::string text;
};


class Core {
public:
	using Storage = std::vector<Record>;

	struct Const_View {
		Storage::const_iterator _m_begin, _m_end;	

		Storage::const_iterator begin() const noexcept(true) {
			return _m_begin;
		}

		Storage::const_iterator end() const noexcept(true) {
			return _m_end;
		}
	};

	Core(const std::string &db_path, Record_Level default_lvl);

	void set_default_lvl(Record_Level lvl) noexcept(false);

	void create_record(Record_Level lvl, std::string text) noexcept(false);
	
	[[nodiscard("View to the rectords must be used!")]]
	Const_View get_last_records(void) const noexcept(false);
	
private:
	Storage _m_records;
	Record_Level _m_default_lvl;

	Core(Core&) = delete;
	Core(const Core&) = delete;
};


}
#endif
