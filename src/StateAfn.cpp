#include "StateAfn.hpp"

StateAfn::StateAfn(State* current){
    cState = current;
    lastStates = new MyList<std::string>();
}

State* StateAfn::getCState(){
    return cState;
}
MyList<std::string>* StateAfn::getLastStates(){
    return lastStates;
}

void StateAfn::addProcessAfn(std::string msg/*State* current, Transition* transition*/){
    lastStates->Push(msg);
}
