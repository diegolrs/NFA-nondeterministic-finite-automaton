#include <iostream>
#include <string>
#include "Utils/MyList.hpp"
#include "DFA_FileReader.hpp"
#include "DFA_Machine.hpp"
#include "Exceptions/Exception.hpp"

#include "Symbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace DFA_FileReader;

const std::string FILE_ADDRESS = "../afn5.txt";

void TestTransitions()
{
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    Symbol* a = new Symbol("a");
    Transition* t =  new Transition(q1, a);
    Transition* t2 = new Transition(q1, new Symbol());

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

        cout << machine->ToString();
        
        //machine->Process(machine->);

        for(int i = 0; i < 10; i++){
            if((i%2) == 0){
                machine->Process(Symbol("0"));
            }else{
                machine->Process(Symbol("1"));
            }
        }
        cout << machine->PrintProcessChain() << endl;
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


}