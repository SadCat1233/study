#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const long long unsigned int MAX_SUM = 18446744073709551615;


bool half(const vector<int>& arr, int valuesSum) {
    if (valuesSum % 2 != 0) return false;
    int target = valuesSum / 2;

    if (target > MAX_SUM) return false;

    bitset<MAX_SUM + 1> dp;
    dp[0] = 1;

    for (int number : arr) {
        dp |= (dp << number);
    }

    return dp[target];
}

int main() {
    int num, value;
    int valuesSum = 0;

    cin >> num;
    vector<int> arr(num);

    for (int i = 0; i < num; i++) {
        cin >> value;
        if (value < 0) { 
            cout << "NO";
            return 0;
        }
        valuesSum += value;
        arr.push_back(value);
    }

    cout << (half(arr, valuesSum) ? "YES\n" : "NO\n");
    return 0;
}
