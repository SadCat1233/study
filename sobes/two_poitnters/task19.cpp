#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string longestCommonPrefix(vector<string> strs) {
    string prefix = strs[0];
    for (auto i = 1; i < strs.size(); i++) {
        string currStr = strs[i];
        for (auto j = 0; j < min(prefix.size(), currStr.size()); j++) {
            if (prefix[j] != currStr[j]) {
                prefix = prefix.substr(0, j);
                break;
            }
        }
        if (prefix.size() > currStr.size()) {
            prefix = prefix.substr(0, currStr.size());
        }
    }
    return prefix;
}