#ifndef __CATAGRAPHE_SERDE__
#define __CATAGRAPHE_SERDE__
#include <cstdint>
#include <vector>

namespace ctgrph {
	using byte = std::uint8_t;
	using bytes = std::vector<byte>;

	class I_Serializible {
	public:
		[[nodiscard]]
		virtual bytes serialize(void) const noexcept(true) = 0;
	};

	class I_Deserializible {
	public:
		virtual void deserialize(const bytes&) noexcept(false) = 0;
	};
}

#endif
