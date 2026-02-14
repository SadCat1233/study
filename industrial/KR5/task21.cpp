#include <iostream>
#include <stack>

using namespace std;

bool isUniqueStack(stack<int> s, int num) {
    while (!s.empty()) {
        if (s.top() == num) {
            return false;
        }
        s.pop();
    }
    return true;
}


int main() {
    stack<int> s;
    s.push(2);
    s.push(11);
    s.push(7);
    cout << isUniqueStack(s, 5) << endl;
    cout << isUniqueStack(s, 7) << endl;
    return 0;
}