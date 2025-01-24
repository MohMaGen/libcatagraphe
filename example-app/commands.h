#ifndef __CATAGRAPHE_APP_COMMANDS__
#define __CATAGRAPHE_APP_COMMANDS__

#include <catagraphe/core.h>
#include "./core-thread.h"

namespace commands {

	/**
	 *     Create_Record_Command
	 * -----------------------------
	 * Commands that's creating new record with current date from level and
	 * text.
	 */
	class Record_Create_Command: public core::I_Core_Command {
		ctgrph::Record_Level _m_lvl;
		std::string _m_text;
	public:
		/**
		 * @param lvl  --- level of the record to create.
		 * @param text --- msg text fo the record to create.
		 */
		Record_Create_Command(ctgrph::Record_Level lvl,
				      std::string text):
				      _m_lvl(lvl), _m_text(text) {}

		virtual void execute(ctgrph::Core&) noexcept(false) override;
	};

	/**
	 *     Save_Command
	 * ---------------------
	 * Commands that's saving current `ctgrph::Core' state to the file[arg
	 * `save_path'].
	 */
	class Save_Command: public core::I_Core_Command {
		std::string _m_save_path;
	public:
		/**
		 * @param path --- path to save `ctgrph::Core' state.
		 */
		Save_Command(const std::string save_path):
			_m_save_path(save_path) {}

		virtual void execute(ctgrph::Core&) noexcept(false) override;
	};	
}


#endif
