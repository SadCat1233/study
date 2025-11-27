//Group: EFBO-01-25
//Student: Gamaev Pavel

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }
}