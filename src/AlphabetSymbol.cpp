#include "AlphabetSymbol.hpp"
#include "DFA_FileReader.hpp"

AlphabetSymbol::AlphabetSymbol()
{
    _value = DFA_FileReader::EPSILON_FILE_TAG;
}

AlphabetSymbol::AlphabetSymbol(std::string value)
{
    _value = value;
}

std::string AlphabetSymbol::GetValue()
{
    return _value;
}

bool AlphabetSymbol::IsEpsilon(AlphabetSymbol s)
{
    return _value == DFA_FileReader::EPSILON_FILE_TAG;
}

bool AlphabetSymbol::IsEquals(AlphabetSymbol s)
{
    return _value == s.GetValue();
}

bool AlphabetSymbol::operator==(AlphabetSymbol other)
{
    return (this->GetValue() == other.GetValue());
}