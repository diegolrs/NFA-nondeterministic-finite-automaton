#include <iostream>
#include <string>
#include "Utils/MyList.hpp"
#include "NFA_FileReader.hpp"

#include "Symbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace NFA_FileReader;

const std::string FILE_ADDRESS = "../afn2.txt";

int main()
{
    //NFA_FileReader::ReadFile(FILE_ADDRESS);

    State* q0 = new State("q0");
    State* q1 = new State("q1");
    Symbol* a = new Symbol("a");
    Transition* t =  new Transition(q1, a);
    Transition* t2 = new Transition(q1, new Symbol());

    q0->AddTransition(t);
    q0->AddTransition(t2);
    q0->ListTransitions();
}