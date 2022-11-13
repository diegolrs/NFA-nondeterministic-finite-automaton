#include "NFA_FileReader.hpp"

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

    MyList<Symbol>* symbols;
    MyList<State>* states;
    MyList<std::string>* transitions;

    while (getline (myFile, myText)) 
    {
        if(StringExtensions::Contains(myText, ALPHABET_FILE_TAG))
        {
            symbols = ReadAlphabet(myText);
        }
        else if(StringExtensions::Contains(myText, STATES_FILE_TAG))
        {
            states = ReadStates(myText);
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
            transitions = ReadTransitions(&myFile);
            break;
        }
    }

    for(int i = 0; i < symbols->Length(); i++)
    {
        std::cout << symbols->At(i).GetValue() << ",";
    }

    std::cout << std::endl;

    for(int i = 0; i < states->Length(); i++)
    {
        std::cout << states->At(i).GetName() << ",";
    }

    std::cout << std::endl;

    for(int i = 0; i < transitions->Length(); i++)
    {
        std::cout << transitions->At(i) << std::endl;
    }

    myFile.close();
}

MyList<Symbol>* NFA_FileReader::ReadAlphabet(std::string alphabetLine)
{
    std::cout << "\n-----Reading alphabet ---------" << std::endl;
    std::string inputline = StringExtensions::RemoveText(alphabetLine, ALPHABET_FILE_TAG);
    MyList<std::string> symbols_str = StringExtensions::Split(inputline, DELIMETER);

    MyList<Symbol>* symbols = new MyList<Symbol>();

    for(int i = 0; i < symbols_str.Length(); i++)
        symbols->Push(Symbol(symbols_str.At(i)));

    return symbols;
}

MyList<State>* NFA_FileReader::ReadStates(std::string statesLine)
{
    std::cout << "\n-----Reading states ---------" << std::endl;
    std::string inputline =  StringExtensions::RemoveText(statesLine, STATES_FILE_TAG);
    MyList<std::string> states_str = StringExtensions::Split(inputline, DELIMETER);

    MyList<State>* states = new MyList<State>();

    for(int i = 0; i < states_str.Length(); i++)
        states->Push(State(states_str.At(i)));

    return states;
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

MyList<std::string>* NFA_FileReader::ReadTransitions(std::ifstream *myFile)
{
    std::cout << "\n-----Reading transitions ---------" << std::endl;

    std::string inputline;
    MyList<std::string>* transitions_str = new MyList<std::string>();

    while (getline(*myFile, inputline)) 
    {
        transitions_str->Push(inputline);
    }

    std::cout << "-----------------------" << std::endl;

    return transitions_str;
}