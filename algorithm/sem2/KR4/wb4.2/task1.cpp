#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct TrieNode {
    bool isWord = false;
    unordered_map<char, unique_ptr<TrieNode>> next;
};

class Trie {
private:
    TrieNode root;

    bool erase(TrieNode* node, const string& word, int index) {
        if (index == static_cast<int>(word.size())) {
            if (!node->isWord) {
                return false;
            }

            node->isWord = false;
            return node->next.empty();
        }

        char symbol = word[index];
        auto child = node->next.find(symbol);

        if (child == node->next.end()) {
            return false;
        }

        bool shouldDeleteChild = erase(child->second.get(), word, index + 1);

        if (shouldDeleteChild) {
            node->next.erase(symbol);
        }

        return !node->isWord && node->next.empty();
    }

public:
    void insert(const string& word) {
        TrieNode* current = &root;

        for (char symbol : word) {
            if (!current->next.count(symbol)) {
                current->next[symbol] = make_unique<TrieNode>();
            }

            current = current->next[symbol].get();
        }

        current->isWord = true;
    }

    bool search(const string& word) const {
        const TrieNode* current = &root;

        for (char symbol : word) {
            auto child = current->next.find(symbol);

            if (child == current->next.end()) {
                return false;
            }

            current = child->second.get();
        }

        return current->isWord;
    }

    void erase(const string& word) {
        erase(&root, word, 0);
    }
};

int main() {
    int n;
    cin >> n;

    Trie trie;

    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        trie.insert(word);
    }

    string wordToDelete;
    cin >> wordToDelete;

    trie.erase(wordToDelete);

    cout << (trie.search(wordToDelete) ? "YES" : "NO") << endl;

    return 0;
}
