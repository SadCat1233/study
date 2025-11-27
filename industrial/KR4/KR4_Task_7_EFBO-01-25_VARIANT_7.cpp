#include <iostream>

using namespace std;

bool f(int halfSum, int data[], int ind, int s1, int s2, int size) {
    if (s1 == s2 && s1 == halfSum) {
        return true;
    }
    if (ind == size) {
        return false;
    }
    if (s1 > halfSum || s2 > halfSum) {
        return false;
    }
    return f(halfSum, data, ind + 1, s1 + data[ind], s2, size) || f(halfSum, data, ind + 1, s1, s2 + data[ind], size);
}


int main() {
    int n, s = 0;
    cin >> n;
    int data[n];
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        s += data[i];
    }
    if (s % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }
    cout << f(s, data, 0, 0, 0, n) << endl;
    return 0;
}