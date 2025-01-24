#ifndef __CATAGRAPHE_APP_SHELL__
#define __CATAGRAPHE_APP_SHELL__
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>


namespace shell {

	struct Env {
		bool should_close;
	};

	class Wrong_Arguments_Exception: public std::runtime_error {
	public:
		Wrong_Arguments_Exception(const std::string &help_msg):
			std::runtime_error("[Wrong arguments] see help msg:\n"
					   + help_msg) { }
	};


	/**
	 *     I_Command
	 * -----------------
	 * Command interface for shell.
	 */
	class I_Command {
	public:
		/**
		 * Method that execute command.
		 *
		 * @param args --- arguments passed to the command.
		 */
		virtual void
		execute(std::shared_ptr<Env> env,
			std::vector<std::string> args) noexcept(false) = 0;

		/**
		 * Match command name with shell input.
		 */
		virtual bool
		match_name(const std::string&) const noexcept(true) = 0;

		/**
		 * Return documentation [help msg] for this command.
		 */
		virtual std::string help_msg(void) const noexcept(true) = 0;
	};

	/**
	 *     Shell
	 * -------------
	 */
	class Shell {
		std::vector<std::unique_ptr<I_Command>> _m_commands;
		std::string _m_prompt;
		std::shared_ptr<Env> _m_env;
	public:
		Shell(const std::string &prompt);

		template<typename __Command, typename... __Args>
		void add_command(__Args... args) noexcept(false)
		{
			auto cmd = std::unique_ptr<I_Command>(
						new __Command(args...));
			_m_commands.push_back(std::move(cmd));
		}

		void run(void) noexcept(true);
	};	
}

#endif
