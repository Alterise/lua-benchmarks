#pragma once

#include <string>
#include <iostream>
#include <utility>

const int loop_count = 1'000'000;

class A {
public:
    A(int digit, std::string  text) : text_(std::move(text)), digit_(digit), publicDigit(digit) {}

    void print() {
        std::cout << text_;
    }

    std::string getText() const {
        return text_;
    }

    int getDigit() const {
        return digit_;
    }

    void increment() {
        digit_++;
    }

    int publicDigit;
private:
    std::string text_;
protected:
    int digit_;
};

class B : public A {
public:
    B(int digit, std::string text) : A(digit, std::move(text)) {}

    void increment() {
        digit_ += 2;
    }
};

class C : public A {
public:
    C(int digit, std::string text) : A(digit, std::move(text)) {}
};