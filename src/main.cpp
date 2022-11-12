#include <iostream>
#include <string>
#include "Utils/MyList.h"
#include "NFA_FileReader.h"

using namespace std;
using namespace NFA_FileReader;

const std::string FILE_ADDRESS = "../afn2.txt";

#include "Symbol.h"
#include "Transition.h"
#include "State.h"

int main()
{
    //NFA_FileReader::ReadFile(FILE_ADDRESS);
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    Symbol* a = new Symbol("a");
    Transition t =  Transition(q1, a);

    cout << t.GetDestinationState()->GetName() << " -> ";
    cout << t.GetTransitionSymbol()->GetValue() << " -> ";

    q0->AddTransition(t);
    q0->ListTransitions();
}