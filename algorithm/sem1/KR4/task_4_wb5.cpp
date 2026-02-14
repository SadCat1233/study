#include <iostream>

using namespace std;

int nod(int a, int b) {
    if (a == b) {
        return a;
    }
    if (a > b) {
        return nod(a - b, b);
    }
    return nod(a, b - a);
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << nod(a, b) << endl;
    return 0;
}