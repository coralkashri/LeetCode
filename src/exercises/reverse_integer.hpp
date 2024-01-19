#include "../exercise.hpp"

namespace leet_code {

	/* Question source: https://leetcode.com/problems/reverse-integer */

    template<>
    class exercise_impl<"reverse_integer"> : public exercise_base {
    public:
        int32_t exercise(int32_t x) {
        	const bool is_negative = x < 0;
        	const int max_int = !is_negative ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
        	int32_t res = 0;
        	bool is_lower = false, is_higher = false;
        	constexpr char max_int_digits_count = std::numeric_limits<int32_t>::digits10 + 1;
        	auto divide = static_cast<int32_t>(std::pow(10, max_int_digits_count - 1));

        	while (x) {
        		const int32_t current_max_int_digit = std::abs((max_int / divide) % 10);
        		divide /= 10;

        		const int32_t current_int_digit = std::abs(x % 10);
        		x /= 10;

        		if (!is_higher && !is_lower) {
        			if (current_int_digit < current_max_int_digit)
        				is_lower = true;
        			else if (current_int_digit > current_max_int_digit)
        				is_higher = true;
        		}

        		if (!divide && is_higher) return 0;

        		res *= 10;
        		res += current_int_digit;
        	}

        	return res * (is_negative ? -1 : 1);
        }

        void prepare_test_cases() {
            actual_test_cases.emplace_back(123, 321);
            actual_test_cases.emplace_back(-5296, -6925);
            actual_test_cases.emplace_back(0, 0);
        }

        double test_cases() {
            double success = 0;

            for (auto [password, expected_result] : actual_test_cases) {
                success += check_if_same(password, exercise(password), expected_result);
            }

            return success / (double)actual_test_cases.size();
        }

    private:
    	std::vector<std::pair<int32_t, int32_t>> actual_test_cases;
    };
}