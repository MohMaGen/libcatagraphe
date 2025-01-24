#ifndef __CATAGRAPHE_APP_CORE_THREAD__
#define __CATAGRAPHE_APP_CORE_THREAD__

#include <catagraphe/core.h>
#include <exception>
#include <stdexcept>
#include <thread>
#include <mutex>

namespace core {

	class Core_Thread_Exception: public std::runtime_error {
	public:
		Core_Thread_Exception(const std::string &what):
			std::runtime_error("[Core Thread]: " + what) { }
	};

	class I_Core_Command {
	public:
		virtual void execute(ctgrph::Core&) noexcept(false) = 0;
		~I_Core_Command() {}
	};

	/**
	 *     Core_Thread
	 * -------------------
	 * Class to interact with ctgrph::Core's thread.
	 *
	 * This class implements the RAII based thread save interface. To
	 * get access to the interface --- lock the `Core_Thread'; the
	 * thread will be locked for `Core_Interface' live time.
	 */
	class Core_Thread {
		std::thread _m_thrd;
		std::mutex  _m_mutex;

		ctgrph::Core _m_core;

		using Commands = std::vector<std::unique_ptr<I_Core_Command>>;
		Commands _m_commands;	

		bool _m_is_running;
	public:
		Core_Thread(ctgrph::Record_Level default_lvl);
		~Core_Thread();

		/**
		 * Inite `ctgrph::Core' with `db_origin_path', then
		 * create std::thread.
		 */
		void init(const std::string &db_path) noexcept(false);

		/**
		 *     Core_Interface
		 * ----------------------
		 * Interface for thread save interaction with `ctgrph::Core'.
		 */
		class Core_Interface {
			friend Core_Thread;

			std::lock_guard<std::mutex> _m_guard;	
			Commands &_m_commands;
			bool &_m_is_running;
		public:
			explicit Core_Interface(std::mutex &mutex,
						Commands &commands,
						bool &is_running):
				_m_guard(mutex),
				_m_commands(commands),
				_m_is_running(is_running) {}

			/**
			 * Construct and send command to the state thread.
			 */
			template<typename __Command, typename... __Args>
			void send_command(__Args... args);

			/**
			 * Close `Core_Thread'.
			 */
			void close(void) noexcept(true);
		};

		Core_Interface lock(void) noexcept(false);
	};
}


#endif
