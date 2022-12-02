#include <iostream>
#include <string>
#include "stdlib.h"

#include "Utils/MyList.hpp"
#include "NFA_FileReader.hpp"
#include "NFA_Machine.hpp"
#include "Exceptions/Exception.hpp"

#include "Utils/NaryTree.hpp"
#include "AlphabetSymbol.hpp"
#include "Transition.hpp"
#include "State.hpp"

using namespace std;
using namespace NFA_FileReader;

const std::string REQUEST_FILE_NAME_MSG = "Digite o nome do arquivo: ";
const std::string REQUEST_CHAIN_TO_PROCCESS_MSG = "Digite os elementos da cadeia: ";

void TestDFAReader(MyList<AlphabetSymbol> *c, string arquivo)
{
    try
    {
        NFA_ReadedData data =  NFA_FileReader::ReadFile(arquivo);
        NFA_Machine* machine = new NFA_Machine(data);

        int maxInterations = c->Length();
        int curInteration = 0;
        int firstEpsilonProcessingHeight = 1;

        machine->ProcessEpsilon(firstEpsilonProcessingHeight);
        curInteration++;

        for (int i = 0; i < c->Length(); i++)
        {            
            machine->ProcessSymbol(c->At(i).GetValue(), curInteration);
            machine->ProcessEpsilon(curInteration);
            curInteration++;
        }


        // ------------------------------
        // --------- PRINT DATA ---------
        // ------------------------------
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

        TestDFAReader(chainToProcess, fileName);
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