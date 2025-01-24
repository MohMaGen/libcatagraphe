#include <catagraphe/core.h>

#include <iostream>
#include <cstring>
#include "./core-thread.h"
#include "./commands.h"
#include "./shell.h"

const char HELP_MSG[] =
	"USAGE:\n"
	"\t\x1b[1mexample-app\x1b[0m \x1b[4mPATH_TO_DB\x1b[0m [\x1b[4mDEFAULT_LEVEL\x1b[0m]\n"
	"\n"
	"OPTIONS:\n"
	"\t\x1b[1;4mPATH_TO_DB\x1b[0m\tpath to database file.\n"
	"\n"
	"\t\x1b[1;4mDEFAULT_LEVEL\x1b[0m\tname of default level\n"
	"\t\t\tOne of Text, Debug, Info, Warning, Error. If not\n"
	"\t\t\tspecified, the Text value will be used as default level.\n";



int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << "\x1b[31m" << "Wrong command line options:"
			  << "\x1b[0m"  << std::endl;
		std::cerr << HELP_MSG << std::endl;
		return 1;
	}

	std::string db_path { argv[1] };


	ctgrph::Record_Level default_lvl = ctgrph::Record_Level::Text;
	if (argc >= 3) {
		if (std::strcmp(argv[2], "Text") == 0)
			default_lvl = ctgrph::Record_Level::Text;

		if (std::strcmp(argv[2], "Info") == 0)
			default_lvl = ctgrph::Record_Level::Text;

		if (std::strcmp(argv[2], "Warning") == 0)
			default_lvl = ctgrph::Record_Level::Warning;

		if (std::strcmp(argv[2], "Error") == 0)
			default_lvl = ctgrph::Record_Level::Error;
	}

	core::Core_Thread thrd { default_lvl };
	thrd.init(db_path);

	
	shell::Shell shell { "[" + db_path + " catagraphe]$" };

	shell.run();	

	return 0;
}
