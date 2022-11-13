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

void TestTransitions()
{
    State* q0 = new State("q0");
    State* q1 = new State("q1");
    Symbol* a = new Symbol("a");
    Transition* t =  new Transition(q1, a);
    Transition* t2 = new Transition(q1, new Symbol());

    q0->AddTransition(t);
    q0->AddTransition(t2);
    q0->ListTransitions();
}

void TestNFAReader()
{
    NFA_FileReader::ReadFile(FILE_ADDRESS);
}

#include "Utils/StringExtensions.hpp"
void TestStrSplit()
{
    string b = "É parte da cura o desejo de ser curado.";
    MyList<string> l = StringExtensions::Split(b, " ");

    for(int i = 0; i < l.Length(); i++)
        cout << l.At(i) << endl;
}

int main()
{
    //TestTransitions();
    TestNFAReader();
    //TestStrSplit();
}