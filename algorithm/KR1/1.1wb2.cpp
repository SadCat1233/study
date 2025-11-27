//1.1 рб2
#include <iostream>
#include <vector>

using namespace std;

int bin_search(vector<double>& arr, double t) {
    int first = 0; int last = arr.size() - 1; int mid; int mid_value;
    while (last >= first) {
        mid = (last + first) / 2;
        mid_value = arr[mid];
        if (mid_value == t) {
            cout << "Элемент найден" << endl;
            return mid + 1;
        }
        if (mid_value > t) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }
    arr.insert(arr.begin() + first, t);
    for (int j = 0; j < arr.size(); j++) {
        cout << arr[j] << " ";
    }
    cout << endl;
    cout << "Элемент не найден" << endl;
    return first + 1;
}

int main() {
    int n, target;
    cin >> n;
    vector<double> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    cin >> target;
    cout << bin_search(d, target);
    cout << " - позиция исходного элемента" << endl;
    return 0;
}