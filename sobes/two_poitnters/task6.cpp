#include <vector>

using namespace std;

vector<int> intersect(vector<int> nums1, vector<int> nums2) {
    int left = 0;
    int right = 0;
    vector<int> nums3;
    while (left < nums1.size() && right < nums2.size()) {
        if (nums1[left] < nums2[right]) {
            left++;
        } else if (nums1[left] > nums2[right]) {
            right++;
        } else {
            nums3.push_back(nums1[left]);
            left++;
            right++;
        }
    }
    return nums3;
}
