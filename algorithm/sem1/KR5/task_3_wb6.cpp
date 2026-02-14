#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

pair<int, int> hashFunc(vector<int>& data, int target) {
    unordered_map<int, int> hashTable;
    for (auto i = 0; i < (int)data.size(); i++) {
        int x = target - data[i];
        if (hashTable.count(x)) {
            return {hashTable[x], i};
        }
        hashTable[data[i]] = i;
    }
    return {-1, -1};
} 


int main() {
    int n, target;
    cin >> n;
    vector<int> data;
    for (auto i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        data.push_back(temp);
    }
    cin >> target;
    cout << hashFunc(data, target).first << " " << hashFunc(data, target).second << endl;
    return 0;
}