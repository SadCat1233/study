#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int findDifference(vector<int> nums1, vector<int> nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    int fast = 0;
    int slow = 0;
    long long int minDiff = LLONG_MAX;

    while (fast < nums1.size() && slow < nums2.size()) {
        long long int diff = abs(nums1[fast] - nums2[slow]);
        minDiff = min(minDiff, diff);

        if (nums1[fast] < nums2[slow]) {
            fast++;
        } else if (nums2[slow] < nums1[fast]) {
            slow++;
        } else {
            return 0;
        }
    }
    return minDiff;
}
