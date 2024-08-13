#include <fstream>

#include "dictionary.h"
#include "util.h"

namespace Spellchecker {
    Dictionary::Dictionary() {}

    bool Dictionary::check(const std::string& word) {
        std::string w = word;
        while(isPunctuation(w[w.length()-1])) {
            w = w.substr(0, w.length()-1);
        }
        while(isPunctuation(w[0])) {
            w = w.substr(1);
        }
        if(w.length() == 0) return true;
        return words.find(toLower(w)) != words.end() || isCapitalized(w);
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
    }
}