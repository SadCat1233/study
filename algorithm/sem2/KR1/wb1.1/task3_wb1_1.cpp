#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
        if (numbers[i] > mx) {
            mx = numbers[i];
        }
    }
    unordered_map<int, int> temp;
    for (int i = 0; i < n; i++) {
        temp[numbers[i]] += 1;
        if (temp[numbers[i]] > n / 2) {
            cout << numbers[i] << endl;
            return 0;
        }
    }
    return 0;
}