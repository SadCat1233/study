#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


string project(int i, int sub, int m, vector<string> input) {
    string res;
    for (int k = 0; k < m; k++) {
        if (sub >> k & 1) res += input[i][k];
    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> input(n);
    for (int i = 0; i < n; i++) cin >> input[i];

    vector<int> masks(n);
    for (int i = 0; i < n; i++) {
        int mask = 0;
        for (int k = 0; k < m; k++)
            if (input[i][k] != '?') mask |= (1 << k);
        masks[i] = mask;
    }

    int maskSize = 1 << m;

    vector<vector<int>> group(maskSize);
    for (int i = 0; i < n; i++) group[masks[i]].push_back(i);

    long long ans = 0;

    for (int fisrtGroupMask = 0; fisrtGroupMask < maskSize; fisrtGroupMask++) {
        if (group[fisrtGroupMask].empty()) continue;
        for (int secondGroupMask = fisrtGroupMask; secondGroupMask < maskSize; secondGroupMask++) {
            if (group[secondGroupMask].empty()) continue;
            int inter = fisrtGroupMask & secondGroupMask;
            
            if (fisrtGroupMask == secondGroupMask) {
                unordered_map<string,long long> cnt;
                for (int i : group[fisrtGroupMask]) cnt[project(i, inter, m, input)]++;
                for (auto& [s, c] : cnt) ans += c * (c - 1) / 2;
            } else {
                unordered_map<string,long long> cntA, cntB;
                for (int i : group[fisrtGroupMask]) cntA[project(i, inter, m, input)]++;
                for (int j : group[secondGroupMask]) cntB[project(j, inter, m, input)]++;
                for (auto& [s, c] : cntA)
                    if (cntB.count(s)) ans += c * cntB[s];
            }
        }
    }

    cout << ans << "\n";
    return 0;
}