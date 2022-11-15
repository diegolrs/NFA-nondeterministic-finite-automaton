#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Exceptions/NFA_Exceptions.hpp"
#include "Utils/StringExtensions.hpp"
#include "Utils/MyList.hpp"

#include "AlphabetSymbol.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "DFA_ReadedData.hpp"

namespace DFA_FileReader
{
    // Constants used in text file
    const std::string DELIMETER = ",";
    const std::string ALPHABET_FILE_TAG = "alfabeto=";    
    const std::string STATES_FILE_TAG = "estados="; 
    const std::string INIT_STATE_FILE_TAG = "inicial="; 
    const std::string END_STATES_FILE_TAG = "final="; 
    const std::string TRANSITION_FILE_TAG = "transicoes"; 
    const std::string EPSILON_FILE_TAG = "epsilon"; 

    DFA_ReadedData ReadFile(std::string address);

    MyList<std::string>* ReadAlphabet(std::string alphabetLine);
    MyList<std::string>* ReadStates(std::string statesLine);
    MyList<Transition_ReadedData>* ReadTransitions(std::ifstream *myFile);
    std::string ReadInitialState(std::string initialStateLine);
    MyList<std::string>* ReadEndStates(std::string endStatesLine);
}