#include <vector>

using namespace std;

vector<int> findDifference(vector<int> nums1, vector<int> nums2) {
    int first = 0;
    int second = 0;
    vector<int> result;

    while (first < nums1.size() & second < nums2.size()) {
        if (nums1[first] == nums2[second]) {
            first++;
        } else if (nums1[first] < nums2[second]) {
            result.push_back(nums1[first]);
            first++;
        } else {
            second++;
        }
    }
    while (first < nums1.size()) {
        result.push_back(nums1[first]);
        first++;
    }
    return result;
}
