#pragma once

#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <list>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <unordered_set>
#include <queue>
#include "fixed_string.hpp"
#include "time.hpp"

namespace leet_code {

    template<fixed_string Name, typename ResT = void, typename ...Args>
    ResT exercise(Args ...args) {
        throw std::runtime_error("Unimplemented");
    }

    template<fixed_string Name>
    void prepare_test_cases() {
        std::cout << "No prepare test cases are defined for this exercise\n";
    }

    template<fixed_string Name>
    double test_cases() {
        std::cout << "No test cases are defined for this exercise\n";
        return 100;
    }

    template<fixed_string Name>
    void run_test_cases() {
        prepare_test_cases<Name>();
        auto start_time = std::chrono::high_resolution_clock::now();
        double res = test_cases<Name>();
        auto stop_time = std::chrono::high_resolution_clock::now();
        std::cout << "Success percentages: " << res * 100 << "%\n";
        std::cout << "Computation time: ";
        pretty_time_print(start_time, stop_time);
        std::cout << std::endl;
    }

    template<fixed_string Name, typename ResT = void, typename ...Args>
    void run_exercise(Args ...args) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto res = exercise<Name, ResT, Args...>(args...);
        auto stop_time = std::chrono::high_resolution_clock::now();
        std::cout << res << "\n";
        std::cout << "Computation time: ";
        pretty_time_print(start_time, stop_time);
        std::cout << std::endl;
    }

    template<typename ResT>
    bool check_if_same(auto param, ResT actual, ResT expected) {
        if (actual == expected) return true;
        std::cout << "Param: " << param << " Actual: " << actual << " Expected: " << expected << "\n";
        return false;
    }
}