#include <iostream>
#include <string>
#include "Utils/MyList.hpp"
#include "NFA_FileReader.hpp"
#include "NFA_Machine.hpp"
#include "Exceptions/Exception.hpp"

#include "AlphabetSymbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace NFA_FileReader;

const std::string FILE_ADDRESS = "../4b.txt";

void TestTransitions()
{
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    AlphabetSymbol* a = new AlphabetSymbol("a");
    Transition* t =  new Transition(q1, a);
    Transition* t2 = new Transition(q1, new AlphabetSymbol());

    q0->AddTransition(t);
    q0->AddTransition(t2);
    cout << q0->GetTransitionsStr();
}

void TestDFAReader(MyList<AlphabetSymbol> *c)
{
    try
    {
        NFA_ReadedData data =  NFA_FileReader::ReadFile(FILE_ADDRESS);
        NFA_Machine* machine = new NFA_Machine(data);

        int maxInterations = c->Length();
        int curInteration = 0;
        int firstEpsilonProcessingHeight = 1;

        machine->ProcessEpsilon(firstEpsilonProcessingHeight, maxInterations);
        curInteration++;

        for (int i = 0; i < c->Length(); i++)
        {            
            machine->ProcessSymbol(c->At(i).GetValue(), curInteration, maxInterations);
            machine->ProcessEpsilon(curInteration, maxInterations);
            curInteration++;
        }

        //cout << machine->GetProcessChain() << endl;
        // if (machine->IsOnFinalState())
        //    cout << "\n\nA cadeia fornecida eh reconhecida pelo automato" << endl;
        // else
        //     cout << "\n\nA cadeia fornecida nao eh reconhecida pelo automato" << endl;

        NaryTree<Transition*>* chain = machine->GetChain();
        MyList<NaryTree_Node<Transition*>*> crashed = chain->GetWithHeight(NFA_Machine::CRASH_STATE_HEIGHT);
        AlphabetSymbol* symbol;

        for(int i = 0; i < crashed.Length(); i++)
        {
            NaryTree_Node<Transition*>* s = crashed.At(i);

            while(s != nullptr)
            {
                cout << s->GetContent()->GetDestinationState()->GetName();
                symbol = s->GetContent()->GetTransitionSymbol();
                s = s->GetParent();

                if(s != nullptr)
                {
                    cout << " <- (" << symbol->GetValue() << ")";
                    cout << " <- ";
                }
                    
            }
            cout << "\n";
        }

        MyList<NaryTree_Node<Transition*>*> endeds = chain->GetWithHeight(chain->GetMaxHeight());

        for(int i = 0; i < endeds.Length(); i++)
        {
            NaryTree_Node<Transition*>* s = endeds.At(i);

            if(s->GetContent()->GetDestinationState()->IsAFinalState())
                cout << "V ";
            else
                cout << "X ";

            while(s != nullptr)
            {
                cout << s->GetContent()->GetDestinationState()->GetName();
                symbol = s->GetContent()->GetTransitionSymbol();

                s = s->GetParent();

                if(s != nullptr)
                {
                    cout << " <- (" << symbol->GetValue() << ")";
                    cout << " <- ";
                }
            }
            cout << "\n";
        }
    }
    catch(FileNotFoundException e)
    {
        std::cerr << e.GetMessage() << '\n';
        exit(-1);
    }
    catch(InvalidTransitionFormatException e)
    {
        std::cerr << e.GetMessage() << '\n';
        exit(-1);
    }
}

#include "Utils/StringExtensions.hpp"
void TestStrSplit()
{
    string b = "É parte da cura o desejo de ser curado.";
    MyList<string>* l = StringExtensions::Split(b, " ");

    for(int i = 0; i < l->Length(); i++)
        cout << l->At(i) << endl;
}

#include "Utils/NaryTree.hpp"
void TestTree()
{
    NaryTree<State*>* tree = new NaryTree<State*>();
    //tree->SetRoot(root);

    State* q0 = new State("q0");
    State* q1 = new State("q1");
    State* q2 = new State("q2");
    State* q3 = new State("q3");

    tree->AddLeaf(q0, nullptr);
    NaryTree_Node<State*>* root = tree->GetWithHeight(0).At(0);

    NaryTree_Node<State*>* n1 = new NaryTree_Node<State*>(q1, root, 1);
    NaryTree_Node<State*>* n2 = new NaryTree_Node<State*>(q2, root, 1);
    NaryTree_Node<State*>* n3 = new NaryTree_Node<State*>(q3, n2, 2);

    tree->AddLeaf(q1, root);
    tree->AddLeaf(q2, root);
    
    // NaryTree_Node<State*>* s = root;

    // while(s != nullptr)
    // {
    //     cout << "->" << s->GetContent()->GetName();
    //     s = s->GetParent();
    // }

    // cout << endl;

    MyList<NaryTree_Node<State*>*> levels = tree->GetWithHeight(1);
    tree->AddLeaf(q3, levels.At(0));

    for(int i = 0; i < levels.Length(); i++)
    {
        cout << levels.At(i)->GetContent()->GetName() << " ";
    }

    NaryTree_Node<State*>* s = tree->GetWithHeight(2).At(0);
    cout << s->GetContent()->GetName();
    while(s != nullptr)
    {
        cout << "->" << s->GetContent()->GetName();
        s = s->GetParent();
    }

    cout << endl;
}

int main()
{
    MyList<AlphabetSymbol> *chain = new MyList<AlphabetSymbol>();
    string symbols;
 
    cout << "Digite os elementos da cadeia: " << endl;
    getline(cin, symbols);

    for(int i = 0; i < symbols.size(); i++) 
    {
        string symbol(1, symbols[i]);
        chain->Push(AlphabetSymbol(symbol));
    }


    //TestTransitions();
    TestDFAReader(chain);
    //TestTree();
    //TestStrSplit();

    // NFA_Chain c = NFA_Chain(nullptr, nullptr);
    // MyList<NFA_Chain> chain = RetornaStruct();//MyList<NFA_Chain>();
    // chain.Push(c);

    // for(int i = 0; i < 5000; i++)
    // {
    //     cout<<chain.Length();
    //     NFA_Chain c2 = NFA_Chain(nullptr, nullptr);
    //     chain.Push(c2);
    // }

    // cout << "sucesso";

    // try
    // {
    //     Transition_ReadedData d;
    //     d.destinState = "destino";
    //     d.initialState = "inicio";
    //     d.transitionSymbol = "simbolo";
    //     throw InvalidTransitionFormatException(d);
    // }
    // catch (InvalidTransitionFormatException &e)
    // {
    //     std::cout << e.what() << std::endl;
    // }
    return{ 0 };
}