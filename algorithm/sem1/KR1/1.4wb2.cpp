//1.4 рб2
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<double> arr;
    vector<int> ans;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double num;
        cin >> num;
        arr.push_back(num);
    }
    vector<double> temp(arr.size());
    copy(arr.begin(), arr.end(), temp.begin());
    temp.erase(temp.begin());
    sort(temp.begin(), temp.end());
    for (int i = 0; i < n - 1; i++) {
        int index = -1;
        int first = 0; int last = temp.size() - 1; double target = arr[0]; double mid_value; int mid;
        while (last >= first) {
            mid = (last + first) / 2;
            mid_value = temp[mid];
            if (mid_value == target) {
                index = mid;
                break;
            }
            if (mid_value > target) {
                last = mid - 1;
            }
            else {
                first = mid + 1;
            }
        }
        if (index == -1) {
            index = first;
        }
        ans.push_back(index);
        arr.erase(arr.begin());
        target = arr[0];
        copy(arr.begin(), arr.end(), temp.begin());
        temp.erase(temp.begin());
        sort(temp.begin(), temp.end());
    }
    for (int j = 0; j < n; j++) {
        cout << ans[j];
    }
    return 0;
}