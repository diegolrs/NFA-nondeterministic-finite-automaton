#pragma once

#include <iostream>
#include "NFA_ReadedData.hpp"
#include "Exceptions/NFA_Exceptions.hpp"

#include "Utils/NaryTree.hpp"
#include "AlphabetSymbol.hpp"
#include "State.hpp"
#include "Transition.hpp"

//Deterministic Finite Automaton Machine
class NFA_Machine
{
    public:
        static const int CRASH_STATE_HEIGHT = -4; // altura para setar nos estados que deram crash

        NFA_Machine(NFA_ReadedData data);
        std::string ToString();

        bool IsOnFinalState();
        std::string GetEndOfProcessingMessage(MyList<State*> l);

        void ProcessSymbol(AlphabetSymbol sim, int iterationIndex, int maxIndex);
        void ProcessEpsilon(int iterationIndex, int maxIndex);

        NaryTree<Transition*>* GetChain();
    private:
        const std::string TRAP_STATE_NAME = "Trap State";
        const std::string CRASH_STATUS_NAME = "CRASH";
        const std::string CHAIN_IS_ACCEPTED_MSG = "A cadeia processada eh aceita. \n";
        const std::string CHAIN_IS_NOT_ACCEPTED_MSG = "A cadeia processada nao eh aceita. \n";

        MyList<AlphabetSymbol*>* alphabet;
        MyList<State*>* states;

        State* initialState;
        NaryTree<Transition*>* chain;
        State* crashState;

        MyList<Transition*>* transitions;
        
        bool IsACurrentState(State* s);
        bool ContainsState(State* s);
        int IndexOfState(State* s);
        int IndexOfSymbol(AlphabetSymbol* s);
};