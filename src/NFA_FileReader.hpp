#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Exceptions/NFA_Exceptions.hpp"
#include "Utils/StringExtensions.hpp"
#include "Utils/MyList.hpp"
#include "Symbol.hpp"
#include "State.hpp"
#include "Transition.hpp"

namespace NFA_FileReader
{
    const std::string DELIMETER = ",";

    // Constants used in text file
    const std::string ALPHABET_FILE_TAG = "alfabeto=";    
    const std::string STATES_FILE_TAG = "estados="; 
    const std::string INIT_STATE_FILE_TAG = "inicial="; 
    const std::string END_STATES_FILE_TAG = "final="; 
    const std::string TRANSITION_FILE_TAG = "transicoes"; 

    void ReadFile(std::string address);

    MyList<Symbol>* ReadAlphabet(std::string alphabetLine);
    MyList<State>* ReadStates(std::string statesLine);
    MyList<std::string>* ReadTransitions(std::ifstream *myFile);
    // State ReadInitialState(std::string initialStateLine);
    // MyList<State> ReadEndStates(std::string endStatesLine);
    // MyList<Transition> ReadTransitions(std::ifstream *myFile);
    
    //void ReadAlphabet(std::string alphabetLine);
    // void ReadStates(std::string statesLine);
    void ReadInitialState(std::string initialStateLine);
    void ReadEndStates(std::string endStatesLine);
    //void ReadTransitions(std::ifstream *myFile);
}