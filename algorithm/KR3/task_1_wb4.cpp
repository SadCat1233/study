#include <iostream>
#include <vector>

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

    for (auto i = 0; i < length - 1; i++) {
        for (auto j = 0; j < length - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}