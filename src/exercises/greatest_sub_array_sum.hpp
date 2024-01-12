#include "../exercise.hpp"

namespace leet_code {

    template<>
    class exercise_impl<"greatest_sub_array_sum"> : public exercise_base {
    public:
        int64_t exercise(std::span<int32_t> array) {
            int64_t greatest_sum = array[0];
            int64_t current_sum = array[0];

            size_t i = 0;
            int32_t current_num = array[i];
            while (current_num < 0 && i < array.size() - 1) {
                current_num = array[++i];
                greatest_sum = std::max((int32_t)greatest_sum, current_num);
            }

            if (current_num < 0) return greatest_sum;

            current_sum = current_num;

            ++i;
            for (; i < array.size(); ++i) {
                current_num = array[i];
                current_sum = std::max(current_num, (int32_t)current_sum + current_num);
                greatest_sum = std::max(current_sum, greatest_sum);
            }

            return greatest_sum;
        }

        std::vector<std::pair<std::vector<int32_t>, int64_t>> actual_test_cases;

        void prepare_test_cases() {
            actual_test_cases.emplace_back(std::vector{-2,1,2,1,-5,-4,-6,-3,1,2,3,5}, 11l);
            actual_test_cases.emplace_back(std::vector{1, 1, 1, 1}, 4l);
            actual_test_cases.emplace_back(std::vector{1, 1, -1, 1}, 2l);
            actual_test_cases.emplace_back(std::vector{1, 1, -1, 4}, 5l);
            actual_test_cases.emplace_back(std::vector{-100, 1, -1, 4}, 4l);
            actual_test_cases.emplace_back(std::vector{-100, -2, -5, -3}, -2l);
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