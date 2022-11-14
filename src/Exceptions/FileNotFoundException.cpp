#include "FileNotFoundException.hpp"

FileNotFoundException::FileNotFoundException(std::string address)
{
    _address = address;
}

std::string FileNotFoundException::GetMessage()
{ 
    return "File was not found at address " + _address;
}