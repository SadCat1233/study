#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    int data[n][n];
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if ((i + j) < (n - 1)) {
                data[i][j] = 0;
            }
            if (i + j == n - 1) {
                data[i][j] = 1;
            }
            if (i + j > n - 1) {
                data[i][j] = 2;
            }
        }
    }
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}