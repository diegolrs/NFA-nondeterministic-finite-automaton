#include "DFA_FileReader.hpp"

DFA_ReadedData DFA_FileReader::ReadFile(std::string address)
{
    std::string myText;
    std::ifstream myFile(address);

    if(!myFile.is_open())
    {
        throw FileNotFoundException(address);
    }  

    MyList<std::string>* alphabet;
    MyList<std::string>* states;
    std::string initialState;
    MyList<std::string>* endStates;
    MyList<Transition_ReadedData>* transitions;

    while (getline (myFile, myText)) 
    {
        if(StringExtensions::Contains(myText, ALPHABET_FILE_TAG))
        {
            alphabet = ReadAlphabet(myText);
        }
        else if(StringExtensions::Contains(myText, STATES_FILE_TAG))
        {
            states = ReadStates(myText);
        }
        else if(StringExtensions::Contains(myText, INIT_STATE_FILE_TAG))
        {
            initialState = ReadInitialState(myText);
        }
        else if(StringExtensions::Contains(myText, END_STATES_FILE_TAG))
        {
            endStates = ReadEndStates(myText);
        }
        else if(StringExtensions::Contains(myText, TRANSITION_FILE_TAG))
        {
            transitions = ReadTransitions(&myFile);
            break;
        }
    }

    myFile.close();

    DFA_ReadedData readedData = DFA_ReadedData();
    readedData.alphabet = alphabet;
    readedData.endStates = endStates;
    readedData.initialState = initialState;
    readedData.states = states;
    readedData.transitions = transitions;
    return readedData;
}

MyList<std::string>* DFA_FileReader::ReadAlphabet(std::string alphabetLine)
{
    std::string inputline = StringExtensions::RemoveText(alphabetLine, ALPHABET_FILE_TAG);
    return StringExtensions::Split(inputline, DELIMETER);
}

MyList<std::string>* DFA_FileReader::ReadStates(std::string statesLine)
{
    std::string inputline =  StringExtensions::RemoveText(statesLine, STATES_FILE_TAG);
    return StringExtensions::Split(inputline, DELIMETER);
}

std::string DFA_FileReader::ReadInitialState(std::string initialStateLine)
{
    return StringExtensions::RemoveText(initialStateLine, INIT_STATE_FILE_TAG);
}

MyList<std::string>* DFA_FileReader::ReadEndStates(std::string endStatesLine)
{
    std::string inputline = StringExtensions::RemoveText(endStatesLine, END_STATES_FILE_TAG);
    return StringExtensions::Split(inputline, DELIMETER);
}

MyList<Transition_ReadedData>* DFA_FileReader::ReadTransitions(std::ifstream *myFile)
{
    std::string inputline;
    MyList<Transition_ReadedData>* transitionsData = new MyList<Transition_ReadedData>();

    while (getline(*myFile, inputline)) 
    {
        Transition_ReadedData data = Transition_ReadedData();

        MyList<std::string>* _split = StringExtensions::Split(inputline, DELIMETER);
        data.initialState = _split->At(0);
        data.destinState = _split->At(1);
        data.transitionSymbol = _split->At(2);

        transitionsData->Push(data);
    }

    return transitionsData;
}