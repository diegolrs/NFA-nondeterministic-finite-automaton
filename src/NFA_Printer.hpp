#pragma once

#include <iostream>
#include "Transition.hpp"
#include "Utils/NaryTree.hpp"
#include "NFA_Machine.hpp"

namespace NFA_Printer
{
    const char CHAIN_IS_ACCEPTED_SYMBOL = 'V';
    const char CHAIN_IS_NOT_ACCEPTED_SYMBOL = 'X';
    const std::string CHAIN_IS_ACCEPTED_MSG = "A cadeia processada eh aceita. \n";
    const std::string CHAIN_IS_NOT_ACCEPTED_MSG = "A cadeia processada nao eh aceita. \n";

    void PrintProcessmentTree(NaryTree<Transition*>* processmentTree);
    void PrintProcessmentList(MyList<NaryTree_Node<Transition*>*> node);
}