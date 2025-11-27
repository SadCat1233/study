#include <iostream>
#include <vector>

using namespace std;

void insertionBinary(vector<int> &data) {
    int length = data.size();
    for (int i = 1; i < length; ++i) {
        int key = data[i];
        int low = 0, high = i - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (key < data[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (int j = i - 1; j >= low; --j) {
            data[j + 1] = data[j];
        }
        data[low] = key;
    }
}

int main() {
    int n;
    vector<int> data;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        data.push_back(elem);
    }
    insertionBinary(data);
    for (auto num : data) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
