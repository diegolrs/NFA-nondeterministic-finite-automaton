#include "State.hpp"

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

std::string State::GetTransitionsStr()
{
    std::string s = "";

    for(int i = 0; i < _transitions->Length(); i++)
    {
        s += this->GetName() + "->";
        s += _transitions->At(i)->GetTransitionSymbol()->GetValue() + "->";
        s += _transitions->At(i)->GetDestinationState()->GetName() + '\n';
    }

    return s;
}

bool State::IsAFinalState()
{
    return _isAFinalState;
}

void State::SetAsFinalState(bool value)
{
    _isAFinalState = value;
}

bool State::operator==(State other)
{
    return this->GetName() == other.GetName();
}

bool State::operator==(State* other)
{
    std::string s1 = GetName();
    std::string s2 = other->GetName();

    return s1 == s2;
}