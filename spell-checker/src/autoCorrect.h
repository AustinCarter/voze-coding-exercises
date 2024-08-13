#pragma once

#include <string>

namespace Spellchecker {
    class Node {
    public: 
        Node(const std::string &word): word(word) {}
        Node() {}

        std::string& getWord() {
            return this->word;
        }

        Node* getChild(uint32_t dist) {
            return this->children[dist];
        }
        void addChild(uint32_t dist, Node* child) {
            this->children[dist] = child;
        }
    private:
        std::string word;
        std::unordered_map<uint32_t, Node*> children;

    };

    class AutoCorrect {
    public:
        AutoCorrect(const std::string &filename);
        std::vector<std::string>* getRecommendations(const std::string &word);

    private:
        void add(const std::string &word);
        void trickleDown(std::tuple<int, Node*> *heap);
        void bubbleUp(std::tuple<int, Node*> *heap, int index);
        Node *root; 
    };
}