#include "DFA_Machine.hpp"

//Deterministic Finite Automaton Machine
DFA_Machine::DFA_Machine(DFA_ReadedData data)
{
    alphabet = new MyList<Symbol*>();
    states = new MyList<State*>();         
    endStates = new MyList<State*>();
    transitions = new MyList<Transition*>();
    
    // Initial state
    initialState = new State(data.initialState);
    states->Push(initialState);

    // Symbols
    for(int i = 0; i < data.alphabet->Length(); i++)
    {
        Symbol* _s = new Symbol(data.alphabet->At(i));
        alphabet->Push(_s);
    }

    // End States 
    for(int i = 0; i < data.endStates->Length(); i++)
    {
        State* _s = new State(data.endStates->At(i));
        endStates->Push(_s);
    }

    // All States
    for(int i = 0; i < data.states->Length(); i++)
    {
        State* _s = new State(data.states->At(i));
        _s->SetAsFinalState(endStates->Contains(_s));

        // Avoid duplicated states on list
        if(!states->Contains(_s))
        {
            states->Push(_s);
        }
    }

    // Transition
    for(int i = 0; i < data.transitions->Length(); i++)
    {
        Transition_ReadedData _tmp = data.transitions->At(i);

        int initIndex = states->GetIndexOf(new State(_tmp.initialState));
        int destinIndex = states->GetIndexOf(new State(_tmp.destinState));
        int symbolIndex = alphabet->GetIndexOf(new Symbol(_tmp.transitionSymbol));

        if(initIndex == OUT_OF_INDEX || destinIndex == OUT_OF_INDEX || symbolIndex == OUT_OF_INDEX)
        {
            throw new InvalidTransitionFormatException(_tmp);
        }

        State* _destin = states->At(destinIndex);
        Symbol* _symbol =  alphabet->At(symbolIndex);
        State* _init = states->At(initIndex);

        Transition* _transition = new Transition(_destin, _symbol);
        transitions->Push(_transition);
        _init->AddTransition(_transition);
    }
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
    for(int i = 0; i < endStates->Length(); i++)
        s += endStates->At(i)->GetName() + " ";

    s += "\n-----Transitions-----\n";
    for(int i = 0; i < states->Length(); i++)
    {
        s += states->At(i)->GetTransitionsStr();
    }
    s += '\n';

    return s;
}