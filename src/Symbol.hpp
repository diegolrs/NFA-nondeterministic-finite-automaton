#pragma once

#include <string>

struct Symbol
{
    public:
        const std::string EPSILON = "epsilon";

        Symbol();
        Symbol(std::string value);
        std::string GetValue();
        bool IsEquals(Symbol s);
    private:
        std::string _value;
};