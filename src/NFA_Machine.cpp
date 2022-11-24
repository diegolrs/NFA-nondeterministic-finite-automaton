#include "NFA_Machine.hpp"

//Deterministic Finite Automaton Machine
NFA_Machine::NFA_Machine(NFA_ReadedData data)
{
    alphabet = new MyList<AlphabetSymbol*>();
    states = new MyList<State*>();      
    transitions = new MyList<Transition*>();
    crashState = new State(CRASH_STATUS_NAME);

    // EPSILON
    alphabet->Push(new AlphabetSymbol());

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

    currentState = new MyList<State*>();
    currentState->Push(initialState);
}

std::string NFA_Machine::ToString()
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

bool NFA_Machine::ContainsState(State* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(states->At(i)->GetName() == s->GetName())
            return true;
    }

    return false;
}

int NFA_Machine::IndexOfState(State* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(states->At(i)->GetName() == s->GetName())
            return i;
    }

    return OUT_OF_INDEX;
}

int NFA_Machine::IndexOfSymbol(AlphabetSymbol* s)
{
    for(int i = 0; i < states->Length(); i++)
    {
        if(alphabet->At(i)->GetValue() == s->GetValue())
            return i;
    }

    return OUT_OF_INDEX;
}

std::string NFA_Machine::GetProcessChain()
{
    std::string msg = "";
    // for (int i = 0; i < currentState->size(); i++)
    // {
    //     MyList<NFA_Chain> _chain = currentState->at(i)->GetProcessChain();
    //     for (int j = 0; j < _chain.Length(); j++)
    //     {
    //         msg += _chain.At(j).GetCurrent()->GetName() + "->";    
    //         msg += _chain.At(j).GetTransition()->GetTransitionSymbol()->GetValue() + "->"; 
    //         msg += _chain.At(j).GetTransition()->GetDestinationState()->GetName() + '\n';       
    //     }
    //     msg += "\n";
    // }
    return msg;
}

bool NFA_Machine::IsOnFinalState()
{
    for (int i = 0; i < currentState->Length(); i++)
    {
        if (currentState->At(i)->IsAFinalState())
        {
            return true;
        }
    }
    return false;
}

bool NFA_Machine::IsACurrentState(State* s)
{
    for (int i = 0; i < currentState->Length(); i++)
    {
        if (currentState->At(i)->IsEquals(s))
        {
            return true;
        }
    }
    return false;
}

void NFA_Machine::ProcessSymbol(AlphabetSymbol sim, int index)
{
    MyList<State*>* afnStates = new MyList<State*>();
    AlphabetSymbol* symbolRef = new AlphabetSymbol(sim.GetValue());
    State* oldState;

    for (int i = 0; i < currentState->Length(); i++)
    {
        oldState = currentState->At(i);

        std::cout << " -------------------------- " << std::endl;
        std::cout << "N interacao: " << index << std::endl;
        std::cout << "Atual: " << currentState->At(i)->GetName() << std::endl;
        std::cout << "Simbolo: " << sim.GetValue() << std::endl;

        if (oldState->IsEquals(crashState))
        {
            continue;
        }

        if(oldState->CanProcessSymbol(sim))
        {
            //MyList<State*> _states = oldState->ProcessSymbol(sim);
            MyList<State*> _states = oldState->ProcessSymbol(sim);

            for (int j = 0; j < _states.Length(); j++)
            {
                std::cout << "Destino: " << _states.At(j)->GetName() << std::endl;

                afnStates->Push(_states.At(j));
                int index = afnStates->Length()-1;
            }
        }
        else
        {
            std::cout << "Destino: " << crashState->GetName() << std::endl;     
        }
    }

    currentState->Clear();
    currentState = afnStates;
}

void NFA_Machine::ProcessEpsilon(int index)
{
    AlphabetSymbol* epsilon = new AlphabetSymbol();

    for (int i = 0; i < currentState->Length(); i++)
    {
        State* curState = currentState->At(i);

        if (curState->IsEquals(crashState) || !curState->CanProcessSymbol(epsilon))
        {
            continue;
        }
        
        MyList<State*> _states = curState->ProcessSymbol(epsilon);

        for (int j = 0; j < _states.Length(); j++)
        {
            std::cout << " -------------------------- " << std::endl;
            std::cout << "N interacao: " << index << std::endl;
            std::cout << "Atual: " << curState->GetName() << std::endl;
            std::cout << "Simbolo: " << epsilon->GetValue() << std::endl;
            std::cout << "Destino: " << _states.At(j)->GetName() << std::endl;

            if(!IsACurrentState(_states.At(j)))
                currentState->Push(_states.At(j));
        }
    }
}