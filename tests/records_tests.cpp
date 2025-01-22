#include "./tests.h"

#include <catagraphe/serde.h>
#include <catagraphe/core.h>


namespace records_tests {
	void serde_1(void)
	{
		using Level = ctgrph::Record_Level;

		ctgrph::Record record1 (Level::Info, {}, "Aboba");
		ctgrph::Record record2 {};

		auto bytes1 = record1.serialize();
		ctgrph::Const_Bytes_View view1 { bytes1 };

		record2.deserialize(view1);
		auto bytes2 = record2.serialize();
		ctgrph::Const_Bytes_View view2 { bytes2 };

		tests::Assert_Eq::assert_range(bytes1, bytes2);
		tests::Assert_Eq::assert_range(view1, view2);
		tests::Assert_Eq::assert((int)record1.lvl, (int)record1.lvl);
		tests::Assert_Eq::assert(record1.text, record1.text);
		tests::Assert_Eq::assert(record1.date.get_time(),
					 record1.date.get_time());
	}
}


tests::Test_Group::pointer tests::records_tests(void)
{
	return Test_Group::mk_pointer("records", 
			records_tests::serde_1);
}

