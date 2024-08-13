#include <iostream>
#include <fstream>

#include "util.h"
#include "dictionary.h"
#include "autoCorrect.h"


// <path to your program> dictionary.txt file-to-check.txt
int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " dictionary.txt file-to-check.txt" << std::endl;
        return 1;
    } 
    if(!Spellchecker::checkExtension(argv[1], ".txt")) {
        std::cerr << "Dictionary file must be of type .txt" << std::endl;
        return 1;
    } else if(!Spellchecker::checkExtension(argv[2], ".txt")) {
        std::cerr << "Dictionary file-to-check must be of type .txt" << std::endl;
        return 1;
    }



    Spellchecker::Dictionary dictionary;
    dictionary.parseDictionary(argv[1]);

    Spellchecker::AutoCorrect autoCorrect(argv[1]);
    std::vector<std::string> misspellings;
    std::ifstream text(argv[2]);
    std::string context;

    if (text.is_open()) {
        std::string line;
        std::vector<std::string> sentence = {}, tokenizedLine = {};
        int cursorRow = 0, cursorCol = 0;
        int wordIndex = 0;

        while (text.good()) {
            getline(text, line);
            Spellchecker::splitString(line, ' ', tokenizedLine);
            for (std::string &word : tokenizedLine) {
                if (!dictionary.check(word)) {
                    misspellings.push_back(word);
                    Spellchecker::getContext(tokenizedLine, wordIndex, context);
                    std::vector<std::string> *recs = autoCorrect.getRecommendations(word);
                    printf("row %d, col: %d \t %s \t\n", cursorRow, cursorCol, context.c_str());
                    std::cout << "\tsuggestions: ";
                    for(auto &rec : *recs) {
                        std::cout <<  "\033[32m\033[4m" << rec << "\033[24m\033[0m " ;
                    }
                    std::cout << std::endl;

                    context.clear();
                }
                wordIndex++;
                cursorCol += word.length() + 1;
            }
            tokenizedLine.clear();
            cursorRow++;
            cursorCol = 0, wordIndex = 0;
        }
        text.close();
    }
    return 0;
}