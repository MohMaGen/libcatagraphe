#ifndef __CATAGRAPHE_DATE__
#define __CATAGRAPHE_DATE__
#include <cstddef>
#include <string>
#include <time.h>

#include <catagraphe/serde.h>


namespace ctgrph {
	/**
	 *	
	 */
	class Date: public I_Serialize, public I_Deserialize {
		time_t _m_unistd_time; 
	public:
		Date();

		/**
		 * @brief Display date with given format.
		 * 
		 * Format string the same as for `std::strftime'.
		 *
		 * @param fmt --- the format.
		 * @return formated string.
		 */
		[[nodiscard("Displayed date must be used!")]]
		std::string
		display(const std::string &fmt) const noexcept(false);

		[[nodiscard]]
		virtual bytes serialize(void) const noexcept(true) override;

		virtual void deserialize(bytes) noexcept(false) override;
	private:
		bool
		_proc_fmt_seq(std::stirng_view, std::string&, std::string)
			noexcept(true);
	};
}


#endif
