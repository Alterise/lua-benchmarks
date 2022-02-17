#pragma once

#include <iostream>

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>

#include "functions.h"
#include "utils.h"

void performStandaloneBenchmark(const std::string &name, sol::load_result func) {
    auto s = std::chrono::steady_clock::now();
    auto e = std::chrono::steady_clock::now();
    s = std::chrono::steady_clock::now();
    func();
    e = std::chrono::steady_clock::now();
    printElapsedTime(name, s, e, false);
}

void SOL_performBenchmark() {
    std::cout << "Performing Sol3 Benchmark:" << std::endl;
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string);
    lua["loop_count"] = loop_count;
    lua.set_function("increment", increment);
    lua.set_function("string_argument", string_argument);
    lua.set_function("string_const_argument", string_const_argument);
    lua.set_function("string_view_argument", string_view_argument);
    lua.set_function("string_char_argument", string_char_argument);
    lua.set_function("string_iterator", string_iterator);
    lua.set_function("string_const_iterator", string_const_iterator);
    lua.set_function("string_view_iterator", string_view_iterator);
    lua.set_function("string_char_iterator", string_char_iterator);

    std::vector<std::string> nums{"1", "12","123","1234","12345","123456","1234567","12345678","123456789","1234567890",
                                  "12345678909","123456789098","1234567890987","12345678909876","123456789098765",
                                  "1234567890987654","12345678909876543","123456789098765432", "1234567890987654321", "12345678909876543210"};

    auto s = std::chrono::steady_clock::now();
    auto e = std::chrono::steady_clock::now();

    lua.do_file("LuaScripts/functions.lua");

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("Increment (Lua)", lua.load_file("LuaScripts/Increment.lua"));

    sol::protected_function increment2 = lua["increment2"];
    int x = 0;
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        x = increment2(x);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("Increment (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Argument (Lua)", lua.load_file("LuaScripts/StringArgument.lua"));

    sol::protected_function string_argument2 = lua["string_argument2"];
    s = std::chrono::steady_clock::now();
    lua["nums"] = nums;
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(nums[i % 20], nums[19 - i % 20]);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Const Argument (Lua)", lua.load_file("LuaScripts/StringConstArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(static_cast<const std::string>(nums[i % 20]), static_cast<const std::string>(nums[19 - i % 20]));
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Const Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String View Argument (Lua)", lua.load_file("LuaScripts/StringViewArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(static_cast<std::string_view>(nums[i % 20]), static_cast<std::string_view>(nums[19 - i % 20]));
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String View Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Char Argument (Lua)", lua.load_file("LuaScripts/StringCharArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(nums[i % 20].c_str(), nums[19 - i % 20].c_str());
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Char Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Iterator (Lua)", lua.load_file("LuaScripts/StringIterator.lua"));

    sol::protected_function string_iterator2 = lua["string_iterator2"];
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(nums[i % 20], nums[19 - i % 20], i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Const Iterator (Lua)", lua.load_file("LuaScripts/StringConstIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(static_cast<const std::string>(nums[i % 20]), static_cast<const std::string>(nums[19 - i % 20]), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Const Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String View Iterator (Lua)", lua.load_file("LuaScripts/StringViewIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(static_cast<std::string_view>(nums[i % 20]), static_cast<std::string_view>(nums[19 - i % 20]), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String View Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Char Iterator (Lua)", lua.load_file("LuaScripts/StringCharIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(nums[i % 20].c_str(), nums[19 - i % 20].c_str(), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Char Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Internal Iterator (Lua)", lua.load_file("LuaScripts/StringInternalIterator.lua"));
    std::cout << std::endl;

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    auto classes = lua["classes"].get_or_create<sol::table>();
    classes.new_usertype<A>("A", sol::constructors<A(int, std::string)>(),
                                "print", &A::print,
                                "getText", &A::getText,
                                "getDigit", &A::getDigit,
                                "increment", &A::increment,
                                "publicDigit", &A::publicDigit
                                );

    classes.new_usertype<B>("B", sol::constructors<B(int, std::string)>(),
                                sol::base_classes, sol::bases<A>(),
                               "increment", &B::increment
    );

    classes.new_usertype<C>("C", sol::constructors<B(int, std::string)>(),
                            sol::base_classes, sol::bases<A>()
    );


    A A1(5, "AAA");
    lua["A1"] = &A1;
    auto pass_class = [&A1](const A& a) {
        assert(&a == &A1);
    };
    lua.set_function("pass_class", pass_class);

    performStandaloneBenchmark("Class passing (Lua)", lua.load_file("LuaScripts/PassClass.lua"));

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    sol::protected_function pass_class2 = lua["pass_class2"];
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        pass_class2(&A1);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("Class Passing (C++)", s, e);

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    auto get_class = [&A1]() {
        return A1;
    };
    lua.set_function("get_class", get_class);

    performStandaloneBenchmark("Class Getting (Lua)", lua.load_file("LuaScripts/GetClass.lua"));

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    sol::protected_function get_class2 = lua["get_class2"];
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        get_class2();
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("Class Getting (C++)", s, e);

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    B B1(3, "BBB");
    lua["B1"] = &B1;
    C C1(7, "CCC");
    lua["C1"] = &C1;

    performStandaloneBenchmark("Class method call (Base Class)", lua.load_file("LuaScripts/MethodCallA.lua"));
    performStandaloneBenchmark("Class method call (Derived Overwritten Class)", lua.load_file("LuaScripts/MethodCallB.lua"));
    performStandaloneBenchmark("Class method call (Derived Not Overwritten Class)", lua.load_file("LuaScripts/MethodCallC.lua"));
    std::cout << std::endl;
    performStandaloneBenchmark("Class field access (Base Class)", lua.load_file("LuaScripts/FieldAccessA.lua"));
    performStandaloneBenchmark("Class field access (Derived Class)", lua.load_file("LuaScripts/FieldAccessB.lua"));
}
