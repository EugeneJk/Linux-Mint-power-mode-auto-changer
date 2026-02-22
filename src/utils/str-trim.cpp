#include "str-trim.hpp"
#include <algorithm>
#include <cctype>
#include <string>

std::string strTrim(std::string s)
{
    auto notSpace = [](unsigned char ch)
    {
        return !std::isspace(ch);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());

    return s;
}
