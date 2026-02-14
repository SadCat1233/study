#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

void unreturned(vector<int> given, unordered_set<int> returned, int n) {
    for (int i = 0; i < n; i++) {
        if (returned.find(given[i]) == returned.end()) {
            cout << given[i] << " ";
        }
    }
    cout << endl;
}


int main() {
    int n;
    cin >> n;
    vector<int> given;
    unordered_set<int> returned;
    for (auto i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        given.push_back(elem);
    }
    string returned_string;
    cin.ignore();
    getline(cin, returned_string);
    stringstream ss(returned_string);
    string num;
    while (ss >> num) {
        returned.insert(stoi(num));
    }
    unreturned(given, returned, n);
    return 0;
}