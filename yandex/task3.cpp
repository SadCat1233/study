#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<pair<long long, long long>> coords(n);
    for (auto& [x, y] : coords) {
        cin >> x >> y;
        x = abs(x);
        y = abs(y);
    }
    sort(coords.begin(), coords.end(), greater<>());
    long long INF = 1e18;
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        long long max_y = 0;
        for (int j = i - 1; j >= 0; j--) {
            max_y = max(max_y, coords[j].second);
            if (dp[j] != INF)
                dp[i] = min(dp[i], dp[j] + 4LL * coords[j].first * max_y);
        }
    }

    cout << dp[n] << "\n";
}