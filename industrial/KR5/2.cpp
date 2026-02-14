#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    stack<char> stack1;
    string word;
    cin >> word;
    for (char c : word) {
        stack1.push(c);
    }
    int i = 0;
    while (i < stack1.size() / 2) {
        if (stack1.top() != word[i]) {
            cout << "no" << endl;
            return 0;
        }
        i++;
        stack1.pop();
    }
    cout << "yes";
    return 0;
}