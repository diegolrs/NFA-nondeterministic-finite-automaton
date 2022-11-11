#include "NFA_FileReader.h"

void NFA_FileReader::ReadFile(std::string address)
{
    std::string myText;
    std::ifstream myFile(address);

    try
    {
        if(!myFile.is_open())
        {
            throw FileNotFoundException(address);
        }
    }
    catch(FileNotFoundException e)
    {
        std::cerr << e.GetMessage() << '\n';
        return;
    }

    while (getline (myFile, myText)) 
    {
        if(StringExtensions::Contains(myText, ALPHABET_FILE_TAG))
        {
            ReadAlphabet(myText);
        }
        else if(StringExtensions::Contains(myText, STATES_FILE_TAG))
        {
            ReadStates(myText);
        }
        else if(StringExtensions::Contains(myText, INIT_STATE_FILE_TAG))
        {
            ReadInitialState(myText);
        }
        else if(StringExtensions::Contains(myText, END_STATES_FILE_TAG))
        {
            ReadEndStates(myText);
        }
        else if(StringExtensions::Contains(myText, TRANSITION_FILE_TAG))
        {
            ReadTransitions(&myFile);
            break;
        }
    }

    myFile.close();
}

void NFA_FileReader::ReadAlphabet(std::string alphabetLine)
{
    std::cout << "\n-----Reading alphabet ---------" << std::endl;
    std::cout << StringExtensions::RemoveText(alphabetLine, ALPHABET_FILE_TAG) << std::endl;
}

void NFA_FileReader::ReadStates(std::string statesLine)
{
    std::cout << "\n-----Reading states ---------" << std::endl;
    std::cout << StringExtensions::RemoveText(statesLine, STATES_FILE_TAG) << std::endl;
}

void NFA_FileReader::ReadInitialState(std::string initialStateLine)
{
    std::cout << "\n-----Reading initial state ---------" << std::endl;
    std::cout << StringExtensions::RemoveText(initialStateLine, INIT_STATE_FILE_TAG) << std::endl;
}

void NFA_FileReader::ReadEndStates(std::string endStatesLine)
{
    std::cout << "\n-----Reading end states ---------" << std::endl;
    std::cout << StringExtensions::RemoveText(endStatesLine, END_STATES_FILE_TAG) << std::endl;
}

void NFA_FileReader::ReadTransitions(std::ifstream *myFile)
{
    std::cout << "\n-----Reading transitions ---------" << std::endl;
    std::string text;

    while (getline(*myFile, text)) 
    {
        std::cout << text << std::endl;
    }

    std::cout << "-----------------------" << std::endl;
}