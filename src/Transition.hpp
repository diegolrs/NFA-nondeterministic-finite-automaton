#pragma once

#include <iostream>
#include <string>
#include "AlphabetSymbol.hpp"
#include "State.fwd.hpp"
#include "Transition.fwd.hpp"

class Transition
{
    public:
        Transition();
        Transition(State* destin, AlphabetSymbol* transitionSymbol);
        AlphabetSymbol* GetTransitionSymbol();
        State* GetDestinationState();
    private:
        State* _destin;
        AlphabetSymbol* _transitionSymbol;
};