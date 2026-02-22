#include "str-empty-checker.hpp"
#include "str-trim.hpp"
#include <string>

/* Check uset text for empty */
std::optional<std::string> strEmptyChecker(const std::string &value)
{
    std::string result = strTrim(value);
    if (result.empty())
        return std::nullopt;
    return result;
}
