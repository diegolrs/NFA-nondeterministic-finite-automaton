#pragma once
#include "Utils/MyList.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include <iostream>

class NFA_Chain
{
    public:
        NFA_Chain();
        NFA_Chain(State* current, Transition* transition);
        State* GetCurrent();
        Transition* GetTransition();
    private:
        State* _current;
        Transition* _transition;
};