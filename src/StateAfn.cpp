#include "StateAfn.hpp"

StateAfn::StateAfn(State* current)
{
    curState = current;
    //lastStates = std::vector<std::string>(); // MyList<std::string>();
    processChain = MyList<NFA_Chain>();
}

// StateAfn::StateAfn(State* current, MyList<std::string> chain)
// {
//     curState = current;
//     lastStates = std::vector<std::string>();//MyList<std::string>();
    
//     for(int i = 0; i < chain.Length(); i++)
//         lastStates.push_back(chain.At(i));
// }

// StateAfn::StateAfn(State* current, std::vector<std::string> chain)
// {
//     curState = current;
//     lastStates = std::vector<std::string>();//MyList<std::string>();
    
//     for(int i = 0; i < chain.size(); i++)
//         lastStates.push_back(chain.at(i));
// }

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

//MyList<std::string> StateAfn::getLastStates(){
// std::vector<std::string> StateAfn::getLastStates(){

//     return lastStates;
// }

MyList<NFA_Chain> StateAfn::GetProcessChain()
{
    return processChain;
}

void StateAfn::AddProcessChain(NFA_Chain chain)
{
    processChain.Push(chain);
}

bool StateAfn::IsEquals(StateAfn state)
{
    return this->curState->IsEquals(state.curState);
}

bool StateAfn::IsEquals(StateAfn* state)
{
    return this->curState->IsEquals(state->curState);
}