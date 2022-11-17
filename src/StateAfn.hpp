#pragma once

#include <string>
#include "Utils/MyList.hpp"
#include "State.fwd.hpp"
#include "Transition.hpp"

class StateAfn
{
private:
    State *cState;
    MyList<std::string> *lastStates; 
public:
    StateAfn(State* current);
    State* getCState();
    MyList<std::string>* getLastStates();
    void addProcessAfn(std::string msg);
};


