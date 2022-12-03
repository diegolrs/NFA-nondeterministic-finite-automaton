#pragma once

#include <iostream>
#include "Transition.hpp"
#include "Utils/NaryTree.hpp"
#include "Utils/ConsoleFormatter.hpp"
#include "NFA_Machine.hpp"

namespace NFA_Printer
{
    const char CHAIN_IS_ACCEPTED_SYMBOL = 'V';
    const char CHAIN_IS_NOT_ACCEPTED_SYMBOL = 'X';

    void PrintProcessmentTree(NaryTree<Transition*>* processmentTree);
    void PrintProcessmentList(MyList<NaryTree_Node<Transition*>*> node);
    void UpdateConsoleColor(bool chainIsAccepted); // Make text green case chain is accepted, red otherwise
}