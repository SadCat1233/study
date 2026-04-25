#include <vector>
#include <string>

using namespace std;

vector<char> urlify(vector<char>& s, int k) {
    int fast = k - 1;
    int slow = s.size() - 1;
    while (fast >= 0) {
        if (s[fast] != ' ') {
            s[slow] = s[fast];
            slow--;
        } else {
            s[slow] = '0';
            s[slow - 1] = '2';
            s[slow - 2] = '%';
            slow -= 3;
        }
        fast--;
    }
    return s;
}