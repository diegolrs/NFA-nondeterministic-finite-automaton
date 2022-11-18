#include "NFA_Chain.hpp"

NFA_Chain::NFA_Chain()
{
    _current = nullptr;
    _transition = nullptr;
}

NFA_Chain::NFA_Chain(State* current, Transition* transition)
{
    _current = current;
    _transition = transition;
}

State* NFA_Chain::GetCurrent()
{
    return _current;
}

Transition* NFA_Chain::GetTransition()
{
    return _transition;
}