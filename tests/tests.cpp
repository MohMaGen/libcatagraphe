#include "./tests.h"
#include <iostream>
#include <chrono>


int main(void)
{
	tests::Tests tests { };	

	tests.push_group(tests::date_tests());
	tests.push_group(tests::records_tests());
	tests.push_group(tests::core_tests());

	std::cout << "Start tests" << std::endl;
	tests.run_groups();
	std::cout << "Runt tests" << std::endl;

	int running = 0;
	while ((running = tests.count_groups_running()) > 0) { }

	std::cout << "complete_tests: ["
		  << tests.goups_count() - running << "/"
		  << tests.goups_count()
		  << "]" << std::endl;

	return 0;
}

namespace tests {
	std::mutex stdout_mutex { };

	void Tests::push_group(Test_Group::pointer group) noexcept(true)
	{
		_m_groups.push_back(std::move(group));
	}

	int Tests::goups_count(void) const noexcept(true)
	{
		return _m_groups.size();
	}

	int Tests::count_groups_running(void) const noexcept(true)
	{
		int count = 0;

		for (auto &group: _m_groups) {
			if (!group->is_finished()) ++count;
		}

		return count;
	}

	void Tests::run_groups(void) noexcept(true)
	{
		for (auto &group: _m_groups) {
			group->run_async();
		}
	}


	void Test_Group::run(void) noexcept(true)
	{
		const auto log_group = [this]() { 
			std::cout << "\x1b[33m(" << _m_name << ")\x1b[0m";
		};
		const auto log_succed = [log_group](auto val) { 
			std::lock_guard guar { stdout_mutex };
			log_group();
			std::cout << " \x1b[32m" << val << "\x1b[0m"
				  << std::endl;
		};
		const auto log_failed = [log_group](auto val) { 
			std::lock_guard guar { stdout_mutex };
			log_group();
			std::cout << " \x1b[31m" << val << "\x1b[0m"
				  << std::endl;
		};

		const auto test_failed = [log_failed](size_t n) {
			log_failed("test " + std::to_string(n) + " failed");
		};

		const auto test_succed = [log_succed](size_t n) {
			log_succed("test " + std::to_string(n) + " succed");
		};

		for (auto test: _m_tests) {
			std::lock_guard guard { _m_mutex };	

			try {
				test(); 
			} catch (std::exception &e) {
				_m_error = std::string(e.what());
				test_failed(_m_ok_count);
				log_failed(_m_error);
				break;	
			}
			test_succed(_m_ok_count);
			_m_ok_count++;
		}

		if (_m_error.length() != 0) {
			log_failed("group failed");
			return;
		}
		log_succed("group succed");
	}

	void Test_Group::run_async(void) noexcept(true)
	{
		_m_fut = std::async(&Test_Group::run, this);
	}

	bool Test_Group::is_finished(void) const noexcept(true)
	{
		using namespace std::chrono_literals;	

		auto status = _m_fut.wait_for(0ms);
		return status == std::future_status::ready;
	}

}
