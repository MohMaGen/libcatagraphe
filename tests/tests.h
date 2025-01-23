#ifndef __CATAGRAPHE_TESTS__
#define __CATAGRAPHE_TESTS__

#include <functional>
#include <exception>
#include <vector>
#include <future>
#include <memory>
#include <mutex>

namespace tests {	
	using Test = std::function<void(void)>;
	
	class Test_Group {
		std::vector<Test> _m_tests;
		std::string _m_name;

		std::future<void> _m_fut;
		std::string _m_error;
		std::mutex _m_mutex;
		size_t _m_ok_count;
	public:
		using pointer = std::unique_ptr<Test_Group>;

		template<typename ...__Tests>
		Test_Group(std::string name, __Tests... tests):
			_m_tests{ tests... },
			_m_name{ name },
			_m_error{ "" },
			_m_ok_count{ 0 }
			{ }

		template<typename ...__Tests>
		static pointer mk_pointer(__Tests... tests)
		{
			return std::make_unique<Test_Group>(tests...);
		}

		void run_async(void) noexcept(true);
		void run(void) noexcept(true);

		bool is_finished(void) const noexcept(true);

		std::string get_name(void) const noexcept(true) {
			return _m_name;
		}
	};

	class Tests {
		std::vector<Test_Group::pointer> _m_groups;

	public:
		void push_group(Test_Group::pointer) noexcept(true);

		void run_groups(void) noexcept(true);
		int count_groups_running(void) const noexcept(true);
		int goups_count(void) const noexcept(true);
	};

	class Assert_Exception: public std::runtime_error {
	public:
		Assert_Exception(std::string what, int line, std::string file):
			std::runtime_error(
				"(" + file +":" + std::to_string(line) + ") "
				+ what) {}
	};

	class Assert_Eq: public Assert_Exception {
	public:
		static void assert(std::string val, std::string must_be,
				   int line, std::string file) {
			if (val == must_be) return;
			throw Assert_Eq(val, must_be, line, file);
		}

		template<typename __Range>
		static void assert_range(__Range val, __Range  must_be,
					 int line, std::string file) {
			if (std::equal(val.begin(), val.end(),
				       must_be.begin())) return;
			
			std::string val_s = "{ ", must_be_s = "{ ";

			std::for_each(val.begin(), val.end(),
				[&val_s](auto e) {
					val_s += "`";
					val_s += std::to_string(e);
					val_s += "' ";
				});
			val_s += "}";

			std::for_each(must_be.begin(), must_be.end(),
				[&must_be_s](auto e) {
					must_be_s += "`";
					must_be_s += std::to_string(e);
					must_be_s += "' ";
				});

			must_be_s += "}";

			throw Assert_Eq(val_s, must_be_s, line, file);

		}

		template<typename T>
		static void
		assert(T val, T must_be, int line, std::string file) {
			if (val == must_be) return;

			throw Assert_Eq(std::to_string(val),
					std::to_string(must_be),
					line, file);
		}

		Assert_Eq(std::string val, std::string must_be,
			  int line, std::string file):
			Assert_Exception(
				"[Assert Eq failed]: expect to be "
				"equal to `" + must_be + "', "
				"but actually is `" + val +"'",
				line, file) { }

#define assert_eq(val, must_be) tests::Assert_Eq::assert(val, must_be,        \
							 __LINE__, __FILE__)

#define assert_eq_range(val, must_be) tests::Assert_Eq::assert_range(         \
					val, must_be, __LINE__, __FILE__)

	};

	class Assert_Expect_Exception: public std::runtime_error {
	public:
		Assert_Expect_Exception(std::string name):
			std::runtime_error(
				"[Assert Expect Exception]: "
				"expect throwing exception`" + name + ".") { }	
	};

	#define assert_exception(block, exception) do try {                   \
			block                                                 \
			throw tests::Assert_Expect_Exception(#exception);     \
		} catch (exception &e) { }                                    \
		  catch (...) {                                               \
			throw tests::Assert_Expect_Exception(#exception);     \
		} while(0)                                                    \


	Test_Group::pointer date_tests(void);
	Test_Group::pointer records_tests(void);
	Test_Group::pointer core_tests(void);
}


#endif
