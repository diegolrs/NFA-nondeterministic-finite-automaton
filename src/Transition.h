#pragma once

#include <iostream>
#include <string>
#include "Symbol.h"
#include "State.fwd.h"
#include "Transition.fwd.h"

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