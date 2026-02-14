#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int length;
    cin >> length;
    vector<int> arr;

    for (auto i = 0; i < length; i++) {
        int elem;
        cin >> elem;
        arr.push_back(elem);
    }

    int temp;
    for (auto i = 0; i < length / 2; i++) {
        for (auto j = i; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                arr[j] = arr[j] + arr[j + 1];
                arr[j + 1] = arr[j] - arr[j + 1];
                arr[j] = arr[j] - arr[j + 1];
            }
        }
        for (auto j = length - i - 2; j >= i + 1; j--) {
            if (arr[j] < arr[j - 1]) {
                arr[j] = arr[j] + arr[j - 1];
                arr[j - 1] = arr[j] - arr[j - 1];
                arr[j] = arr[j] - arr[j - 1];
            }
        } 
    }

    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}