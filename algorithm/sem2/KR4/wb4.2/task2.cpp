#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct TrieNode {
    bool isEnd = false;
    unordered_map<char, int> next;
};

vector<TrieNode> trie(1);

bool isNumber(const string& value) {
    if (value.empty()) {
        return false;
    }

    for (char symbol : value) {
        if (symbol < '0' || symbol > '9') {
            return false;
        }
    }

    return true;
}

void insertWord(const string& word) {
    int current = 0;

    for (char symbol : word) {
        if (!trie[current].next.count(symbol)) {
            trie[current].next[symbol] = trie.size();
            trie.push_back(TrieNode());
        }

        current = trie[current].next[symbol];
    }

    trie[current].isEnd = true;
}

vector<string> getPrefixes(const string& word) {
    vector<string> prefixes;
    int current = 0;
    string prefix;

    for (int i = 0; i + 1 < static_cast<int>(word.size()); i++) {
        char symbol = word[i];

        if (!trie[current].next.count(symbol)) {
            break;
        }

        current = trie[current].next[symbol];
        prefix += symbol;

        if (trie[current].isEnd) {
            prefixes.push_back(prefix);
        }
    }

    return prefixes;
}

int countExistingPrefixes(const string& word) {
    int count = 0;
    int current = 0;

    for (int i = 0; i + 1 < static_cast<int>(word.size()); i++) {
        char symbol = word[i];

        if (!trie[current].next.count(symbol)) {
            break;
        }

        current = trie[current].next[symbol];

        if (trie[current].isEnd) {
            count++;
        }
    }

    return count;
}

int main() {
    vector<string> input;
    string token;

    while (cin >> token) {
        input.push_back(token);
    }

    if (input.empty()) {
        return 0;
    }

    vector<string> words;

    if (isNumber(input[0]) && input.size() > 1) {
        int n = stoi(input[0]);

        for (int i = 1; i <= n && i < static_cast<int>(input.size()); i++) {
            words.push_back(input[i]);
        }
    } else {
        words = input;
    }

    for (const string& word : words) {
        insertWord(word);
    }

    string bestWord;
    int bestCount = -1;

    for (const string& word : words) {
        int currentCount = countExistingPrefixes(word);

        if (currentCount > bestCount ||
            (currentCount == bestCount && word.size() > bestWord.size())) {
            bestCount = currentCount;
            bestWord = word;
        }
    }

    cout << bestWord << " (Префиксы: ";

    vector<string> prefixes = getPrefixes(bestWord);

    for (int i = 0; i < static_cast<int>(prefixes.size()); i++) {
        if (i > 0) {
            cout << ", ";
        }

        cout << prefixes[i];
    }

    cout << ")" << endl;

    return 0;
}
