#include <iostream>
#include <string>
#include "stdlib.h"

#include "Utils/MyList.hpp"
#include "NFA_FileReader.hpp"
#include "NFA_Machine.hpp"
#include "Exceptions/Exception.hpp"

#include "AlphabetSymbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace NFA_FileReader;

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

void TestDFAReader(MyList<AlphabetSymbol> *c, string arquivo)
{
    try
    {
        NFA_ReadedData data =  NFA_FileReader::ReadFile(arquivo);
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

        NaryTree<Transition*>* chain = machine->GetChain();
        MyList<NaryTree_Node<Transition*>*> crashed = chain->GetWithHeight(NFA_Machine::CRASH_STATE_HEIGHT);
        AlphabetSymbol* symbol;

        for(int i = 0; i < crashed.Length(); i++)
        {
            NaryTree_Node<Transition*>* s = crashed.At(i);
            MyList<Transition*> chainList = MyList<Transition*>();

            while(s != nullptr)
            {
                chainList.Push(s->GetContent());
                s = s->GetParent();  
            }

            Transition* _transition = chainList.At(chainList.Length()-1);
            cout << _transition->GetDestinationState()->GetName();

            for(int j = chainList.Length()-2; j >= 0; j--)
            {
                Transition* _transition = chainList.At(j);

                symbol = _transition->GetTransitionSymbol();

                if(symbol != nullptr)
                    cout << " -> " << symbol->GetValue() << " -> " ;

                cout << _transition->GetDestinationState()->GetName();
            }

            cout << "\n";
        }

        MyList<NaryTree_Node<Transition*>*> endeds = chain->GetWithHeight(chain->GetMaxHeight());
        
        for(int i = 0; i < endeds.Length(); i++)
        {
            NaryTree_Node<Transition*>* s = endeds.At(i);
            MyList<Transition*> chainList = MyList<Transition*>();

            while(s != nullptr)
            {
                chainList.Push(s->GetContent());
                s = s->GetParent();
            }

            Transition* _transition = chainList.At(chainList.Length()-1);
            cout << _transition->GetDestinationState()->GetName();

            for(int j = chainList.Length()-2; j >= 0; j--)
            {
                _transition = chainList.At(j);

                symbol = _transition->GetTransitionSymbol();

                if(symbol != nullptr)
                    cout << " -> " << symbol->GetValue() << " -> " ;

                cout << _transition->GetDestinationState()->GetName();
            }

            if(chainList.At(0)->GetDestinationState()->IsAFinalState())
                cout << " V";
            else
                cout << " X";

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

string RequestFileName()
{
    string fileName;
    cout << "Digite o nome do arquivo: " << endl;
    getline(cin, fileName);
    return fileName;
}

MyList<AlphabetSymbol>* RequestChainToProcess()
{
    string symbols;
    MyList<AlphabetSymbol> *chain = new MyList<AlphabetSymbol>();

    cout << "Digite os elementos da cadeia: " << endl;
    getline(cin, symbols);

    for(int i = 0; i < symbols.size(); i++) 
    {
        string symbol(1, symbols[i]);
        chain->Push(AlphabetSymbol(symbol));
    }

    return chain;
}

int main()
{
    string fileName = RequestFileName();
    MyList<AlphabetSymbol> *chain = RequestChainToProcess();
    //TestTransitions();
    TestDFAReader(chain, fileName);
    //TestTree();
    //TestStrSplit();

    return 0;
}