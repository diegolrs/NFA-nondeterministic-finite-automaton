#include "State.h"

State::State()
{
    _name = "not defined";
    _isAFinalState = false;
    _transitions = new MyList<Transition*>();
}

State::State(std::string name, bool isAFinalState)
{
    _name = name;
    _isAFinalState = isAFinalState;
    _transitions = new MyList<Transition*>();
}

std::string State::GetName()
{
    return _name;
}

void State::AddTransition(Transition* t)
{
    _transitions->Push(t);
}

void State::ListTransitions()
{
    for(int i = 0; i < _transitions->Length(); i++)
    {
        std::cout << this->GetName() << " -> ";
        std::cout << _transitions->At(i)->GetTransitionSymbol()->GetValue() << " -> ";
        std::cout << _transitions->At(i)->GetDestinationState()->GetName() << std::endl;
    }
}

bool State::IsAFinalState()
{
    return _isAFinalState;
}