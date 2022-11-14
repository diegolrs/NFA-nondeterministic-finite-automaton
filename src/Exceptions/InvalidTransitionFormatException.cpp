#include "InvalidTransitionFormatException.hpp"

InvalidTransitionFormatException::InvalidTransitionFormatException(Transition_ReadedData invalidData)
{
    _invalidData = invalidData;
}

std::string InvalidTransitionFormatException::GetMessage()
{ 
    return "Invalid transition format for initial state: " + _invalidData.initialState
            + " transition symbol:" +_invalidData.transitionSymbol
            + " and destin state:" + _invalidData.destinState;
}