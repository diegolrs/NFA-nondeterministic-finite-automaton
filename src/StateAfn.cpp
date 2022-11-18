#include "StateAfn.hpp"

StateAfn::StateAfn(State* current)
{
    curState = current;
    lastStates = std::vector<std::string>(); // MyList<std::string>();
}

StateAfn::StateAfn(State* current, MyList<std::string> chain)
{
    curState = current;
    lastStates = std::vector<std::string>();//MyList<std::string>();
    
    for(int i = 0; i < chain.Length(); i++)
        lastStates.push_back(chain.At(i));
}

StateAfn::StateAfn(State* current, std::vector<std::string> chain)
{
    curState = current;
    lastStates = std::vector<std::string>();//MyList<std::string>();
    
    for(int i = 0; i < chain.size(); i++)
        lastStates.push_back(chain.at(i));
}


State* StateAfn::getCState(){
    return curState;
}

//MyList<std::string> StateAfn::getLastStates(){
std::vector<std::string> StateAfn::getLastStates(){

    return lastStates;
}

void StateAfn::addProcessAfn(std::string msg/*State* current, Transition* transition*/){
    lastStates.push_back(msg);
}

bool StateAfn::IsEquals(StateAfn state)
{
    return this->curState->IsEquals(state.curState);
}

bool StateAfn::IsEquals(StateAfn* state)
{
    return this->curState->IsEquals(state->curState);
}