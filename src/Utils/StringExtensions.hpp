#pragma once
#include <string>

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
}