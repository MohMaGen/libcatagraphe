#include "tests.h"
#include <catagraphe/core.h>


namespace core_tests {
	void init_1(void) {
		const ctgrph::Bytes bytes ({
			'\x00', // lvl

			'\x00','\x00','\x00','\x00',
			'\x00','\x00','\x00','\x00', // date

			'H', 'e', 'l', 'l', 'o', ',', ' ',
			'W', 'o', 'r', 'l', 'd', '!', '\x00',

			'\x00', // lvl

			'\x00','\x00','\x00','\x00',
			'\x00','\x00','\x00','\x00', // date

			'H', 'e', 'l', 'l', 'o', ',', ' ',
			'C', 't', 'g', 'r', 'p', 'h', '!', '\x00'
		});

		ctgrph::Core core (ctgrph::Record_Level::Info);
		core.init(bytes);

		auto records = core.get_records();

		tests::Assert_Eq::assert(records.begin()->text,
					 "Hello, World!");

		tests::Assert_Eq::assert((records.begin()+1)->text,
					 "Hello, Ctgrph!");
	}
}

tests::Test_Group::pointer tests::core_tests(void)
{
	return Test_Group::mk_pointer("core", core_tests::init_1);
}
