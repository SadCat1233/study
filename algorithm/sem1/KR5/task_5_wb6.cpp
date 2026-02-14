#include <iostream>
#include <unordered_map>

using namespace std;

char hashFunc(char data[], int n) {
    unordered_map<char, int> hashTable;
    for (int i = 0; i < n; i++) {
        if (hashTable.count(data[i])) {
            return data[i];
        }
        hashTable[data[i]] = 1;
    }
    return '~';
}

int main() {
    int n;
    cin >> n;
    char data[n];
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
    cout << hashFunc(data, n) << endl;
    return 0;
}