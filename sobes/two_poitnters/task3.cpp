#include <vector>
#include <cmath>

using namespace std;

int maxArea(vector<int> nums) {
    int leftPtr = 0, rightPtr = nums.size() - 1;
    int ans = 0;
    while (leftPtr < rightPtr) {
        int currArea = min(nums[leftPtr], nums[rightPtr]) * (rightPtr - leftPtr);
        ans = max(ans, currArea);
        if (nums[leftPtr] < nums[rightPtr]) {
            leftPtr++;
        } else {
            rightPtr--;
        }
    }
    return ans;
}
