#include "./shell.h"
#include <iostream>


namespace shell {

	Shell::Shell(const std::string &prompt):
		_m_commands{ }, _m_prompt(prompt)
	{
		_m_env = std::make_shared<Env>();
		_m_env->should_close = false;
	}


	static std::vector<std::string> parse_args(std::string_view view)
	{
		std::vector<std::string> result { };	
		auto trim = [](auto &view) {
			view.remove_prefix(std::min(view.find_first_not_of(" "),
					    view.size()));
		};


		trim(view);
		while (view.length() > 0) {

			char end = ' ';
			if (view.begin()[0] == '"') {
				view.remove_prefix(1);
				end = '"';
			}
			
			size_t i = std::min(view.find(end), view.size());	

			std::string_view res { view.begin(), i};
			result.push_back(std::string(res));
			
			if (end == '"') ++i;
			view.remove_prefix(i);
			trim(view);
		}

		return result;
	}

	void Shell::run(void) noexcept(true)
	{
		const auto execute_cmd = [this](auto &cmd, const auto &args) {
			try {
				cmd->execute(_m_env, args);
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
			}
		};

		while (!_m_env->should_close) {
			std::cout << _m_prompt + " ";
			std::string name;
			std::cin >> name;

			char buf[0x100];
			std::cin.getline(buf, sizeof(buf)-1);

			auto args = parse_args(std::string_view{ buf });

			bool exec = false;
			for (auto &cmd : _m_commands) {
				if (!cmd->match_name(name)) continue;
				exec = true;
				execute_cmd(cmd, args);
				break;
			}

			if (!exec) {
				std::cerr << "\x1b[31;1m[Wrong Command]\x1b[0m"
					  << std::endl;
			}
		}
	}
}
