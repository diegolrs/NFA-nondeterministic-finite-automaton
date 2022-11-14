#pragma once
#include "Exception.hpp"

class FileNotFoundException : Exception
{
    public:
        FileNotFoundException(std::string address);
        std::string GetMessage();
    private:
        std::string _address;
};