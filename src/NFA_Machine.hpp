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
        NaryTree<Transition*>* StartProcessment(NFA_Machine* machine, MyList<AlphabetSymbol> *chain);
    private:
        const std::string CRASH_STATUS_NAME = "CRASH";

        State* initialState;
        State* crashState;
        MyList<AlphabetSymbol*>* alphabet; // All alphabet symbols
        MyList<State*>* states; // All states
        MyList<Transition*>* transitions; // All states transitions 
        
        bool IsACurrentState(State* s, NaryTree<Transition*>* processmentTree);
        bool ContainsState(State* s);
        int IndexOfState(State* s);
        int IndexOfSymbol(AlphabetSymbol* s);

        void ProcessSymbol(AlphabetSymbol sim, int iterationIndex, NaryTree<Transition*>* processmentTree);
        void ProcessEpsilon(int iterationInde, NaryTree<Transition*>* processmentTreex);
};