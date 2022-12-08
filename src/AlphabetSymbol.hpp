#pragma once

#include <string>

class AlphabetSymbol
{
    public:
        AlphabetSymbol(); // Start as epsilon
        AlphabetSymbol(std::string value); // Start as a value

        std::string GetValue();
        
        bool IsEpsilon();
        bool IsEquals(AlphabetSymbol s);
        bool IsEquals(AlphabetSymbol* s);
    private:
        std::string _value;
};