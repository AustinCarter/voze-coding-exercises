#include <iostream>
#include <fstream>

#include "dictionary.h"
#include "util.h"


void getContext(std::vector<std::string> &line, int index, std::string &res) {
    int start = std::max(index - 2, 0);
    int end = std::min((int)line.size(), index + 2);

    for(int i = start; i < end; i++) {
        if(i == index) res += "\033[31m\033[4m";
        res += line[i];
        if(i == index) res += "\033[24m\033[0m";
        res += ' ';
    }
}

// <path to your program> dictionary.txt file-to-check.txt
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " dictionary.txt file-to-check.txt" << std::endl;
        return 1;
    }

    Spellchecker::Dictionary dictionary;
    dictionary.parseDictionary(argv[1]);

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
                    getContext(tokenizedLine, wordIndex, context);
                    printf("misspelled %s: row %d, col: %d \n \t %s\n", word.c_str(), cursorRow, cursorCol, context.c_str());
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