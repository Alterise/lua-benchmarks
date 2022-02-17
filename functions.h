#pragma once
#include <string>
#include <chrono>
#include "utils.h"

auto increment = [](int val) {
    return val + 1;
};

// auto string_argument = [](std::string s1, std::string s2) {
//     auto s = s1[0] + s2[0];
// };

void string_argument(std::string s1, std::string s2) {
    auto s = s1[0] + s2[0];
}

auto string_const_argument = [](const std::string &s1, const std::string &s2) {
    auto s = s1[0] + s2[0];
};

auto string_view_argument = [](const std::string_view &s1, const std::string_view &s2) {
    auto s = s1[0] + s2[0];
};

auto string_char_argument = [](const char *s1, const char *s2) {
    auto s = s1[0] + s2[0];
};

auto string_iterator = [](std::string s1, std::string s2, int count) {
    return (count % 2 ? s1 : s2);
};

auto string_const_iterator = [](const std::string &s1, const std::string &s2, int count) {
    return (count % 2 ? s1 : s2);
};

auto string_view_iterator = [](const std::string_view &s1, const std::string_view &s2, int count) {
    return (count % 2 ? s1 : s2);
};

auto string_char_iterator = [](const char *s1, const char *s2, int count) {
    return (count % 2 ? s1 : s2);
};

template<typename T>
void printElapsedTime(const std::string &name, T s, T e, bool double_el = true) {
    std::cout << "Time elapsed (" << name << "): " << std::chrono::duration<double, std::milli>(e - s).count() << "ms"
              << std::endl;
    if (double_el) std::cout << std::endl;
}