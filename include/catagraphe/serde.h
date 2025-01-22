#ifndef __CATAGRAPHE_SERDE__
#define __CATAGRAPHE_SERDE__
#include <cstdint>
#include <vector>

namespace ctgrph {
	using Byte = std::uint8_t;
	using Bytes = std::vector<Byte>;

	class Const_Bytes_View { 
		Bytes::const_iterator _m_begin, _m_end;
	public:
		Const_Bytes_View() {}
		Const_Bytes_View(Bytes::const_iterator begin,
				 Bytes::const_iterator end);

		Const_Bytes_View(const Bytes &b);

		Bytes::const_iterator begin(void) const noexcept(true);
		Bytes::const_iterator end(void) const noexcept(true);

		Const_Bytes_View shift(size_t n) noexcept(false);

		size_t len(void) const noexcept(true);
	};

	class I_Serializible {
	public:
		[[nodiscard]]
		virtual Bytes serialize(void) const noexcept(true) = 0;
		virtual ~I_Serializible() {}
	};

	class I_Deserializible {
	public:
		virtual void deserialize(Const_Bytes_View&) noexcept(false) = 0;
		virtual ~I_Deserializible() {}
	};
}

#endif
