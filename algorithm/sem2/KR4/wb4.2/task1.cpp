#include <iostream>
#include <string>
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

bool eraseWord(TrieNode* root, const string& word) { // приведенная функиция НЕ будет удалять узлы если это возможно (отуствие детей и не конец другого слова), тк в задание не уточняется это
    TrieNode* cur = root;

    for (char c : word) {
        if (c < 'a' || c > 'z') return false;

        int idx = charToIndex(c);
        if (!cur->children[idx]) return false;
        
        cur = cur->children[idx];
    }
    if (!cur->isEndOfWord) return false;       
    cur->isEndOfWord = false;
    return true;
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

bool search(TrieNode* root, const string& word) {
    TrieNode* current = root;
    
    for (char ch : word) {
        int index = charToIndex(ch);
        
        if (current->children[index] == nullptr) {
            return false;
        }
        current = current->children[index];
    }

    return (current != nullptr && current->isEndOfWord);
}

int main(){

    string word = "hello";

    TrieNode* root = new TrieNode();

    insert(root, "hello");
    insert(root, "privet");
    insert(root, "car");
    insert(root, "podushka");

    cout << search(root, word) << endl; // 1 - слово найдено
    eraseWord(root, word); // удаляем логически слово
    cout << search(root, word) << endl; // 0 - слово не найдено


    return 0;
}