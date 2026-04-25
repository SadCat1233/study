#include <string>
#include <cmath>

using namespace std;

bool isSimilar(string s, string t) {
    if (abs(static_cast<int>(s.size()) - static_cast<int>(t.size())) > 1) return false;
    int first = 0;
    int second = 0;
    int diff = 0;
    while (first < s.size() && second < t.size()) {
        if (s[first] == t[second]) {
            first++;
            second++;
            continue;
        }
        diff += 1;
        if (diff > 1) return false;
        if (s.size() > t.size()) {
            first++;
        } else if (s.size() < t.size()) {
            second++;
        } else {
            first++;
            second++;
        }
    }
    return true;
}
