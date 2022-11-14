#pragma once

#include <string>

class Symbol
{
    public:
        //static const std::string EPSILON;

        Symbol();
        Symbol(std::string value);
        std::string GetValue();
        bool IsEquals(Symbol s);

        bool operator==(Symbol other);
    private:
        std::string _value;
};