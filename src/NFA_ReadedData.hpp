#pragma once

#include <string>
#include "Utils/MyList.hpp"

//Transition data readed from file
struct Transition_ReadedData
{
    std::string initialState;
    std::string destinState;
    std::string transitionSymbol;
};

//Nondeterministic Finite Automaton data readed from file
struct NFA_ReadedData
{  
    MyList<std::string>* alphabet;
    MyList<std::string>* states;
    std::string initialState;
    MyList<std::string>* endStates;
    MyList<Transition_ReadedData>* transitions;
};