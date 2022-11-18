#pragma once

#include <iostream>
#include "DFA_ReadedData.hpp"
#include "Exceptions/NFA_Exceptions.hpp"

#include "AlphabetSymbol.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "StateAfn.hpp"
#include "NFA_Chain.hpp"

//Deterministic Finite Automaton Machine
class DFA_Machine
{
    public:
        DFA_Machine(DFA_ReadedData data);
        std::string ToString();

        std::string GetProcessChain();
        bool IsOnFinalState();
        void ProcessSymbol(AlphabetSymbol sim);
        void ProcessEpsilon();
    private:
        const std::string TRAP_STATE_NAME = "Trap State";
        const std::string CRASH_STATUS_NAME = "CRASH";

        MyList<AlphabetSymbol*>* alphabet;
        MyList<State*>* states;

        State* initialState;
        MyList<StateAfn*>* currentState; 
        StateAfn* trapState;

        MyList<Transition*>* transitions;
        
        bool ContainsState(State* s);
        int IndexOfState(State* s);
        int IndexOfSymbol(AlphabetSymbol* s);
};