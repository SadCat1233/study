#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void hashFunc(string s) {
    unordered_map<char, int> data;
    for (auto i : s) {
        if (data.count(i)) {
            data[i]++;
        }
        else {
            data[i] = 1;
        }
    }
    for (auto& p : data) {
        cout << p.first << " " << p.second << endl;
    }
}


int main() {
    string s;
    cin >> s;
    hashFunc(s);
    return 0;
}