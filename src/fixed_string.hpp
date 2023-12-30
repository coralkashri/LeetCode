#pragma once

#include <algorithm>
#include <compare>
#include <string>

template <size_t Size>
class fixed_string {
public:
    constexpr fixed_string(char const (&chars)[Size + 1]) {
        std::copy_n(chars, Size, data.data());
        data.back() = 0;
    }

    constexpr std::strong_ordering operator<=>(fixed_string const&) const = default;

    constexpr std::array<char, Size + 1> get() const {
        return data;
    }

    std::array<char, Size + 1> data;
};

template<unsigned N> fixed_string(char const (&)[N]) -> fixed_string<N - 1>;