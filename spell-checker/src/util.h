#include <sstream>
#include <iostream>

namespace Spellchecker
{
    void splitString(const std::string &s, char delim, std::vector<std::string> &result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim)) {
            result.push_back(item);
        }
    }

    void joinString(const std::vector<std::string> &words, char delim, std::string &result) {
        for (std::string word : words) {
            result += word + delim;
        }
    }
}
