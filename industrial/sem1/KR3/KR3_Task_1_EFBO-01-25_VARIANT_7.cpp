#include <iostream>

using namespace std;

int sumDigits(int n) {
    if (n == 0) {
        return 0;
    }
    return 1 + sumDigits(n / 10);
}


int main() {
    int n;
    cin >> n;
    cout << sumDigits(abs(n)) << endl;
    return 0;
}