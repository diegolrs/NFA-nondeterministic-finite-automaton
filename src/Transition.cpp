#include "Transition.hpp"

Transition::Transition()
{
    this->_destin = nullptr;
    this->_transitionSymbol = nullptr;
}


Transition::Transition(State* destin, Symbol* transitionSymbol)
{
    this->_destin = destin;
    this->_transitionSymbol = transitionSymbol;
}

Symbol* Transition::GetTransitionSymbol()
{
    return this->_transitionSymbol;
}

State* Transition::GetDestinationState()
{
    return this->_destin;
}