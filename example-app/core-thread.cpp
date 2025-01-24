#include "./core-thread.h"
#include <iostream>


namespace core {	
	Core_Thread::Core_Thread(ctgrph::Record_Level default_lvl):
		_m_core(default_lvl) { }
	
	static void log_err(const std::string &what) {
		std::cerr << "[ERR] " + what << std::endl;
	}

	void Core_Thread::init(const std::string &db_path) noexcept(false)
	{
		const auto event_loop = [this](void) {
			std::lock_guard guard { _m_mutex };
			for (auto &cmd : _m_commands) {
				try {
					cmd->execute(_m_core);
				} catch (std::exception &e) {
					log_err(e.what());
				};
			}
		};

		_m_core.init(db_path);	
		_m_thrd = std::thread([this, &event_loop](void) {
			do event_loop(); while(_m_is_running);
		});

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


	template<typename __Command, typename... __Args>
	void Core_Thread::Core_Interface::send_command(__Args... args)
	{
		auto cmd = std::unique_ptr<I_Core_Command>(
					new __Command(args...));
		_m_commands.push_back(std::move(cmd));
	}

	void Core_Thread::Core_Interface::close(void) noexcept(true)
	{
		_m_is_running = false;
	}
}
