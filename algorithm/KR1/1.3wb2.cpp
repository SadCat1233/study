//1.3 рб2
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bin_search(vector<double>& arr, double t) {
    int first = 0; int last = arr.size() - 1; int mid; int mid_value;
    while (last >= first) {
        mid = (last + first) / 2;
        mid_value = arr[mid];
        if (mid_value == t) {
            return mid + 1;
        }
        if (mid_value > t) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }
    return first;
}

int main() {
    int n; int target = 0; int i = 0;
    cin >> n;
    vector<double> d(n);
    while (i < d.size()) {
        cin >> d[i];
        if (d[i] == 0) {
            d.erase(d.begin() + i);
        }
        else {
            i++;
        }
    }
    n = d.size();
    cout << max(bin_search(d, target), n - bin_search(d, target)) << endl;
    return 0;
}

