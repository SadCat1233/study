#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    int leftPtr = 0, rightPtr = nums.size() - 1;
    while (leftPtr < rightPtr) {
        if (nums[leftPtr] + nums[rightPtr] > target) {
            rightPtr--;
        } else if (nums[leftPtr] + nums[rightPtr] < target) {
            leftPtr++;
        } else {
            return {leftPtr + 1, rightPtr + 1};
        }
    }
    return {-1, -1};
}