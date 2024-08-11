#include <iostream>

#include "dictionary.h"

// <path to your program> dictionary.txt file-to-check.txt
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " dictionary.txt file-to-check.txt" << std::endl;
        return 1;
    }

    Spellchecker::Dictionary dictionary;    
    dictionary.parseDictionary(argv[1]);

    std::vector<std::string> misspellings;

    std::vector<std::string> words = {"hello", "HELLO", "hELLO", "diglal", "garfunkle", "Garfunkle", "hemp"};
    for(const std::string& word : words) {
        if(!dictionary.check(word)) {
            misspellings.push_back(word);
        } 
    }

    for(const std::string& misspelling : misspellings) {
        std::cout << misspelling << " is misspelled." << std::endl;
    }
    return 0;
}