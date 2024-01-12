//#pragma once
#include <cstring>
#include "../exercise.hpp"

namespace leet_code {
    /* Question source: https://leetcode.com/problems/palindrome-partitioning-ii/description/ */

    template<>
    class exercise_impl<"palindrome_partitioning_2"> : public exercise_base {
    public:
        size_t exercise(std::string s) {
            return solver().min_cut(s);
        }

        void prepare_test_cases() {
            actual_test_cases.emplace_back("cbbbcc", 1ul);
            actual_test_cases.emplace_back("aaaabaa", 1ul);
            actual_test_cases.emplace_back("aab", 1ul);
            actual_test_cases.emplace_back("a", 0ul);
            actual_test_cases.emplace_back("ab", 1ul);
            actual_test_cases.emplace_back("efe", 0ul);
            actual_test_cases.emplace_back("kwtbjmsjvbrwriqwxadwnufplszhqccayvdhhvscxjaqsrmrrqngmuvxnugdzjfxeihogzsdjtvdmkudckjoggltcuybddbjoizu", 89ul);
            actual_test_cases.emplace_back("ababababababababababababcbabababababababababababa", 0ul);
            actual_test_cases.emplace_back("fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi", 75ul);
            actual_test_cases.emplace_back("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", 1ul);
        }

        double test_cases() {
            double success = 0;

            for (auto[str, expected_result]: actual_test_cases) {
                success += check_if_same(str, exercise(str), expected_result);
            }

            return success / (double) actual_test_cases.size();
        }

    private:
        std::vector<std::pair<std::string, size_t>> actual_test_cases;

        class solver {
        public:
            size_t min_cut(std::string_view s) {
                std::fill_n(memo, 2000, -1);
                std::memset(is_palindrome_memo, -1, sizeof(is_palindrome_memo));

                return next_cut(s);
            }

        private:
            int memo[2000];
            char is_palindrome_memo[2000][2000];

            bool is_palindrome(const std::string_view &str, int64_t start, int64_t stop) {
                if (is_palindrome_memo[start][stop] != -1) return is_palindrome_memo[start][stop];
                auto &res = is_palindrome_memo[start][stop];
                while (start <= stop) {
                    if (str[start++] != str[stop--]) return res = false;
                }
                return res = true;
            }

            size_t next_cut(std::string_view str, int64_t start = 0) {
                if (memo[start] != -1) {
                    return memo[start];
                }

                if (is_palindrome(str, start, ssize(str) - 1)) {
                    return 0;
                }

                size_t ans = -1;
                for (int64_t stop_index = start; stop_index < str.size(); ++stop_index) {
                    if (is_palindrome(str, start, stop_index)) {
                        ans = std::min(ans, 1 + next_cut(str, stop_index + 1));
                    }
                }

                return memo[start] = ans;
            }
        };
    };
}