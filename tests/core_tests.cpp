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

			'\x0A',

			'\x01', // lvl

			'\x00','\x00','\x00','\x00',
			'\x00','\x00','\x00','\x00', // date

			'H', 'e', 'l', 'l', 'o', ',', ' ',
			'C', 't', 'g', 'r', 'p', 'h', '!', '\x00'

			// may not end with newline
		});

		ctgrph::Core core (ctgrph::Record_Level::Info);
		core.init(bytes);

		auto records = core.get_records();

		auto record1 = records.begin()[0];
		assert_eq(record1.text, "Hello, World!");
		assert_eq((int)record1.lvl, (int)ctgrph::Record_Level::Text);
		assert_eq(record1.date.get_time(), (time_t) 0x0);

		auto record2 = records.begin()[1];
		assert_eq(record2.text, "Hello, Ctgrph!");
		assert_eq((int)record2.lvl, (int)ctgrph::Record_Level::Debug);
		assert_eq(record2.date.get_time(), (time_t) 0x0);
	}
}

tests::Test_Group::pointer tests::core_tests(void)
{
	return Test_Group::mk_pointer("core", core_tests::init_1);
}
