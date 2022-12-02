#include <iostream>
#include <string>
#include "stdlib.h"

#include "Utils/MyList.hpp"
#include "NFA_FileReader.hpp"
#include "NFA_Machine.hpp"
#include "NFA_Printer.hpp"
#include "Exceptions/Exception.hpp"

#include "Utils/NaryTree.hpp"
#include "AlphabetSymbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace NFA_FileReader;

const std::string REQUEST_FILE_NAME_MSG = "Digite o nome do arquivo: ";
const std::string REQUEST_CHAIN_TO_PROCCESS_MSG = "Digite os elementos da cadeia: ";

string RequestFileName()
{
    string fileName;
    cout << REQUEST_FILE_NAME_MSG << endl;
    getline(cin, fileName);
    return fileName;
}

MyList<AlphabetSymbol>* RequestChainToProcess()
{
    string symbols;
    MyList<AlphabetSymbol> *chain = new MyList<AlphabetSymbol>();

    cout << REQUEST_CHAIN_TO_PROCCESS_MSG << endl;
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
    try
    {
        string fileName = RequestFileName();
        MyList<AlphabetSymbol> *chainToProcess = RequestChainToProcess();

        NFA_ReadedData dataReadedFromFile =  NFA_FileReader::ReadFile(fileName);
        NFA_Machine* machine = new NFA_Machine(dataReadedFromFile);
        NaryTree<Transition*>* processmentTree = machine->StartProcessment(machine, chainToProcess);

        cout << machine->ToString();
        NFA_Printer::PrintProcessmentTree(processmentTree);
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

    return 0;
}