#include <iostream>
#include <vector>

using namespace std;

void heapify(vector<int>& arr, int size, int index) {
    while (true) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap(arr[index], arr[largest]);
        index = largest;
    }
}

void heapSort(vector<int>& arr) {
    int size = arr.size();

    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    heapSort(arr);

    for (int value : arr) {
        cout << value << " ";
    }

    return 0;
}

/*
Пирамидальная Heap Sort	O(n log n)	O(n log n)	O(n log n)	O(1)
Пузырьковая	            O(n)	    O(n^2)	    O(n^2)	    O(1)
Вставками	            O(n)	    O(n^2)	    O(n^2)	    O(1)
Выбором	                O(n^2)	    O(n^2)	    O(n^2)	    O(1)
Быстрая Quick Sort	    O(n log n)	O(n log n)	O(n^2)	    O(log n)
*/