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

const std::string FILE_ADDRESS = "../afn7.txt";

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

        for (int i = 0; i < c->Length(); i++)
        {
            if (i == 0)
            {
                machine->ProcessEpsilon(curInteration, maxInterations);
                curInteration++;
            }
            
            machine->ProcessSymbol(c->At(i).GetValue(), curInteration, maxInterations);
            machine->ProcessEpsilon(curInteration, maxInterations);
            curInteration++;
        }

        //cout << machine->GetProcessChain() << endl;
        if (machine->IsOnFinalState())
           cout << "\n\nA cadeia fornecida eh reconhecida pelo automato" << endl;
        else
            cout << "\n\nA cadeia fornecida nao eh reconhecida pelo automato" << endl;
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