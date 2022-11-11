#pragma once

#include <iostream>
#include <string>

class Exception 
{
    public:
        virtual std::string GetMessage() = 0;
};