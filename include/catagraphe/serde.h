#ifndef __CATAGRAPHE_SERDE__
#define __CATAGRAPHE_SERDE__
#include <cstdint>
#include <vector>

namespace ctgrph {
	using byte = std::unit8_t;
	using bytes = std::vector<byte>;

	class I_Serialisible {
	public:
		[[nodiscard]]
		virtual bytes serialize(void) const noexcept(true) = 0;
	};

	class I_Deserialisible {
	public:
		virtual void deserialize(bytes) noexcept(false) = 0;
	};
}

#endif
