#include "dictionary.h"
#include <fstream>

bool isCapitalized(const std::string& word) {
    if(!std::isupper(word[0]))
       return false;
    for (int i = 1; i < word.size(); i++) {
        if (!std::islower(word[i])) {
            return false;
        }
    }
    return true;
}

std::string toLower(const std::string& word) {
    std::string lower = word;
    for (int i = 0; i < word.size(); i++) {
        lower[i] = std::tolower(word[i]);
    }
    return lower;
}

namespace Spellchecker {
    TrieNode::TrieNode() : terminal(false) {}

    void TrieNode::addChild(char c) {
        children[c] = new TrieNode();
    }

    TrieNode* TrieNode::getChild(char c) {
        return children[c];
    }

    Dictionary::Dictionary() {}

    bool Dictionary::check(const std::string& word) {
        return words.find(toLower(word)) != words.end() || isCapitalized(word);
    }
    
    void Dictionary::parseDictionary(const std::string& filename) {
        std::ifstream dictFile (filename);
        if(dictFile.is_open()) {
            std::string word;
            while (dictFile.good()) {
                dictFile >> word;
                this->addWord(word);
            }
            dictFile.close();
        }
    }

    void Dictionary::addWord(const std::string& word) {
        words.insert(toLower(word));
        TrieNode* current = &root;
        for (char c : word) {
            char lower = std::tolower(c);
            if (current->getChild(lower) == nullptr) {
                current->addChild(lower);
            }
            current = current->getChild(lower);
        }
        current->setTerminal(true);
    }
}