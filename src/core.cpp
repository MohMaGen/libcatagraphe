#include <catagraphe/exception.h>
#include <catagraphe/core.h>
#include <algorithm>
#include <fstream>
#include <cstring>

namespace ctgrph {

	Record_Level level_of_string(const std::string &string) {
		if (string == "Text")
			return Record_Level::Text;

		if (string == "Debug")
			return Record_Level::Debug;

		if (string == "Info")
			return Record_Level::Info;

		if (string == "Warning")
			return Record_Level::Warning;

		if (string == "Error")
			return Record_Level::Error;

		throw Exception("[Level of String] failed to parse level");
	}

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
		auto lvl_b = in.shift(sizeof(lvl));
		lvl = *(Record_Level*)lvl_b.begin().base();

		date.deserialize(in);

		text = std::string { };
		Const_Bytes_View text_b { };
		while (*(text_b = in.shift(sizeof(char))).begin() != 0) {
			text.push_back(*text_b.begin());
		}
	}


	Core::Core(Record_Level default_lvl):
		_m_records(0), _m_default_lvl{ default_lvl } { }

	void Core::init(const std::string &db_path) noexcept(false)
	{
		Bytes bytes { };	
		bytes.read_file(db_path);

		init(bytes);
	}

	void Core::init(const Bytes &bytes) noexcept(false)
	{
		Const_Bytes_View view { bytes };

		while (view.len() > 0) {
			Record record { };

			try { 
				record.deserialize(view);
			} catch (std::exception &e) {
				throw Core_Init_Exception(e.what());
			}	

			_m_records.push_back(record);

			try {
				Byte b = view.shift(1).begin()[0];
				if (b != (Byte)0xA)
				throw Serde_Exception("Core",
					"expect new line after record, but get"
					+ std::to_string((char)b));

			} catch (std::exception &e) { }
		}	
	}

	void Core::save(const std::string &db_path) const noexcept(false)
	{
		Bytes res = save();

		std::ofstream file (db_path, std::ios::binary);
		file.write((const char*)res.begin().base(), res.len());
	}

	Bytes Core::save(void) const noexcept(true)
	{
		Bytes out { };

		for (auto record: _m_records) {
			auto bytes = record.serialize();

			std::copy(bytes.begin(), bytes.end(),
				  back_inserter(out));

			out.push_back((Byte)0x0A); // new line
		}

		return out;
	}

	void Core::set_default_lvl(Record_Level lvl) noexcept(true) {
		_m_default_lvl = lvl;
	}

	void Core::create_record(Record_Level lvl, const std::string &text)
		noexcept(false)
	{
		if ((size_t)lvl < (size_t)_m_default_lvl) return;

		if (text.length() == 0)
			throw Exception("Can't create empty record!");

		_m_records.push_back(Record(lvl, Date {}, text));

	}
		
	Core::Const_View Core::get_records(void) const noexcept(false) {
		return Const_View { _m_records.cbegin(), _m_records.cend() };
	}
	
}
