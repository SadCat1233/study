#include <vector>
#include <iostream>

using namespace std;

vector<int> sortedSquares(vector<int> nums) {
    vector<int> ans(nums.size());
    int leftPtr = 0, rightPtr = nums.size() - 1;
    int size = nums.size() - 1;
    while (leftPtr <= rightPtr) {
        if (abs(nums[leftPtr]) > abs(nums[rightPtr])) {
            ans[size] = nums[leftPtr] * nums[leftPtr];
            leftPtr++;
        } else {
            ans[size] = nums[rightPtr] * nums[rightPtr];
            rightPtr--;
        }
        size--;
    }
    return ans;
}