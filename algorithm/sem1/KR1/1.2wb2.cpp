//1.2 рб2
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<double> d;
    for (int i = 0; i < n; i++) {
        double temp;
        cin >> temp;
        d.push_back(temp);
    }
    if (n < 3) {
        cout << "Массив слишком короткий" << endl;
        return 0;
    }
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (d[mid] < d[mid + 1]) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    int peak = left;
    if ((peak == 0) || (peak == d.size() - 1)) {
        cout << "Пик не может быть первым или последним элементом" << endl;
        return 0;
    }
    for (int i = 0; i < peak + 1; i++) {
        if (d[i] <= d[i - 1]) {
            cout << "Массив не горный" << endl;
            return 0;
        }
    }
    for (int i = peak + 1; i < d.size(); i++) {
        if (d[i] >= d[i - 1]) {
            cout << "Массив не горный" << endl;
            return 0;
        }
    }
    cout << "Первый пик - " << peak + 1 << endl; 
}
