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

        void ProcessSymbol(AlphabetSymbol sim, int iterationIndex);
        void ProcessEpsilon(int iterationIndex);
        NaryTree<Transition*>* StartProcessment();

        NaryTree<Transition*>* GetChain();
    private:
        const std::string CRASH_STATUS_NAME = "CRASH";
        const std::string CHAIN_IS_ACCEPTED_MSG = "A cadeia processada eh aceita. \n";
        const std::string CHAIN_IS_NOT_ACCEPTED_MSG = "A cadeia processada nao eh aceita. \n";

        MyList<AlphabetSymbol*>* alphabet; // All alphabet symbols
        MyList<State*>* states; // All states
        MyList<Transition*>* transitions; // All states transitions 

        State* initialState;
        State* crashState;
        NaryTree<Transition*>* processmentTree; // Process tree that will be generated while processing
        
        bool IsACurrentState(State* s);
        bool ContainsState(State* s);
        int IndexOfState(State* s);
        int IndexOfSymbol(AlphabetSymbol* s);
};