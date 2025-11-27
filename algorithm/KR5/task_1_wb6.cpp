#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int data[7] = {86, 90, 27, 29, 38, 30, 40};
    vector<vector<int>> answer(7);
    for (auto i : data) {
        answer[i % 7].push_back(i);
    }
    for (auto i : answer) {
        if (i.empty()) {
            cout << 0;
        }
        else {
            for (auto j : i) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
    return 0;
}