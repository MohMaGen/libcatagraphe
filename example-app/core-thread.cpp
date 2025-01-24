#include "./core-thread.h"
#include <iostream>


namespace core {	
	Core_Thread::Core_Thread(ctgrph::Record_Level default_lvl):
		_m_thrd{}, _m_mutex{}, _m_core(default_lvl),
		_m_commands{}, _m_is_running{false} { }
	
	static void log_err(const std::string &what) {
		std::cerr << "[ERR] " + what << std::endl;
	}

	void Core_Thread::_m_loop(void) noexcept(true) {
		do {
			std::lock_guard guard { _m_mutex };
			for (auto &cmd : _m_commands) {
				try {
					cmd->execute(_m_core);
				} catch (std::exception &e) {
					log_err(e.what());
				};
			}
			_m_commands.clear();
		} while(_m_is_running);
	}

	void Core_Thread::init(const std::string &db_path) noexcept(false)
	{
		_m_core.init(db_path);	
		_m_thrd = std::thread(&Core_Thread::_m_loop, this);

		_m_is_running = true;
	}

	Core_Thread::Core_Interface Core_Thread::lock(void) noexcept(false)
	{
		if (!_m_is_running)
			throw Core_Thread_Exception("Try lock, but not inited");

		return Core_Interface (_m_mutex, _m_commands, _m_is_running);
	}

	Core_Thread::~Core_Thread(void)
	{
		_m_thrd.join();	
	}


	void Core_Thread::Core_Interface::close(void) noexcept(true)
	{
		_m_is_running = false;
	}
}
