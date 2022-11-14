#pragma once

#include <iostream>
#include "DFA_ReadedData.hpp"
#include "Exceptions/NFA_Exceptions.hpp"

#include "Symbol.hpp"
#include "State.hpp"
#include "Transition.hpp"

//Deterministic Finite Automaton Machine
class DFA_Machine
{
    public:
        DFA_Machine(DFA_ReadedData data);
        std::string ToString();
        bool Process(Symbol sim);
        std::string PrintProcessChain();
        bool IsOnFinalState();
    private:
        MyList<Symbol*>* alphabet;
        MyList<State*>* states;
        State* initialState;
        State* currentState; 
        MyList<State*>* endStates;
        MyList<Transition*>* transitions;
        MyList<std::string>* processChain;
};