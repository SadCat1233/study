#include <vector>

using namespace std;

vector<char> unurlify(vector<char> s) {
    int fast = 0;
    int slow = 0;
    while (fast < s.size()) {
        if (s[fast] == '%' && s[fast + 1] == '2' && s[fast + 2] == '0') {
            s[slow] = ' ';
            fast += 3;
        } else {
            s[slow] = s[fast];
            fast++;
        }
        slow++;
    }
    for (int i = slow; i < s.size(); i++) {
        s[i] = '#';
    }
    return s;
}
