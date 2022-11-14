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
        void SetAsFinalState(bool value);

        bool operator==(State other);
        bool operator==(State* other);
    private:
        std::string _name;
        bool _isAFinalState;
        MyList<Transition*>* _transitions;
};