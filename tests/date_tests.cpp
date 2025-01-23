#include "./tests.h"
#include <catagraphe/exception.h>
#include <catagraphe/serde.h>
#include <catagraphe/date.h>

#include <iostream>


namespace date_tests {
	void serde_1(void) {
		ctgrph::Date date1 { }, date2 { };
		auto bytes = date1.serialize();
		ctgrph::Const_Bytes_View view { bytes };
		date2.deserialize(view);

		assert_eq(date2.get_time(), date1.get_time());
	}

	void serde_2(void) [[maybe_unused]] {
		ctgrph::Date date1 { }, date2 { };

		auto bytes1 = date1.serialize();
		ctgrph::Const_Bytes_View view1 { bytes1 };

		date2.deserialize(view1);
		auto bytes2 = date2.serialize();
		ctgrph::Const_Bytes_View view2 { bytes2 };

		assert_eq_range(bytes1, bytes2);
		assert_eq_range(view1, view2);
	}	

	void display_1(void) {
		ctgrph::Date date1 { };
		std::string str (200, 'a');
		
		assert_exception((void) date1.display(str);,
				 ctgrph::Date_Display_Exception);

		(void) date1.display("%H:%M:%s");
	}
}

tests::Test_Group::pointer tests::date_tests(void) {
	return Test_Group::mk_pointer( "date",
		date_tests::serde_1, date_tests::serde_2,
		date_tests::display_1);
}
