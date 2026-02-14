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

    for (int i = 1; i < length; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}