#include <sstream>
#include <iostream>

#include "util.h"

namespace Spellchecker
{
    int min(int a, int b, int c) {
        return std::min(a, std::min(b, c));
    }

    //get Levenshtein distance of two words (delete, insert, replace)
    int editDistance(const std::string& a, const std::string& b) {
        int m = a.length(), n = b.length();
        int dp[m+1][n+1];
    
        for (int i=0; i<=m; i++) {
            dp[i][0] = i;
        }
        for (int j=0; j<=n; j++) {
            dp[0][j] = j;
        }
    
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=n; j++) {
                if (a[i-1] != b[j-1]) {
                    dp[i][j] = min( 1 + dp[i-1][j],  // deletion
                                    1 + dp[i][j-1],  // insertion
                                    1 + dp[i-1][j-1] // replacement
                                );
                }
                else {
                    dp[i][j] = dp[i-1][j-1];
                }
            }
        }
        return dp[m][n];
    }

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

    const std::vector<char> punctuation = {',', '.', '"', '?', '!', ':', ';', '(', ')', '-', '^', '{', '}', '[', ']'};
    bool isPunctuation(const char c) {
        return std::find(punctuation.begin(), punctuation.end(), c) != punctuation.end();
    }

    std::string toLower(const std::string& word) {
        std::string lower = word;
        for (int i = 0; i < word.size(); i++) {
            lower[i] = std::tolower(word[i]);
        }
        return lower;
    }

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

    void getContext(std::vector<std::string> &line, int index, std::string &res) {
        int start = std::max(index - 2, 0);
        int end = std::min((int)line.size(), index + 2);

        for(int i = start; i < end; i++) {
            if(i == index) res += "\033[31m\033[4m"; // underline and set color to red
            res += line[i];
            if(i == index) res += "\033[24m\033[0m"; // reset color and end underline
            res += ' ';
        }
    }
}
