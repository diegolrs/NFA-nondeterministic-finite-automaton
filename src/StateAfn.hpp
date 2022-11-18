#pragma once

#include <string>
#include "Utils/MyList.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include <iostream>
#include <vector>

class StateAfn
{
private:
    State *curState;
    //MyList<std::string> lastStates; 
    std::vector<std::string> lastStates; 
public:
    StateAfn(State* current);
    StateAfn(State* current, MyList<std::string> chain);
    StateAfn(State* current, std::vector<std::string> chain);
    State* getCState();
    //MyList<std::string> getLastStates();
    std::vector<std::string> getLastStates();
    void addProcessAfn(std::string msg);
    bool IsEquals(StateAfn state);
    bool IsEquals(StateAfn* state);
};


