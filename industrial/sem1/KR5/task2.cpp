#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;

bool isValid(string s) {
    unordered_map<char, char> data = {
        {')', '('},
        {'}', '{'},
        {']', '['},
    };
    stack<char> tempStack;
    for (char c : s) {
        if (data.find(c) == data.end()) {
            tempStack.push(c);
        }
        else if (!tempStack.empty() && (tempStack.top() == data[c])) {
            tempStack.pop();
        }
        else {
            return false;
        }
    }
    return tempStack.empty();
}

int main() {
    string s;
    cin >> s;
    cout << isValid(s) << endl;
    return 0;
}