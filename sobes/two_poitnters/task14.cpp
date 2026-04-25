#include <vector>
#include <unordered_set>

using namespace std;

vector<int> removeDuplicates(vector<int> nums) {
    unordered_set<int> visited;

    int fast = 0;
    int slow = 0;
    while (fast < nums.size()) {
        if (visited.find(nums[fast]) == visited.end()) {
            visited.insert(nums[fast]);
            swap(nums[slow], nums[fast]);
            slow++;
        }
        fast++;
    }
    nums.resize(slow);
    return nums;
}