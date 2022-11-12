#pragma once
#include <string>
#include <cstring>
#include "MyList.hpp"

namespace StringExtensions
{
    inline bool Contains(std::string s1, std::string s2)
    {
        return (s1.find(s2) != std::string::npos);
    }

    inline std::string RemoveText(std::string text, std::string toRemove)
    {
        int found = -1;

        do
        {
            found = text.find(toRemove, found+1);

            if(found != -1)
            {
                text = text.substr(0, found) + text.substr(found+toRemove.length());
            }

        } while (found != -1);
        
        return text;
    }

    inline MyList<std::string> Split(std::string text, std::string delimiter)
    {
        MyList<std::string> l = MyList<std::string>();

        char *dup = (char*) text.c_str(); // duplicating string as char*
        const char *delimiter_ptr = delimiter.c_str();
        char *ptr = strtok(dup, delimiter_ptr); 

        while (ptr != NULL)
        {
            // Convert to string and push on list
            std::string myString;
            myString.assign(ptr);
            l.Push(myString); 

            ptr = strtok (NULL, delimiter_ptr); 
        }

        free(dup); // releasing duplicated string

        return l;
    }
}