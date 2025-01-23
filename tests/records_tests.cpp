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

		assert_eq(*bytes1.rbegin(), (ctgrph::Byte)0);

		record2.deserialize(view1);
		auto bytes2 = record2.serialize();
		ctgrph::Const_Bytes_View view2 { bytes2 };

		assert_eq_range(bytes1, bytes2);
		assert_eq_range(view1, view2);
		assert_eq((int)record1.lvl, (int)record1.lvl);
		assert_eq(record1.text, record1.text);
		assert_eq(record1.date.get_time(),
					 record1.date.get_time());
	}

	void serde_2(void)
	{
		using Level = ctgrph::Record_Level;
		const std::string msg (400, 'a');

		ctgrph::Record record1 (Level::Info, {}, msg);
		ctgrph::Record record2 {};

		auto bytes1 = record1.serialize();
		ctgrph::Const_Bytes_View view1 { bytes1 };

		assert_eq(*bytes1.rbegin(), (ctgrph::Byte)0);

		record2.deserialize(view1);
		auto bytes2 = record2.serialize();
		ctgrph::Const_Bytes_View view2 { bytes2 };

		assert_eq_range(bytes1, bytes2);
		assert_eq_range(view1, view2);
		assert_eq((int)record1.lvl, (int)record1.lvl);
		assert_eq(record1.text, record1.text);
		assert_eq(record1.date.get_time(),
					 record1.date.get_time());
	}
}


tests::Test_Group::pointer tests::records_tests(void)
{
	return Test_Group::mk_pointer("records", 
			records_tests::serde_1, records_tests::serde_2);
}

