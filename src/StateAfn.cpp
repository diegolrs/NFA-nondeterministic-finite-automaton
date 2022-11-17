#include "StateAfn.hpp"

StateAfn::StateAfn(State* current)
{
    curState = current;
    lastStates =  MyList<std::string>();
}

StateAfn::StateAfn(State* current, MyList<std::string> chain)
{
    curState = current;
    lastStates = MyList<std::string>();
    
    // for(int i = 0; i < chain.Length(); i++)
    //     lastStates.Push(chain.At(i));
}

State* StateAfn::getCState(){
    return curState;
}

MyList<std::string> StateAfn::getLastStates(){
    return lastStates;
}

void StateAfn::addProcessAfn(std::string msg/*State* current, Transition* transition*/){
    //lastStates.Push(msg);
}

bool StateAfn::IsEquals(StateAfn state)
{
    return this->curState->IsEquals(state.curState);
}

bool StateAfn::IsEquals(StateAfn* state)
{
    return this->curState->IsEquals(state->curState);
}