#include "../exercise.hpp"

namespace leet_code {
    /* Question source: https://leetcode.com/problems/palindrome-partitioning-ii/description/ */

    constexpr char exercise_name[] = "palindrome_partitioning_2";

    class solver {
    public:
        size_t min_cut(std::string_view s) {
            return next_cut(s);
        }

    private:
        std::unordered_map<std::string_view, size_t> memo;
        std::unordered_map<std::string_view, bool> is_palindrome_memo;

        bool is_palindrome(const std::string_view &str, int64_t start, int64_t stop) {
            if (is_palindrome_memo.contains(str.substr(start, stop + 1))) return is_palindrome_memo[str.substr(start, stop + 1)];
            auto& res = is_palindrome_memo[str.substr(start, stop + 1)];
            while (start <= stop) {
                if (str[start++] != str[stop--]) return res = false;
            }
            return res = true;
        }

        size_t next_cut(std::string_view str) {
            if (memo.contains(str)) {
                return memo[str];
            }

            if (is_palindrome(str, 0, str.size() - 1)) {
                return memo[str] = 0;
            }

            size_t ans = -1;
            for (int64_t stop_index = 0; stop_index < str.size(); ++stop_index) {
                if (is_palindrome(str, 0, stop_index)) {
                    ans = std::min(ans, 1 + next_cut(str.substr(stop_index + 1)));
                }
            }

            return memo[str] = ans;
        }
    };

    template<>
    size_t exercise<exercise_name>(std::string s) {
        return solver().min_cut(s);
    }

    std::vector<std::pair<std::string, size_t>> actual_test_cases;

    template<>
    void prepare_test_cases<exercise_name>() {
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

    template<>
    double test_cases<exercise_name>() {
        double success = 0;

        for (auto [str, expected_result] : actual_test_cases) {
            success += check_if_same(str, exercise<exercise_name, size_t>(str), expected_result);
        }

        return success / (double)actual_test_cases.size();
    }
}