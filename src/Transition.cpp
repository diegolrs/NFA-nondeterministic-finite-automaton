#include <iostream>
#include <string>
#include "Symbol.h"
#include "State.h"

class Transition
{
    public:
        Transition(State* current, State* next, Symbol* transitionSymbol)
        {
            _current = current;
            _next = next;
            _transitionSymbol = transitionSymbol;
        }
    private:
        State* _current;
        State* _next;
        Symbol* _transitionSymbol;
};