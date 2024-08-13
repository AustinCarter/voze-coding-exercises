#pragma once

#include <string>
#include <unordered_set>

namespace Spellchecker {
    class Dictionary {
    public:
        Dictionary();
        bool check(const std::string& word);
        void addWord(const std::string& word);
        void parseDictionary(const std::string& filename);
        
    private:
        std::unordered_set<std::string> words;
    };
}