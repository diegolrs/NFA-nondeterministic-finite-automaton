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

    currentState = new MyList<StateAfn*>();
    currentState->Push(new StateAfn(initialState));
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
    for (int i = 0; i < currentState->Length(); i++)
    {
        std::vector<std::string> _chain = currentState->At(i)->getLastStates();
        for (int j = 0; j < _chain.size(); j++)
        {
            msg += _chain.at(j);       
        }
        msg += "\n";
    }
    return msg;
}

bool DFA_Machine::IsOnFinalState()
{
    for (int i = 0; i < currentState->Length(); i++)
    {
        State* _s = currentState->At(i)->getCState();
        if (_s->IsAFinalState())
        {
            std::string name = currentState->At(i)->getCState()->GetName();
            bool value = currentState->At(i)->getCState();
            return true;
        }
    }
    return false;
}

void DFA_Machine::ProcessSymbol(AlphabetSymbol sim)
{
    MyList<StateAfn*>* afnStates = new MyList<StateAfn*>();

    for (int i = 0; i < currentState->Length(); i++)
    {
        if (currentState->At(i)->IsEquals(trapState))
        {
            //afnStates->Push(trapState);
            afnStates->Push(new StateAfn(trapState->getCState(), currentState->At(i)->getLastStates()));
            continue;
        }

        std::string msg = "";
        State* oldState = currentState->At(i)->getCState();
        //MyList<std::string> processChain =  currentState->At(i)->getLastStates();
        std::vector<std::string> processChain = currentState->At(i)->getLastStates();

        if(oldState->CanProcessSymbol(sim))
        {
            MyList<State*> _states = oldState->ProcessSymbol(sim);

            for (int j = 0; j < _states.Length(); j++)
            {
                afnStates->Push(new StateAfn(_states.At(j), processChain));
                msg = oldState->GetName() + "->" + sim.GetValue() + "->" + _states.At(j)->GetName() + "\n";
                int index = afnStates->Length()-1;
                StateAfn* _mafn = afnStates->At(index);
                _mafn->addProcessAfn(msg);
            }
        }else
        {
            afnStates->Push(new StateAfn(trapState->getCState(), processChain));
            msg = oldState ->GetName() + "->" + sim.GetValue() + "->" + CRASH_STATUS_NAME +"\n";
            afnStates->At(afnStates->Length()-1)->addProcessAfn(msg);
        }
    }

    currentState->Clear();
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