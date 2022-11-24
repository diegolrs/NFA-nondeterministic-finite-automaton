#include "AlphabetSymbol.hpp"
#include "NFA_FileReader.hpp"

AlphabetSymbol::AlphabetSymbol()
{
    _value = NFA_FileReader::EPSILON_FILE_TAG;
}

AlphabetSymbol::AlphabetSymbol(std::string value)
{
    _value = value;
}

std::string AlphabetSymbol::GetValue()
{
    return _value;
}

bool AlphabetSymbol::IsEpsilon()
{
    return _value == NFA_FileReader::EPSILON_FILE_TAG;
}

bool AlphabetSymbol::IsEquals(AlphabetSymbol s)
{
    return _value == s.GetValue();
}

bool AlphabetSymbol::IsEquals(AlphabetSymbol* s)
{
    return _value == s->GetValue();
}

bool AlphabetSymbol::operator==(AlphabetSymbol other)
{
    return (this->GetValue() == other.GetValue());
}