#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions/NFA_Exceptions.hpp"
#include "Utils/StringExtensions.hpp"

namespace NFA_FileReader
{
    // Constants used in text file
    const std::string ALPHABET_FILE_TAG = "alfabeto=";    
    const std::string STATES_FILE_TAG = "estados="; 
    const std::string INIT_STATE_FILE_TAG = "inicial="; 
    const std::string END_STATES_FILE_TAG = "final="; 
    const std::string TRANSITION_FILE_TAG = "transicoes"; 

    void ReadFile(std::string address);

    void ReadAlphabet(std::string alphabetLine);
    void ReadStates(std::string statesLine);
    void ReadInitialState(std::string initialStateLine);
    void ReadEndStates(std::string endStatesLine);
    void ReadTransitions(std::ifstream *myFile);
}