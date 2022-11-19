#include "StateAfn.hpp"

StateAfn::StateAfn(State* current)
{
    curState = current;
    processChain = MyList<NFA_Chain>();
}

StateAfn::StateAfn(State* current, MyList<NFA_Chain> chain)
{
    curState = current;
    processChain = MyList<NFA_Chain>();
    
    for(int i = 0; i < chain.Length(); i++)
    {
        NFA_Chain _tmp = NFA_Chain(chain.At(0).GetCurrent(), chain.At(0).GetTransition());
        processChain.Push(_tmp);
    } 
}

State* StateAfn::getCurState(){
    return curState;
}

MyList<NFA_Chain> StateAfn::GetProcessChain()
{
    return processChain;
}

void StateAfn::AddProcessChain(NFA_Chain value)
{
    processChain.Push(value);
}

bool StateAfn::IsEquals(StateAfn state)
{
    return this->curState->IsEquals(state.curState);
}

bool StateAfn::IsEquals(StateAfn* state)
{
    return this->curState->IsEquals(state->curState);
}