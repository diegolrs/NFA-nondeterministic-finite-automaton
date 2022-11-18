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
    //MyList<std::string> lastStates; 
    //std::vector<std::string> lastStates; 
    MyList<NFA_Chain> processChain;
public:
    StateAfn(State* current);
    // StateAfn(State* current, MyList<std::string> chain);
    // StateAfn(State* current, std::vector<std::string> chain);
    StateAfn(State* current, MyList<NFA_Chain> chain);
    State* getCurState();
    //MyList<std::string> getLastStates();
    //std::vector<std::string> getLastStates();
    MyList<NFA_Chain> GetProcessChain();
    //void addProcessAfn(std::string msg);
    void AddProcessChain(NFA_Chain chain);
    bool IsEquals(StateAfn state);
    bool IsEquals(StateAfn* state);
};


