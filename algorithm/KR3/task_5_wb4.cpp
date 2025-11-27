#include <iostream>
#include <vector>
using namespace std;
 
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

int main() {
    int length;
    cin >> length;
    vector<int> numbers;
    for (int i = 0; i < length; i++) {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
    shellSort(numbers);
    for (auto i : numbers) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}