#include <LookAndSay.hpp>
#include <iostream>
#include <string>
#include <sstream>

std::string LookAndSay::next(const std::string& current)
{
    std::stringstream ss;
   
    const auto length = current.length();
    auto current_number = current[0];
    auto consecutive_length = 1;
    for (auto index = 1u; index < length; index++) {
        if (current_number == current[index]) {
            consecutive_length++;
        } else {
            ss << consecutive_length << current_number;
            consecutive_length = 1;
        }
        current_number = current[index];
   }
   ss << consecutive_length << current_number;

   return ss.str();
}
