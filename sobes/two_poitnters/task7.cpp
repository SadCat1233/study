#include <string>

using namespace std;

bool fuzzyMatch(string s, string t) {
    int first = 0;
    int second = 0;
    while (first < s.size() && second < t.size()) {
        if (s[first] == t[second]) {
            second++;
            first++;
        } else {
            second++;
        }
    }
    return first == s.size();
}
