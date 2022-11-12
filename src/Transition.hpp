#pragma once

#include <iostream>
#include <string>
#include "Symbol.hpp"
#include "State.fwd.hpp"
#include "Transition.fwd.hpp"

class Transition
{
    public:
        Transition();
        Transition(State* destin, Symbol* transitionSymbol);
        Symbol* GetTransitionSymbol();
        State* GetDestinationState();
    private:
        State* _destin;
        Symbol* _transitionSymbol;
};