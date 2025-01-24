#ifndef __CATAGRAPHE_APP_COMMANDS__
#define __CATAGRAPHE_APP_COMMANDS__

#include <catagraphe/core.h>
#include "./core-thread.h"

#include <memory>

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

		virtual void
		execute(ctgrph::Core &core) noexcept(false) override
		{
			core.create_record(_m_lvl, _m_text);
		}
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

		virtual void
		execute(ctgrph::Core &core) noexcept(false) override
		{
			core.save(_m_save_path);
		}
	};


	struct Const_View_Guard {
		ctgrph::Core::Const_View view;

		std::mutex mutex;
		bool finished;
	};

	/**
	 *     Get_Records_Command
	 * ---------------------------
	 *
	 */
	class Get_Records_Command: public core::I_Core_Command {
		std::shared_ptr<Const_View_Guard> _m_view;
	public:
		Get_Records_Command(std::shared_ptr<Const_View_Guard> view):
			_m_view(view) {}

		virtual void
		execute(ctgrph::Core &core) noexcept(false) override
		{
			std::lock_guard guard { _m_view->mutex };

			_m_view->view = core.get_records();
			_m_view->finished = true;
		}
	};
}


#endif
