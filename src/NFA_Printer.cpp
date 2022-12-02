#include "NFA_Printer.hpp"

using namespace ConsoleFormatter;

void NFA_Printer::PrintProcessmentTree(NaryTree<Transition*>* processmentTree)
{
    // Get all crashed chains and all chain at the deepest level (bigger height value)
    MyList<NaryTree_Node<Transition*>*> crashedsChains, finishedsChains;
    crashedsChains = processmentTree->GetWithHeight(NFA_Machine::CRASH_STATE_HEIGHT);
    finishedsChains = processmentTree->GetWithHeight(processmentTree->GetMaxHeight());

    std::cout << "-----Processment-----";
    PrintProcessmentList(crashedsChains);
    PrintProcessmentList(finishedsChains);
}

void NFA_Printer::PrintProcessmentList(MyList<NaryTree_Node<Transition*>*> node)
{
    AlphabetSymbol* symbol;

    for(int i = 0; i < node.Length(); i++)
    {
        NaryTree_Node<Transition*>* s = node.At(i);
        MyList<Transition*> chainList = MyList<Transition*>();

        // Getting all processing chain of the last state
        // Iterate from bottom to top
        while(s != nullptr)
        {
            chainList.Push(s->GetContent());
            s = s->GetParent();  
        }

        bool chainIsAccepted = chainList.At(0)->GetDestinationState()->IsAFinalState();

        // Make text green case chain is accepted, red otherwise
        UpdateConsoleColor(chainIsAccepted);

        Transition* _transition = chainList.GetLast();

        // Print initial state
        std::cout << std::endl << _transition->GetDestinationState()->GetName();

        for(int j = chainList.Length()-2; j >= 0; j--)
        {
            Transition* _transition = chainList.At(j);

            symbol = _transition->GetTransitionSymbol();

            if(symbol != nullptr)
                std::cout << " -> " << symbol->GetValue() << " -> " ;

            std::cout << _transition->GetDestinationState()->GetName();
        }

        if(chainIsAccepted)
            std::cout << " " << NFA_Printer::CHAIN_IS_ACCEPTED_SYMBOL;
        else
            std::cout << " " << NFA_Printer::CHAIN_IS_NOT_ACCEPTED_SYMBOL;

        ConsoleFormatter::ResetConsoleColor();
    }
}

void NFA_Printer::UpdateConsoleColor(bool chainIsAccepted)
{
    int consoleColor = chainIsAccepted ? ConsoleFormatter::GREEN_CONSOLE_COLOR 
                                            : ConsoleFormatter::RED_CONSOLE_COLOR;

    ConsoleFormatter::SetConsoleColor(consoleColor);
}