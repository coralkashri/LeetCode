#pragma once

#include <algorithm>
#include <bitset>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <span>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "fixed_string.hpp"
#include "time.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& cout, std::vector<T> cont) {
	std::copy_n(cont.begin(), cont.size(), std::ostream_iterator<T>(std::cout, ", "));
	return cout;
}

namespace leet_code {
	class exercise_base {
	public:
		virtual ~exercise_base() = default;

		template <typename Exercise>
		void run_test_cases(this Exercise&& self) {
			self.prepare_test_cases();
			auto start_time = std::chrono::high_resolution_clock::now();
			double res = self.test_cases();
			auto stop_time = std::chrono::high_resolution_clock::now();
			std::cout << "Success percentages: " << res * 100 << "%\n";
			std::cout << "Computation time: ";
			pretty_time_print(start_time, stop_time);
			std::cout << std::endl;
		}

		template <typename Exercise, typename ResT = void, typename... Args>
		void run_exercise(this Exercise&& self, Args... args) {
			auto start_time = std::chrono::high_resolution_clock::now();
			auto res = self.template exercise<ResT, Args...>(args...);
			auto stop_time = std::chrono::high_resolution_clock::now();
			std::cout << res << "\n";
			std::cout << "Computation time: ";
			pretty_time_print(start_time, stop_time);
			std::cout << std::endl;
		}

	protected:
		template <typename ResT>
		bool check_if_same(auto param, ResT actual, ResT expected) {
			if (actual == expected) {
				// std::cout << "SUCCESS\n";
				return true;
			}
			std::cout << "Param: " << param << " ";
			std::cout << "FAIL: Actual: " << actual << " Expected: " << expected <<
				"\n";
			return false;
		}
	};

	template <fixed_string Name>
	class exercise_impl : public exercise_base {
	public:
		template <typename ResT = void, typename... Args>
		ResT exercise(Args... args) {
			throw std::runtime_error("Unimplemented");
		}

		virtual void prepare_test_cases() {
			std::cout << "No prepare test cases are defined for this exercise\n";
		}

		virtual double test_cases() {
			std::cout << "No test cases are defined for this exercise\n";
			return 1;
		}
	};
} // namespace leet_code
