#pragma once

#include <string>
#include "Utils/MyList.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "NFA_Chain.hpp"
#include <iostream>
#include <vector>

class StateAfn
{
private:
    State *curState;
    MyList<NFA_Chain> processChain;
public:
    StateAfn(State* current);
    StateAfn(State* current, MyList<NFA_Chain> value);

    State* getCurState();
    MyList<NFA_Chain> GetProcessChain();
    void AddProcessChain(NFA_Chain value);

    bool IsEquals(StateAfn state);
    bool IsEquals(StateAfn* state);
};


