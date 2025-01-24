#ifndef __CATAGRAPHE_APP_SHELL_COMMANDS__
#define __CATAGRAPHE_APP_SHELL_COMMANDS__
#include "./shell.h"
#include "./core-thread.h"


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

}



#endif
