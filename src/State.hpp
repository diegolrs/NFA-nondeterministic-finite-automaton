#pragma once

#include <string>
#include "Utils/MyList.hpp"
#include "State.fwd.hpp"
#include "Transition.hpp"
#include <vector>
#include <iostream>

class State
{
    public:
        State();
        State(std::string name, bool isAFinalState=false);
        std::string GetName();
        void AddTransition(Transition* t);
        std::string ToString();

        bool IsAFinalState();
        bool IsEquals(State other);
        bool IsEquals(State* other);

        bool CanProcessSymbol(AlphabetSymbol s);
        bool CanProcessSymbol(AlphabetSymbol* s);

        MyList<State*> ProcessSymbol(AlphabetSymbol s);
        MyList<State*> ProcessSymbol(AlphabetSymbol* s);
    private:
        std::string _name;
        bool _isAFinalState;
        MyList<Transition*>* _transitions;      
};