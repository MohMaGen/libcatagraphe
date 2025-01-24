#ifndef __CATAGRAPHE_APP_SHELL_COMMANDS__
#define __CATAGRAPHE_APP_SHELL_COMMANDS__

#include <algorithm>

#include "./core-thread.h"
#include "./commands.h"
#include "./shell.h"


namespace shell {

	class Close_Command: public I_Command {
		std::shared_ptr<core::Core_Thread> _m_thrd;
	public:
		Close_Command(std::shared_ptr<core::Core_Thread> thrd):
			_m_thrd(thrd) {}

		virtual void
		execute(std::shared_ptr<Env> env,
			std::vector<std::string> args) noexcept(false) override
		{
			if (args.size() != 0)
				throw Wrong_Arguments_Exception(help_msg());

			env->should_close = true;
			_m_thrd->lock().close();
		}

		virtual bool
		match_name(const std::string &name) const noexcept(true)
						    override
		{
			return name == std::string("close");
		}

		virtual std::string
		help_msg(void) const noexcept(true) override
		{
			static const char msg[] = 
				"USAGE:\n"
				"\t\x1b[1mclose\x1b[0m\n"
				"ARGUMENTS:\n"
				"\thas not.\n";

			return { msg };
		}

	};

	class Clear_Command: public I_Command {
	public:
		Clear_Command() {}

		virtual void
		execute(std::shared_ptr<Env> env,
			std::vector<std::string> args) noexcept(false) override
		{
			if (args.size() != 0)
				throw Wrong_Arguments_Exception(help_msg());
			
			system("clear");
		}

		virtual bool
		match_name(const std::string &name) const noexcept(true)
						    override
		{
			return name == std::string("clear");
		}

		virtual std::string
		help_msg(void) const noexcept(true) override
		{
			static const char msg[] = 
				"USAGE:\n"
				"\t\x1b[1mclear\x1b[0m\n"
				"ARGUMENTS:\n"
				"\thas not.\n";

			return { msg };
		}

	};


	class Create_Record_Command: public I_Command {
		std::shared_ptr<core::Core_Thread> _m_thrd;
	public:
		Create_Record_Command(std::shared_ptr<core::Core_Thread> thrd):
			_m_thrd(thrd) {}

		virtual void
		execute(std::shared_ptr<Env> env,
			std::vector<std::string> args) noexcept(false) override
		{
			if (args.size() < 2)
				throw Wrong_Arguments_Exception(help_msg());
			
			auto lvl = ctgrph::level_of_string(args[0]);
			std::string text { };
			
			std::for_each(args.begin()+1, args.end(),
				      [&text](const auto &value) {
				      		if (text.size() > 0)
							text += " ";
				     		text += value;
				      });
			
			auto guard = _m_thrd->lock();
			guard.send_command<commands::Record_Create_Command>
								(lvl, text);
		}

		virtual bool
		match_name(const std::string &name) const noexcept(true)
						    override
		{
			return name == std::string("create");
		}

		virtual std::string
		help_msg(void) const noexcept(true) override
		{
			static const char msg[] = 
				"USAGE:\n"
				"\t\x1b[1mcreate\x1b[0m "
				"\x1b[4;1mLEVEL\x1b[0m "
				"\x1b[4;1mTEXT\x1b[0m\n"
				"ARGUMENTS:\n"
				"\t\x1b[1mLEVEL\x1b[0m\tlevel of the record.\n"
				"\t\x1b[1mTEXT\x1b[0m\ttext of the record.\n";

			return { msg };
		}

	};

	class Save_Command: public I_Command {
		std::shared_ptr<core::Core_Thread> _m_thrd;
		std::string _m_origin_db_path;
	public:
		Save_Command(std::shared_ptr<core::Core_Thread> thrd,
			     std::string origin_db_path):
			_m_thrd(thrd), _m_origin_db_path(origin_db_path) {}

		virtual void
		execute(std::shared_ptr<Env> env,
			std::vector<std::string> args) noexcept(false) override
		{
			if (args.size() > 1)
				throw Wrong_Arguments_Exception(help_msg());

			std::string path = _m_origin_db_path;
			if (args.size() == 1) path = args[0]; 
		
				
			auto guard = _m_thrd->lock();
			guard.send_command<commands::Save_Command>(path);
		}

		virtual bool
		match_name(const std::string &name) const noexcept(true)
						    override
		{
			return name == std::string("save");
		}

		virtual std::string
		help_msg(void) const noexcept(true) override
		{
			static const char msg[] = 
				"USAGE:\n"
				"\t\x1b[1mcreate\x1b[0m "
				"\x1b[4;1m[DB_PATH]\x1b[0m "
				"ARGUMENTS:\n"
				"\t\x1b[1mDB_PATH\x1b[0m\tpath to save the "
				"current state of core.\n"
				"\t\t\tIf DB_PATH not set then will use origin"
				"[the one\n"
				"used to init core] database path.\n";

			return { msg };
		}

	};

}



#endif
