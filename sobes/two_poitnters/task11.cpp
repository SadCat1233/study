#include <vector>

using namespace std;

vector<int> moveZeros(vector<int> nums) {
    int slow = 0;
    int fast = 0;

    while (fast < nums.size()) {
        if (nums[fast] != 0) {
            swap(nums[fast], nums[slow]);
            slow++;
        }
        fast++;
    }
    return nums;
}