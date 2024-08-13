#include <fstream>
#include <iostream>
#include <tuple>

#include "autoCorrect.h"

// the max edit distance a mispelling can from a word and still be considered
#define TOLERENCE 3
// the max number of spelling recommendations to make
#define NUM_RECS 3

int min(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}

//get Levenshtein distance of two words
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

namespace Spellchecker {
    AutoCorrect::AutoCorrect(const std::string &filename)  {
        this->root = nullptr;

        std::ifstream dictionary (filename);
        if(dictionary.is_open()) {
            std::string word;
            while (dictionary.good()) {
                dictionary >> word;
                this->add(word);
            }
            dictionary.close();
        }
    }

    void AutoCorrect::add(const std::string &word) {
        Node *child = new Node(word);

        if(!this->root) {
            this->root = child;
            return;
        }

        Node* parent = this->root;
    
        while(true) {
            int dist = editDistance(child->getWord(),parent->getWord());
            //already in tree
            if(dist == 0) return;
        
            if (!parent->getChild(dist)) {
                parent->addChild(dist, child);
                return;
            }
            else {
                parent = parent->getChild(dist);
            }
        }
   }

   std::vector<std::string>* AutoCorrect::getRecommendations(const std::string &word) {

        std::tuple<int, Node*> heap[NUM_RECS];
        int heapIndex = 0;

        std::vector<Node*> stack;    
        stack.push_back(this->root);
        Node *curr;

        int tol = std::min(TOLERENCE, (int)word.length());

        while(stack.size() > 0) {
           curr = stack.back();
           stack.pop_back();

        //    if(!curr) return recs;

           int dist = editDistance(curr->getWord(), word);

            if(dist <= tol) {
                if(heapIndex < NUM_RECS) {
                    heap[heapIndex] = std::make_tuple(dist, curr);

                    int i = heapIndex;
                    while((i/2)-1 > 0 && std::get<0>(heap[(i/2)-1]) < std::get<0>(heap[i])) {
                        int parentI = (i/2)-1;
                        auto n = heap[i];
                        heap[i] = heap[parentI];
                        heap[parentI] = n;
                        i = parentI;
                    }

                    heapIndex++;
                } else if(dist < std::get<0>(heap[0])) {
                    // std::cout << "modifying heap " << curr->getWord() << " is closer to " << word << " than " << std::get<0>(heap[0]) << std::endl;
                    heap[0] = std::make_tuple(dist, curr);
                    int i = 0;
                    while(i * 2 + 1 < NUM_RECS) {
                        int leftIndex = i * 2 + 1;
                        int rightIndex = i * 2 + 2;

                        auto n = heap[i];
                        int largeChild = leftIndex;

                        if(rightIndex < NUM_RECS && std::get<0>(heap[rightIndex]) > std::get<0>(heap[largeChild])) {
                            largeChild = rightIndex;
                        }

                        if(std::get<0>(heap[i]) > std::get<0>(heap[largeChild])) break;
                        heap[i] = heap[largeChild];
                        heap[largeChild] = n;
                        i = largeChild;
                    }
                }
                // recs->push_back(curr->getWord());
                // printf("adding rec %s for word %s\n", curr->getWord().c_str(), word.c_str());
            }

            // any node within [dist - TOLERENCE, dist + TOLERENCE] could be within the tolerence of our misspelling
            int start = dist - tol;
            if (start < 0) start = 1;

            while (start <= dist + tol) {
                Node* next = curr->getChild(start);
                if(next) stack.push_back(next);
                start++;
            }
        }

        auto recs = new std::vector<std::string>();

        for(auto &t : heap) {
            Node* n;
            std::tie(std::ignore, n) = t;
            recs->push_back(n->getWord());
        }

        return recs;
   }
}