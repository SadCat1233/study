#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        result.push_back({1});
        if (numRows == 1) return result;
        result.push_back({1, 1});
        for (int i = 3; i <= numRows; i++) {
            vector<int> temp(i);
            temp[0] = 1;
            temp[temp.size() - 1] = 1;
            for (int j = 1; j < i - 1; j++) {
                temp[j] = result[i - 2][j - 1] + result[i - 2][j];
            }
            result.push_back(temp);
        }
        return result;
    }
};

int main() {
    vector<int> nums = {0};
    int target = 7;
    Solution s;
    for (auto first : s.generate(5)) {
        for (auto second : first) {
            cout << second << " ";
        } 
        cout << endl;
    }
}