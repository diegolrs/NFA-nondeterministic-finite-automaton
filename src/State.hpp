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
        void ListTransitions();
        bool IsAFinalState();
    private:
        std::string _name;
        bool _isAFinalState;
        MyList<Transition*>* _transitions;
};