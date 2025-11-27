#include <iostream>
#include <string>

using namespace std;

int main() {
    string word1, word2;
    cin >> word1;
    cin >> word2;
    int data[word1.length() + 1][word2.length() + 1];
    for (int i = 0; i < word2.length() + 1; i++) {
        data[0][i] = i;
    }
    for (int i = 0; i < word1.length() + 1; i++) {
        data[i][0] = i;
    }
    for (int i = 1; i <= word1.length(); i++) {
        for (int j = 1; j <= word2.length(); j++) {
            int temp = word1[i - 1] == word2[j - 1] ? 0 : 1;
            data[i][j] = min(data[i][j - 1] + 1, data[i - 1][j] + 1);
            data[i][j] = min(data[i][j], data[i - 1][j - 1] + temp);
        }
    }
    cout << data[word1.length()][word2.length()] << endl;
    return 0;
}