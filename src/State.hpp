#pragma once

#include <string>
#include "Utils/MyList.hpp"
#include "State.fwd.hpp"
#include "Transition.hpp"

class State
{
    public:
        State();
        State(std::string name, bool isAFinalState=false);
        std::string GetName();
        void AddTransition(Transition* t);
        std::string GetTransitionsStr();

        bool IsAFinalState();

        bool operator==(State other);
        bool operator==(State* other);

        bool CanProcessSymbol(AlphabetSymbol s);
        MyList<State*> ProcessSymbol(AlphabetSymbol s);
        State* ProcessEpsilon();
    private:
        std::string _name;
        bool _isAFinalState;
        MyList<Transition*>* _transitions;
        
};