#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


struct TrieNode
{
    TrieNode* children[26]; 
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};


int charToIndex(char ch) {
    return ch - 'a';
}


void insert(TrieNode* root, const string& word) {
    TrieNode* current = root;
    
    for (char ch : word) {
        int index = charToIndex(ch);
        
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }
    current->isEndOfWord = true;
}

int countPath(TrieNode* root, const string& word){
    int count = 0;

    for (char c : word){
        int idx = charToIndex(c);
        root = root->children[idx];
        if (root->isEndOfWord) count++;
    }

    return count;
}


int main(){

    vector<string> inputWord = {"a", "ab", "abc", "abcd", "abcdef", "bcd"};

    TrieNode* root = new TrieNode();

    for (auto word : inputWord){
        insert(root, word);
    }

    int maxCount = -1;

    for (auto word : inputWord){
        int cnt = countPath(root, word) - 1; // само слово не учитываем
        if (cnt > maxCount){
            maxCount = cnt;
        }
    }

    for (auto word : inputWord){
        int cnt = countPath(root, word) - 1; // само слово не учитываем
        if (cnt == maxCount){
            cout << word;
        }
    }


    return 0;
}