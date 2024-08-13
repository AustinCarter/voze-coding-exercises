#pragma once

#include <string>
#include <unordered_set>

namespace Spellchecker {
    class TrieNode {
    public:
        TrieNode();
        void addChild(char c);
        TrieNode* getChild(char c);
        void setTerminal(bool terminal) { this->terminal = terminal; }
    private:
        std::unordered_map<char, TrieNode*> children;
        bool terminal; 
    };
    class Dictionary {
    public:
        Dictionary();
        bool check(const std::string& word);
        void addWord(const std::string& word);
        void parseDictionary(const std::string& filename);
        
    private:
        std::unordered_set<std::string> words;
        TrieNode root;
    };
}