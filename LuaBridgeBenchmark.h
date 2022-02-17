#pragma once

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <limits>
#include <cassert>
#include <LuaBridge/LuaBridge.h>

#include "functions.h"
#include "utils.h"

#include <iostream>

void performStandaloneBenchmark(const std::string &name, lua_State *L, int) {
    auto s = std::chrono::steady_clock::now();
    luabridge::pcall(L);
    auto e = std::chrono::steady_clock::now();
    printElapsedTime(name, s, e, false);
}

void LUABRIDGE_performBenchmark() {
    std::cout << "Performing LuaBridge3 Benchmark:" << std::endl;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luabridge::setGlobal(L, loop_count , "loop_count");
    luabridge::getGlobalNamespace(L)
            .addFunction("increment", increment)
            .addFunction("string_argument", string_argument)
            .addFunction("string_const_argument", string_const_argument)
            .addFunction("string_view_argument", string_view_argument)
            .addFunction("string_char_argument", string_char_argument)
            .addFunction("string_iterator", string_iterator)
            .addFunction("string_const_iterator", string_const_iterator)
            .addFunction("string_view_iterator", string_view_iterator)
            .addFunction("string_char_iterator", string_char_iterator);

    std::vector<std::string> nums{"1", "12","123","1234","12345","123456","1234567","12345678","123456789","1234567890",
                                  "12345678909","123456789098","1234567890987","12345678909876","123456789098765",
                                  "1234567890987654","12345678909876543","123456789098765432", "1234567890987654321", "12345678909876543210"};

    auto s = std::chrono::steady_clock::now();
    auto e = std::chrono::steady_clock::now();

    luaL_dofile(L, "LuaScripts/functions.lua");

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("Increment (Lua)", L, luaL_loadfile(L, "LuaScripts/Increment.lua"));

    luabridge::LuaRef increment2 = luabridge::getGlobal(L, "increment2");
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        auto r = increment2(i);
        assert(r.size() == 1);
        assert(r[0] == i+1);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("Increment (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Argument (Lua)", L, luaL_loadfile(L, "LuaScripts/StringArgument.lua"));

//    luabridge::setGlobal(L, nums, "nums");
    luabridge::LuaRef string_argument2 = luabridge::getGlobal(L, "string_argument2");
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(nums[i % 20], nums[19 - i % 20]);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Const Argument (Lua)", L, luaL_loadfile(L, "LuaScripts/StringConstArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(static_cast<const std::string>(nums[i % 20]), static_cast<const std::string>(nums[19 - i % 20]));
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Const Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String View Argument (Lua)", L, luaL_loadfile(L, "LuaScripts/StringViewArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(static_cast<std::string_view>(nums[i % 20]), static_cast<std::string_view>(nums[19 - i % 20]));
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String View Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Char Argument (Lua)", L, luaL_loadfile(L, "LuaScripts/StringCharArgument.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_argument2(nums[i % 20].c_str(), nums[19 - i % 20].c_str());
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Char Argument (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Iterator (Lua)", L, luaL_loadfile(L, "LuaScripts/StringIterator.lua"));

    luabridge::LuaRef string_iterator2 = luabridge::getGlobal(L, "string_iterator2");
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(nums[i % 20], nums[19 - i % 20], i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Const Iterator (Lua)", L, luaL_loadfile(L, "LuaScripts/StringConstIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(static_cast<const std::string>(nums[i % 20]), static_cast<const std::string>(nums[19 - i % 20]), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Const Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String View Iterator (Lua)", L, luaL_loadfile(L, "LuaScripts/StringViewIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(static_cast<std::string_view>(nums[i % 20]), static_cast<std::string_view>(nums[19 - i % 20]), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String View Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Char Iterator (Lua)", L, luaL_loadfile(L, "LuaScripts/StringCharIterator.lua"));

    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        string_iterator2(nums[i % 20].c_str(), nums[19 - i % 20].c_str(), i);
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("String Char Iterator (C++)", s, e);


    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    performStandaloneBenchmark("String Internal Iterator (Lua)", L,
                               luaL_loadfile(L, "LuaScripts/StringInternalIterator.lua"));
    std::cout << std::endl;

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    luabridge::getGlobalNamespace (L)
            .beginNamespace ("classes")
            .beginClass <A> ("A")
            .addConstructor<void (*) (int, std::string)>()
            .addFunction("print", &A::print)
            .addFunction("getText", &A::getText)
            .addFunction("getDigit", &A::getDigit)
            .addFunction("increment", &A::increment)
            .addProperty("publicDigit", &A::publicDigit)
            .endClass()
            .deriveClass <B, A>("B")
            .addConstructor<void (*) (int, std::string)>()
            .addFunction("increment", &B::increment)
            .endClass()
            .deriveClass <C, A>("C")
            .addConstructor<void (*) (int, std::string)>()
            .endClass()
            .endNamespace();

    A A1(5, "AAA");
    auto _G = luabridge::getGlobal(L, "_G");
    _G["A1"] = &A1;
    auto pass_class = [&A1](const A* a) {
        assert(a == &A1);
    };

    luabridge::getGlobalNamespace(L)
            .addFunction("pass_class", pass_class);

    performStandaloneBenchmark("Class passing (Lua)", L,
                               luaL_loadfile(L, "LuaScripts/PassClass.lua"));

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    luabridge::LuaRef pass_class2 = luabridge::getGlobal(L, "pass_class2");
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
    luabridge::getGlobalNamespace(L)
            .addFunction("get_class", get_class);

    performStandaloneBenchmark("Class Getting (Lua)", L,
                               luaL_loadfile(L, "LuaScripts/GetClass.lua"));

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    luabridge::LuaRef get_class2 = luabridge::getGlobal(L, "get_class2");
    s = std::chrono::steady_clock::now();
    for (int i = 0; i < loop_count; ++i) {
        get_class2();
    }
    e = std::chrono::steady_clock::now();
    printElapsedTime("Class Getting (C++)", s, e);

    //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// //// ////
    B B1(3, "BBB");
    luabridge::setGlobal(L, &B1, "B1");
    C C1(7, "CCC");
    luabridge::setGlobal(L, &C1, "C1");

    performStandaloneBenchmark("Class method call (Base Class)", L, luaL_loadfile(L,"LuaScripts/MethodCallA.lua"));
    performStandaloneBenchmark("Class method call (Derived Overwritten Class)", L, luaL_loadfile(L,"LuaScripts/MethodCallB.lua"));
    performStandaloneBenchmark("Class method call (Derived Not Overwritten Class)", L, luaL_loadfile(L,"LuaScripts/MethodCallC.lua"));
    std::cout << std::endl;
    performStandaloneBenchmark("Class field access (Base Class)", L, luaL_loadfile(L,"LuaScripts/FieldAccessA.lua"));
    performStandaloneBenchmark("Class field access (Derived Class)", L, luaL_loadfile(L,"LuaScripts/FieldAccessB.lua"));
}
