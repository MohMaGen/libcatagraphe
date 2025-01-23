#ifndef __CATAGRAPHE_SERDE__
#define __CATAGRAPHE_SERDE__
#include <cstdint>
#include <string>
#include <vector>

namespace ctgrph {
	using Byte = std::uint8_t;
	using Bytes_Vec = std::vector<Byte>;

	class Bytes;
	std::back_insert_iterator<Bytes_Vec> back_inserter(Bytes&);

	class Bytes {
		Bytes_Vec _m_data;
	public:
		using const_iterator = Bytes_Vec::const_iterator;
		using const_reverse_iterator = Bytes_Vec::const_reverse_iterator;
		using value_type     = Byte;

		template<typename ...__Types>
		Bytes(__Types... types): _m_data(types...) { }

		void read_file(const std::string &path) noexcept(false);
		const_iterator begin(void) const noexcept(true);
		const_iterator end(void) const noexcept(true);
		const_iterator cbegin(void) const noexcept(true);
		const_iterator cend(void) const noexcept(true);
		const_reverse_iterator rbegin(void) const noexcept(true);
		const_reverse_iterator rend(void) const noexcept(true);

		void push_back(Byte) noexcept(true);

		friend std::back_insert_iterator<Bytes_Vec>
		ctgrph::back_inserter(Bytes&);
	};

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
