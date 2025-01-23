#include <catagraphe/serde.h>
#include <catagraphe/exception.h>
#include <exception>
#include <fstream>

namespace ctgrph {

	Const_Bytes_View::Const_Bytes_View(Bytes::const_iterator begin,
					   Bytes::const_iterator end):
		_m_begin(begin), _m_end(end) { }	

	Const_Bytes_View::Const_Bytes_View(const Bytes &b):
		_m_begin(b.cbegin()), _m_end(b.cend()) { }

	Bytes::const_iterator Const_Bytes_View::begin(void) const noexcept(true)
	{
		return _m_begin;
	}

	Bytes::const_iterator Const_Bytes_View::end(void) const noexcept(true)
	{
		return _m_end;
	}

	Const_Bytes_View Const_Bytes_View::shift(size_t n) noexcept(false)
	{
		static const auto err = "Shift size grater than view size!";
		if (n > len()) throw std::out_of_range(err);

		Const_Bytes_View ret { _m_begin, _m_begin + n };
		_m_begin += n;

		return ret;
	}

	size_t Const_Bytes_View::len(void) const noexcept(true)
	{
		return _m_end - _m_begin;
	}

	void Bytes::read_file(const std::string &path) noexcept(false)
	{
		std::ifstream file (path, std::ios::binary);

		char c;
		while (file.get(c)) push_back((Byte)c);
	}

	Bytes::const_iterator Bytes::begin(void) const noexcept(true) {
		return _m_data.begin();
	}

	Bytes::const_iterator Bytes::end(void) const noexcept(true) {	
		return _m_data.end();
	}
	Bytes::const_iterator Bytes::cbegin(void) const noexcept(true) {
		return _m_data.cbegin();
	}

	Bytes::const_iterator Bytes::cend(void) const noexcept(true) {	
		return _m_data.cend();
	}
	Bytes::const_reverse_iterator Bytes::rbegin(void) const noexcept(true)
	{
		return _m_data.rbegin();
	}
	Bytes::const_reverse_iterator Bytes::rend(void) const noexcept(true)
	{
		return _m_data.rend();
	}

	void Bytes::push_back(Byte byte) noexcept(true)
	{
		_m_data.push_back(byte);
	}

	std::back_insert_iterator<Bytes_Vec> back_inserter(Bytes& bytes)
	{
		return std::back_inserter(bytes._m_data); 
	}


}
