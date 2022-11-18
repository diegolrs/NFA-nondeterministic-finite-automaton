#include <iostream>
#include <string>
#include "Utils/MyList.hpp"
#include "DFA_FileReader.hpp"
#include "DFA_Machine.hpp"
#include "Exceptions/Exception.hpp"

#include "AlphabetSymbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace DFA_FileReader;

const std::string FILE_ADDRESS = "../afn5.txt";

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

void TestDFAReader()
{
    try
    {
        DFA_ReadedData data =  DFA_FileReader::ReadFile(FILE_ADDRESS);
        DFA_Machine* machine = new DFA_Machine(data);

        //cout << machine->ToString();

        // for(int i = 0; i < 10; i++)
        // {
        //     if((i%2) == 0){
        //         machine->ProcessSymbol(AlphabetSymbol("0"));
        //     }else{
        //         machine->ProcessSymbol(AlphabetSymbol("1"));
        //     }
        // }

        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("1"));
        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("1"));


        //cout << "-----Processment-----" << endl;
        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("0"));
        // machine->ProcessSymbol(AlphabetSymbol("0"));

        machine->ProcessSymbol(AlphabetSymbol("1"));
        machine->ProcessSymbol(AlphabetSymbol("1"));
        machine->ProcessSymbol(AlphabetSymbol("0"));
        machine->ProcessSymbol(AlphabetSymbol("1"));
        machine->ProcessSymbol(AlphabetSymbol("0"));
        
        //machine->ProcessSymbol(AlphabetSymbol("0"));
        //machine->ProcessSymbol(AlphabetSymbol("1"));
        //machine->ProcessSymbol(AlphabetSymbol("1"));

        cout << machine->GetProcessChain() << endl;
        if (machine->IsOnFinalState()){
           cout << "Cadeia eh aceita" << endl;
        }else{
            cout << "Cadeia nao eh aceita" << endl;
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

int main()
{
    //TestTransitions();
    TestDFAReader();
    //TestStrSplit();

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