#include "DFA_Machine.hpp"

//Deterministic Finite Automaton Machine
DFA_Machine::DFA_Machine(DFA_ReadedData data)
{
    alphabet = new MyList<AlphabetSymbol*>();
    states = new MyList<State*>();      
    transitions = new MyList<Transition*>();
    trapState = new StateAfn(new State(TRAP_STATE_NAME));

    // Symbols
    for(int i = 0; i < data.alphabet->Length(); i++)
    {
        AlphabetSymbol* _s = new AlphabetSymbol(data.alphabet->At(i));
        alphabet->Push(_s);
    }

    // All States
    for(int i = 0; i < data.states->Length(); i++)
    {
        std::string stateData = data.states->At(i);
        bool isAFinalState = data.endStates->Contains(stateData);
        bool isTheInitialState = stateData == data.initialState;

        State* _state = new State(stateData, isAFinalState);

        if(!ContainsState(_state))
            states->Push(_state);

        // Initial State
        initialState = isTheInitialState ? _state : initialState;
    }

    // Transition
    for(int i = 0; i < data.transitions->Length(); i++)
    {
        Transition_ReadedData _tmp = data.transitions->At(i);

        int initIndex = IndexOfState(new State(_tmp.initialState));
        int destinIndex = IndexOfState(new State(_tmp.destinState));
        int symbolIndex = IndexOfSymbol(new AlphabetSymbol(_tmp.transitionSymbol));

        if(initIndex == OUT_OF_INDEX || destinIndex == OUT_OF_INDEX || symbolIndex == OUT_OF_INDEX)
        {
            throw new InvalidTransitionFormatException(_tmp);
        }

        State* _destin = states->At(destinIndex);
        AlphabetSymbol* _symbol =  alphabet->At(symbolIndex);
        State* _init = states->At(initIndex);

        Transition* _transition = new Transition(_destin, _symbol);
        transitions->Push(_transition);
        _init->AddTransition(_transition);
    }

    currentState = new std::vector<StateAfn*>();// new MyList<StateAfn*>();
    //currentState->Push(new StateAfn(initialState));
    currentState->push_back(new StateAfn(initialState));
}

std::string DFA_Machine::ToString()
{
    std::string s = "";

    s += "\n-----Alphabet-----\n";
    for(int i = 0; i < alphabet->Length(); i++)
        s += alphabet->At(i)->GetValue() + " ";

    s += "\n-----States-----\n";
    for(int i = 0; i < states->Length(); i++)
        s += states->At(i)->GetName() + " ";

    s += "\n-----Initial state-----\n";
    s += initialState->GetName() + " ";   

    s += "\n-----End States-----\n";
    for(int i = 0; i < states->Length(); i++)
    {
        if(states->At(i)->IsAFinalState())
            s += states->At(i)->GetName() + " ";
    }

    s += "\n-----Transitions-----\n";
    for(int i = 0; i < states->Length(); i++)
    {
        s += states->At(i)->GetTransitionsStr();
    }
    s += '\n';

    return s;
}

bool DFA_Machine::ContainsState(State* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(states->At(i)->GetName() == s->GetName())
            return true;
    }

    return false;
}

int DFA_Machine::IndexOfState(State* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(states->At(i)->GetName() == s->GetName())
            return i;
    }

    return OUT_OF_INDEX;
}

int DFA_Machine::IndexOfSymbol(AlphabetSymbol* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(alphabet->At(i)->GetValue() == s->GetValue())
            return i;
    }

    return OUT_OF_INDEX;
}

std::string DFA_Machine::GetProcessChain()
{
    std::string msg = "";
    for (int i = 0; i < currentState->size(); i++)
    {
        MyList<NFA_Chain> _chain = currentState->at(i)->GetProcessChain();
        for (int j = 0; j < _chain.Length(); j++)
        {
            msg += _chain.At(j).GetCurrent()->GetName() + "->";    
            msg += _chain.At(j).GetTransition()->GetTransitionSymbol()->GetValue() + "->"; 
            msg += _chain.At(j).GetTransition()->GetDestinationState()->GetName() + '\n';       
        }
        msg += "\n";
    }
    return msg;
}

bool DFA_Machine::IsOnFinalState()
{
    for (int i = 0; i < currentState->size(); i++)
    {
        State* _s = currentState->at(i)->getCurState();
        if (_s->IsAFinalState())
        {
            std::string name = currentState->at(i)->getCurState()->GetName();
            bool value = currentState->at(i)->getCurState();
            return true;
        }
    }
    return false;
}

void DFA_Machine::ProcessSymbol(AlphabetSymbol sim)
{
    //MyList<StateAfn*>* afnStates = new MyList<StateAfn*>();
    std::vector<StateAfn*>* afnStates = new std::vector<StateAfn*>();
    AlphabetSymbol* symbolRef = new AlphabetSymbol(sim.GetValue());

    for (int i = 0; i < currentState->size(); i++)
    {
        StateAfn* nfaState = currentState->at(i);
        State* oldState = currentState->at(i)->getCurState();
        MyList<NFA_Chain> processChain = nfaState->GetProcessChain();

        if (currentState->at(i)->IsEquals(trapState))
        {
            //afnStates->Push(trapState);
            afnStates->push_back(new StateAfn(trapState->getCurState(), processChain));
            continue;
        }

        if(oldState->CanProcessSymbol(sim))
        {
            //MyList<State*> _states = oldState->ProcessSymbol(sim);
            std::vector<State*> _states = oldState->ProcessSymbol2(sim);

            for (int j = 0; j < _states.size(); j++)
            {
                afnStates->push_back(new StateAfn(_states.at(j), processChain));
                int index = afnStates->size()-1;
                afnStates->at(index)->AddProcessChain(NFA_Chain(oldState, new Transition(_states.at(j), symbolRef)));
            }
        }
        else
        {
            afnStates->push_back(new StateAfn(trapState->getCurState(), processChain));
            Transition* _t = new Transition(trapState->getCurState(), symbolRef);
            NFA_Chain _c = NFA_Chain(oldState, _t);
            afnStates->at(afnStates->size()-1)->AddProcessChain(_c);
        }
    }

    //currentState->clear();
    currentState = afnStates;
}

/*void DFA_Machine::ProcessEpsilon()
{
    if (currentState == trapState)
        return;
*/
    /* TODO: Add ProcessEpsilon Code*/
    //currentState = currentState->ProcessEpsilon();
//}