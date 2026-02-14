#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


void bubbleSort(vector<int>& arr) {
    int temp;

    for (int i = 0; i < (arr.size() - 1); i++) {
        for (int j = 0; j < (arr.size() - i - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


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


void shellSort(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];  
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}


void cocktailSort(vector<int>& arr) {
    int temp;
    for (int i = 0; i < (arr.size() / 2); i++) {
        for (int j = i; j < (arr.size() - i - 1); j++) {
            if (arr[j] > arr[j + 1]) {
                arr[j] = arr[j] + arr[j + 1];
                arr[j + 1] = arr[j] - arr[j + 1];
                arr[j] = arr[j] - arr[j + 1];
            }
        }
        for (int j = (arr.size() - i - 2); j >= i + 1; j--) {
            if (arr[j] < arr[j - 1]) {
                arr[j] = arr[j] + arr[j - 1];
                arr[j - 1] = arr[j] - arr[j - 1];
                arr[j] = arr[j] - arr[j - 1];
            }
        } 
    }
}


void inserionSort(vector<int>& arr) {
    for (int i = 1; i < (arr.size()); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


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
    vector<int> arr;
    vector<int> arr1;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 1000);
    }
    for (int i = 0; i < n * 10; i++) {
        arr.push_back(rand() % 1000);
    }
    auto begin = chrono::steady_clock::now();
    bubbleSort(arr);
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Bubble short - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    inserionSort(arr);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Insertion short - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    selectionSort(arr);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Selection short - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    shellSort(arr);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Shell short - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    cocktailSort(arr);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Cocktail short - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    quickSort(arr, 0, n - 1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Quick short - " << time.count() << endl;

    cout << endl << endl;

    begin = chrono::steady_clock::now();
    bubbleSort(arr1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Bubble long - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    inserionSort(arr1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Insertion long - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    selectionSort(arr1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Selection long - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    shellSort(arr1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Shell long - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    cocktailSort(arr1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Cocktail long - " << time.count() << endl;

    begin = chrono::steady_clock::now();
    quickSort(arr1, 0, n * 10 - 1);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "Quick long - " << time.count() << endl;

    return 0;
}