#include "../exercise.hpp"

namespace leet_code {

    /* Question source: https://leetcode.com/problems/strong-password-checker */

    template<>
    class exercise_impl<"strong_password_checker"> : public exercise_base {
    public:
        size_t exercise(std::string_view password) {
            size_t required_length_add = password.size() < 6 ? 6 - password.size() : 0;
            int64_t required_length_remove = password.size() > 20 ? password.size() - 20 : 0;

            bool missing_upper_case = true;
            bool missing_lower_case = true;
            bool missing_digit = true;

            char prev_char = password[0] - 1;
            int64_t current_repeats = 0;
            std::priority_queue<int64_t, std::vector<int64_t>, decltype([](int64_t a, int64_t b) {
                return a % 3 > b % 3;
            })> problem_repeats;

            for (char c : password) {
                if (missing_lower_case && c >= 'a' && c <= 'z') missing_lower_case = false;
                else if (missing_upper_case && c >= 'A' && c <= 'Z') missing_upper_case = false;
                else if (missing_digit && c >= '0' && c <= '9') missing_digit = false;

                if (prev_char == c) {
                    current_repeats++;
                } else {
                    if (current_repeats >= 2) {
                        problem_repeats.push(current_repeats + 1);
                    }
                    current_repeats = 0;
                }

                prev_char = c;
            }

            if (current_repeats >= 2) {
                problem_repeats.push(current_repeats + 1);
            }

            if (problem_repeats.size() + required_length_add + required_length_remove
                + missing_upper_case + missing_lower_case + missing_digit == 0) return 0;

            size_t missing_chars = missing_upper_case + missing_lower_case + missing_digit;
            size_t ans = 0;
            while (required_length_remove > 0 && !problem_repeats.empty()) {
                if (problem_repeats.top() == 3) {
                    problem_repeats.pop();
                } else {
                    auto new_problem = problem_repeats.top() - 1;
                    problem_repeats.pop();
                    problem_repeats.push(new_problem);
                }
                --required_length_remove;
                ++ans;
            }

            ans += required_length_remove;

            return ans + std::max(std::max(required_length_add, missing_chars), [&problem_repeats]() {
                size_t res = 0;
                while (!problem_repeats.empty()) {
                    res += problem_repeats.top() / 3;
                    problem_repeats.pop();
                }
                return res;
            }());
        }

        std::vector<std::pair<std::string_view, size_t>> actual_test_cases;

        void prepare_test_cases() {
            actual_test_cases.emplace_back("a", 5ul);
            actual_test_cases.emplace_back("aA1", 3ul);
            actual_test_cases.emplace_back("1337C0d3", 0ul);
            actual_test_cases.emplace_back("aaa123", 1ul);
            actual_test_cases.emplace_back("aaa1B", 1ul);
            actual_test_cases.emplace_back("aaa111", 2ul);
            actual_test_cases.emplace_back("1111111111", 3ul);
            actual_test_cases.emplace_back("bbaaaaaaaaaaaaaaacccccc", 8ul);
            actual_test_cases.emplace_back("aaaaAAAAAA000000123456", 5ul);
        }

        double test_cases() {
            double success = 0;

            for (auto [password, expected_result] : actual_test_cases) {
                success += check_if_same(password, exercise(password), expected_result);
            }

            return success / (double)actual_test_cases.size();
        }
    };
}