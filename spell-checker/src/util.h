#pragma once

#include <sstream>
#include <iostream>

namespace Spellchecker
{
    int min(int a, int b, int c);
    //get Levenshtein distance of two words (delete, insert, replace)
    int editDistance(const std::string& a, const std::string& b);
    bool isCapitalized(const std::string& word);
    bool isPunctuation(const char c);
    std::string toLower(const std::string& word);
    void splitString(const std::string &s, char delim, std::vector<std::string> &result);
    void joinString(const std::vector<std::string> &words, char delim, std::string &result);
    void getContext(std::vector<std::string> &line, int index, std::string &res);
    bool checkExtension(const std::string &s, const std::string &ext);
}
