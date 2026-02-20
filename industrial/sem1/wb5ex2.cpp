#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int n = a - b;
    string data[n];
    for (int i = 0; i < n; i++) {
        data[i] = "0";
    }
    int ind = 0;
    while (a > b) {
        if (a % 2 != 0) {
            a = a - 1;
            data[ind] = "-1";
            ind++;
        }
        a = a / 2;
        data[ind] = ":2";
        ind++;
    }
    while (a != b) {
        a = a - 1;
        data[ind] = "-1";
        ind++;
    }
    int j = 0;
    while (data[j] != "0") {
        cout << data[j];
        j++;
    }
}