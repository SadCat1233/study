#include <iostream>

using namespace std;

int main() {
    int x;
    cin >> x;
    int n;
    cin >> n;
    int data[n + 2][(int)pow(2, n)];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < (int)pow(2, n); j++) {
            data[i][j] = 0;
        }
    }
    data[0][0] = x;
    for (int i = 0; i < n + 1; i++) {
        int ind = 0;
        int ind_new = 0;
        int counter = 1;
        while (data[i][ind] != 0) {
            cout << data[i][ind] << " ";
            if (data[i][ind] == data[i][ind + 1]) {
                counter++;
            }
            else {
                data[i + 1][ind_new] = counter;
                data[i+ 1][ind_new + 1] = data[i][ind];
                counter = 1;
                ind_new += 2;
            }
            ind++;
        }
        cout << endl;
    }
}