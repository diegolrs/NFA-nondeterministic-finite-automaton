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

    processmentTree = new NaryTree<Transition*>();
    processmentTree->AddLeaf(new Transition(initialState, nullptr), nullptr, 0);
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

bool NFA_Machine::IsOnFinalState()
{
    int maxHeight = processmentTree->GetMaxHeight();
    MyList<NaryTree_Node<Transition*>*> lastsStates = processmentTree->GetWithHeight(maxHeight);

    for (int i = 0; i < lastsStates.Length(); i++)
    {
        if (lastsStates.At(i)->GetContent()->GetDestinationState()->IsAFinalState())
        {
            return true;
        }
    }

    return false;
}

void NFA_Machine::ProcessSymbol(AlphabetSymbol sim, int iterationIndex)
{
    AlphabetSymbol* symbolRef = new AlphabetSymbol(sim.GetValue());
    MyList<NaryTree_Node<Transition*>*> current = processmentTree->GetWithHeight(iterationIndex-1);

    NaryTree_Node<Transition*>* node;
    State* oldState;

    for(int i = 0; i < current.Length(); i++)
    {
        node = current.At(i);
        oldState = node->GetContent()->GetDestinationState();

        // Trying to process crashed state
        if (oldState->IsEquals(crashState))
        {
            continue;
        }

        if(oldState->CanProcessSymbol(sim))
        {
            MyList<State*> _states = oldState->ProcessSymbol(sim);

            for (int j = 0; j < _states.Length(); j++)
            {
                Transition* _chainProcessed = new Transition(_states.At(j), symbolRef);
                processmentTree->AddLeaf(_chainProcessed, node, node->GetHeight()+1);
            }
        }
        else
        {
            Transition* _chainProcessed = new Transition(crashState, symbolRef);
            processmentTree->AddLeaf(_chainProcessed, node, CRASH_STATE_HEIGHT);
        }
    }
}

// Verify if state is being processed right now
bool NFA_Machine::IsACurrentState(State* s)
{
    int maxHeight = processmentTree->GetMaxHeight();
    MyList<NaryTree_Node<Transition*>*> lastsStates = processmentTree->GetWithHeight(maxHeight);

    for (int i = 0; i < lastsStates.Length(); i++)
    {
        if (lastsStates.At(i)->GetContent()->GetDestinationState()->IsEquals(s))
        {
            return true;
        }
    }
    return false;  
}

void NFA_Machine::ProcessEpsilon(int iterationIndex)
{
    AlphabetSymbol* epsilon = new AlphabetSymbol();
    MyList<NaryTree_Node<Transition*>*> current = processmentTree->GetWithHeight(iterationIndex-1);

    for(int i = 0; i < current.Length(); i++)
    {
        NaryTree_Node<Transition*>* node = current.At(i);
        State* curState = node->GetContent()->GetDestinationState();

        if (curState->IsEquals(crashState) || !curState->CanProcessSymbol(epsilon))
        {
            continue;
        }

        MyList<State*> _states = curState->ProcessSymbol(epsilon);

        for (int j = 0; j < _states.Length(); j++)
        {
            if(!IsACurrentState(_states.At(j)))
            {
                // add new state at the same level as the parent node in the processment tree
                Transition* _chainProcessed = new Transition(_states.At(j), epsilon);
                processmentTree->AddLeaf(_chainProcessed, node, node->GetHeight());
            }            
        }
    }
}

NaryTree<Transition*>* NFA_Machine::GetChain()
{
    return processmentTree;
}