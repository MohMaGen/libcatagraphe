#ifndef __CATAGRAPHE_H__
#define __CATAGRAPHE_H__
#include <type_traits>
#include <string>
#include <vector>
#include <span>

#include <catagraphe/exception.h>
#include <catagraphe/serde.h>
#include <catagraphe/date.h>


namespace ctgrph {

	/**
	 *     Record Level
	 * --------------------
	 * Enumeration describing different levels of records.
	 * The lesser value of enum the lesser important record level is.
	 * 
	 * If level of record is lesser than current default level than
	 * record would not be saved.
	 *
	 * This enum is sized to one byte.
	 */
	enum class Record_Level: Byte {
		Text = 0, Debug, Info, Warning, Error,
	};

	Record_Level level_of_string(const std::string &string);	

	/**
	 *     Recod
	 * -------------
	 * Struct represening single record (message) in the journal.
	 * 
	 * Records have 3 public fileds: `lvl', `date', and `text'.
	 * 	- `lvl'   --- level of the current record. Serialized as 
	 *		   one byte. 
	 *	- `date'  --- date at this recod was created. Serialized as
	 *	           8 bytes (unsigned long long). Serialized value equal
	 *	           to get_time() value.
	 *	- `text'  --- the message of record. Serialized as array of
	 *		   characters ened with null character ('\0').
	 *
	 * Records inherit interfaces `I_Serializible' and `I_Deserializible'
	 * from `catagraphe/serde.h', so record can be serialized and
	 * deserialized.
	 */
	class Record: public I_Serializible, public I_Deserializible {
	public:
		Record_Level lvl; 	// level of the record.
		Date date;		// date at this recod was created .
		std::string text;	// message of record.

		Record() { }

		/**
		 * Create record from value of it's fields.
		 */
		Record(Record_Level lvl, Date date, const std::string &text):
			lvl(lvl), date(date), text(text) { }

		/**
		 * Create record with date value equal current date.
		 */
		Record(Record_Level lvl, const std::string &text):
			lvl(lvl), date(), text(text) { }

		

		virtual Bytes serialize(void) const noexcept(true) override;
		virtual void
		deserialize(Const_Bytes_View&) noexcept(false) override;
	};


	/**
	 *     Core
	 * ____________
	 */
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

		void save(const std::string &db_path) const noexcept(false);
		Bytes save(void) const noexcept(true);

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
