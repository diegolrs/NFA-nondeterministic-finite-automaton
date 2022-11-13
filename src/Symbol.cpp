#include "Symbol.hpp"

//const std::string Symbol::EPSILON = "epsilon";

Symbol::Symbol()
{
    _value = "batata";
    //_value = Symbol::EPSILON;
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