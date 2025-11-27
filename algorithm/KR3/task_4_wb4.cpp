#include <iostream>
#include <vector>

using namespace std;


void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int min_index = i;
        for (int j = i; j < arr.size(); j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
}


int main() {
    int length;
    cin >> length;
    vector<int> numbers;
    for (auto i = 0; i < length; i++) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    for (auto i = 0; i < length; i++) {
        int min_index = i;
        for (auto j = i; j < length; j++) {
            if (numbers[min_index] > numbers[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = numbers[min_index];
            numbers[min_index] = numbers[i];
            numbers[i] = temp;
        }
    }

    for (auto i : numbers) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}