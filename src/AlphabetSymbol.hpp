#pragma once

#include <string>

class AlphabetSymbol
{
    public:
        AlphabetSymbol();
        AlphabetSymbol(std::string value);
        std::string GetValue();
        bool IsEpsilon(AlphabetSymbol s);

        bool IsEquals(AlphabetSymbol s);
        bool operator==(AlphabetSymbol other);
    private:
        std::string _value;
};