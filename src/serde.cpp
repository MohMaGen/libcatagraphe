#include <catagraphe/serde.h>
#include <catagraphe/exception.h>
#include <exception>

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

	void I_Deserializible::deserialize(const Bytes &b) noexcept(false) {
		Const_Bytes_View view { b };
		deserialize(view);
	}
}
