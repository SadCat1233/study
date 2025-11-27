#include <iostream>

using namespace std;

int climb(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    
    int data[n + 1];
    data[0] = 0;
    data[1] = 1;
    data[2] = 2;
    for (int i = 3; i < n + 1; i++) {
        data[i] = data[i - 1] + data[i - 2];
    }
    return data[n];
}


int main() {
    int n;
    cin >> n;
    cout << climb(n) << endl;
    return 0;
}