#include <vector>

using namespace std;

vector<int> removeDuplicates(vector<int> nums) {
    int fast = 1;
    int slow = 0;
    while (fast < nums.size()) {
        if (nums[fast] == nums[slow]) {
            ;
        } else {
            slow++;
            swap(nums[slow], nums[fast]);
        }
        fast++;
    }
    nums.resize(slow + 1);
    return nums;
}