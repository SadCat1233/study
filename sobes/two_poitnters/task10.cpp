#include <string>

using namespace std;

int findNextNonSkip(const string& s, int pointer) {
    int skipCount = 0;
    while (pointer >= 0 && (s[pointer] == '#' || skipCount > 0)) {
        if (s[pointer] == '#') {
            skipCount++;
            pointer--;
            continue;
        }
        pointer--;
        skipCount--;
    }
    return pointer;
}

bool compare(const string& s, const string& t) {
    int first = s.size();
    int second = t.size();
    
    while (first > 0 && second > 0) {
        first = findNextNonSkip(s, first - 1);
        second = findNextNonSkip(t, second - 1);
        if (first >= 0 && second >= 0 && s[first] != t[second]) {
            return false;
        }
    }
    return findNextNonSkip(s, first - 1) == findNextNonSkip(t, second - 1);
}