#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int data[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) < (n - 1)) {
                data[i][j] = 0;
            }
            else if ((i + j) > (n - 1)) {
                data[i][j] = 2;
            }
            else {
                data[i][j] = 1;
            }
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}