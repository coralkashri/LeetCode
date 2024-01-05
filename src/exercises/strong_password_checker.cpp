#include "../exercise.hpp"

namespace leet_code {

    /* Question source: https://leetcode.com/problems/strong-password-checker */

    template<>
    size_t exercise<"strong_password_checker">(std::string_view password) {
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

    template<>
    double test_cases<"strong_password_checker">() {
        double test_cases_count = 0;
        double success = 0;
        size_t res;

        std::string_view current_input = "a";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 5ul);

        current_input = "aA1";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 3ul);

        current_input = "1337C0d3";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 0ul);

        current_input = "aaa123";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 1ul);

        current_input = "aaa1B";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 1ul);

        current_input = "aaa111";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 2ul);

        current_input = "1111111111";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 3ul);

        current_input = "bbaaaaaaaaaaaaaaacccccc";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 8ul);

        current_input = "aaaaAAAAAA000000123456";
        res = exercise<"strong_password_checker", size_t>(current_input);
        ++test_cases_count;
        success += check_if_same(current_input, res, 5ul);

        return success / test_cases_count;
    }
}