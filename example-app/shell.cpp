#include "./shell.h"
#include <iostream>


namespace shell {
	class Close_Command: public I_Command {
		bool &_m_should_close;
	public:
		Close_Command(bool &should_close):
			_m_should_close(should_close) {}

		virtual void
		execute(std::vector<std::string> args) noexcept(false) override
		{
			if (args.size() != 0)
				throw Wrong_Arguments_Exception(help_msg());

			_m_should_close = true;
		}

		virtual bool
		match_name(const std::string &name) const noexcept(true)
						    override
		{
			return name == "close";
		}

		virtual std::string
		help_msg(void) const noexcept(true) override
		{
			return
				"USAGE:\n"
				"\t\x1b[1mclose\x1b[0\n"
				"ARGUMENTS:\n"
				"\thas not.\n";
		}

	};


	Shell::Shell(const std::string &prompt):
		_m_commands{ }, _m_prompt(prompt), _m_should_close{ false }
	{
		add_command<Close_Command>(_m_should_close);
	}

	template<typename __Command, typename... __Args>
	void Shell::add_command(__Args... args) noexcept(false)
	{
		auto cmd = std::unique_ptr<I_Command>(new __Command(args...));
		_m_commands.push_back(std::move(cmd));
	}

	void Shell::run(void) noexcept(true)
	{
		const auto execute_cmd = [](auto &cmd) {
			try {
				cmd->execute({});
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
			}
		};

		while (!_m_should_close) {
			std::cout << _m_prompt + " ";
			std::string name;
			std::cin >> name;

			for (auto &cmd : _m_commands) {
				if (!cmd->match_name(name)) continue;

				execute_cmd(cmd);
			}
		}
	}
}
