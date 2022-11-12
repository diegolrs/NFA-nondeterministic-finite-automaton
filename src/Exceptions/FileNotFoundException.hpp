#pragma once
#include "Exception.hpp"

class FileNotFoundException : Exception
{
    public:
        FileNotFoundException(std::string address)
        {
            _address = address;
        }

        std::string GetMessage()
        { 
            return "File was not found at address " + _address;
        }
    private:
        std::string _address;
};