#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    int sum = 0;
    cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }

    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }

    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = target; j >= nums[i]; j--) {
            dp[j] = dp[j] || dp[j - nums[i]];
        }
    }

    if (dp[target])
        cout << "YES";
    else
        cout << "NO";

    return 0;
}