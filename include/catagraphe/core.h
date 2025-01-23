#ifndef __CATAGRAPHE_H__
#define __CATAGRAPHE_H__
#include <type_traits>
#include <string>
#include <vector>
#include <span>

#include <catagraphe/serde.h>
#include <catagraphe/date.h>

namespace ctgrph {

	enum class Record_Level: Byte {
		Text = 0, Debug, Info, Warning, Error
	};


	class Record: public I_Serializible, public I_Deserializible {
	public:
		Record_Level lvl;
		Date date; 
		std::string text;

		Record() { }
		Record(Record_Level lvl, Date date, const std::string &text):
			lvl(lvl), date(date), text(text) { }

		virtual Bytes serialize(void) const noexcept(true) override;
		virtual void
		deserialize(Const_Bytes_View&) noexcept(false) override;
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

		Core(Record_Level default_lvl);
		void init(const std::string &db_path) noexcept(false);
		void init(const Bytes&) noexcept(false);

		void set_default_lvl(Record_Level lvl) noexcept(true);

		void create_record(Record_Level lvl, const std::string &text)
			noexcept(false);
		
		[[nodiscard("View to the rectords must be used!")]]
		Const_View get_records(void) const noexcept(false);
		
	private:
		Storage _m_records;
		Record_Level _m_default_lvl;

		Core(Core&) = delete;
		Core(const Core&) = delete;
	};


}
#endif
