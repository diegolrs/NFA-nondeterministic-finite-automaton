#include "Symbol.hpp"

Symbol::Symbol()
{
    _value = EPSILON;
}

Symbol::Symbol(std::string value)
{
    _value = value;
}

std::string Symbol::GetValue()
{
    return _value;
}

bool Symbol::IsEquals(Symbol s)
{
    return _value == s.GetValue();
}