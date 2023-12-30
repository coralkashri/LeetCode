#pragma once

#include "fixed_string.hpp"
#include "time.hpp"

namespace leet_code {

    template<fixed_string Name, typename ResT = void, typename ...Args>
    ResT exercise(Args ...args) {
        throw std::runtime_error("Unimplemented");
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
}