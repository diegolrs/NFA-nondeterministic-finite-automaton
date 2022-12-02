#include "NFA_Printer.hpp"

void NFA_Printer::PrintProcessmentTree(NaryTree<Transition*>* processmentTree)
{
    // Get all crashed chains and all chain at the deepest level (bigger height value)
    MyList<NaryTree_Node<Transition*>*> crashedsChains, finishedsChains;
    crashedsChains = processmentTree->GetWithHeight(NFA_Machine::CRASH_STATE_HEIGHT);
    finishedsChains = processmentTree->GetWithHeight(processmentTree->GetMaxHeight());

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

            while(s != nullptr)
            {
                chainList.Push(s->GetContent());
                s = s->GetParent();  
            }

            Transition* _transition = chainList.GetLast();
            std::cout << _transition->GetDestinationState()->GetName();

            for(int j = chainList.Length()-2; j >= 0; j--)
            {
                Transition* _transition = chainList.At(j);

                symbol = _transition->GetTransitionSymbol();

                if(symbol != nullptr)
                    std::cout << " -> " << symbol->GetValue() << " -> " ;

                std::cout << _transition->GetDestinationState()->GetName();
            }

            // Print the status of the last state in the chain
            if(chainList.At(0)->GetDestinationState()->IsAFinalState())
                std::cout << " " << NFA_Printer::CHAIN_IS_ACCEPTED_SYMBOL;
            else
                std::cout << " " << NFA_Printer::CHAIN_IS_NOT_ACCEPTED_SYMBOL;

            std::cout << "\n";
        }
}