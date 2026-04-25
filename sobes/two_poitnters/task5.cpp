#include <vector>

using namespace std;

vector<char> reverse(vector<char> chars) {
    int left = 0;
    int right = chars.size() - 1;
    while (left < right) {
        swap(chars[left], chars[right]);
        left++;
        right--;
    }
    return chars;
}