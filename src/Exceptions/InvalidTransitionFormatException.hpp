#pragma once
#include "Exception.hpp"
#include "../DFA_ReadedData.hpp"

class InvalidTransitionFormatException : Exception
{
    public:
        InvalidTransitionFormatException(Transition_ReadedData invalidData);
        std::string GetMessage();
    private:
        Transition_ReadedData _invalidData;
};