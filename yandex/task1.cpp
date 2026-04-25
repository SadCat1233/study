#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<char, priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>>> minHeapMap;
    int n, k;
    cin >> n >> k;
    for (auto i = 0; i < n; i++) {
        string word;
        cin >> word;
        minHeapMap[word[0]].push({0, word});
    }
    for (auto i = 0; i < k; i++) {
        char symbol;
        cin >> symbol;

        auto& minHeap = minHeapMap[symbol];
        auto [counter, word] = minHeap.top();
        minHeap.pop();
        minHeap.push({counter + 1, word});
        cout << word << "\n";
    }
}