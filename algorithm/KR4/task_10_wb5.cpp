#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& data, int low, int high) {
    if (low < high) {
        int pivot = data[high];
        int i = low - 1;
        for (auto j = low; j < high; j++) {
            if (data[j] < pivot) {
                i++;
                swap(data[j], data[i]);
            }
        }
        swap(data[i + 1], data[high]);
        i = i + 1;

        quickSort(data, low, i - 1);
        quickSort(data, i + 1, high);
    }
}


int main() {
    
    int length;
    cin >> length;
    vector<int> data;
    for (auto i = 0; i < length; i++) {
        int temp;
        cin >> temp;
        data.push_back(temp);
    }
    quickSort(data, 0, length - 1);
    for (auto num = 0; num < length; num++) {
        cout << data[num] << " ";
    }
    return 0;
}