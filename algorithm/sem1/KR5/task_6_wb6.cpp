#include <iostream>
#include <unordered_map>

using namespace std;

char hashFunc(char data[], int n) {
    unordered_map<char, int> hashTable;
    char answer;
    for (int i = 0; i < n; i++) {
        hashTable[data[i]]++;
        if (hashTable[data[i]] == 2) {
            hashTable.erase(data[i]);
            answer = hashTable.begin()->first;
        }
    }
    return answer;
}


int main() {
    int n;
    cin >> n;
    string inputString;
    cin >> inputString;
    char data[n];
    for (int i = 0; i < n; i++) {
        data[i] = (char)inputString[i];
    }
    cout << hashFunc(data, n) << endl;
    return 0;
}