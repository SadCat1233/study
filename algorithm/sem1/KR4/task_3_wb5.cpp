#include <iostream>
#include <vector>
#include <string>

using namespace std;

void prefixFunction(string str, int prefix[]) {
    prefix[0] = 0;
    for (auto i = 1; i < str.length() - 1; i++) {
        int temp = prefix[i - 1];
        while (temp > 0 && str[i] != str[temp]) {
            temp = prefix[temp - 1];
        }
        if (str[i] == str[temp]) {
            temp++;
        }
        prefix[i] = temp;
    }
}


vector<int> knutMorrisPratt(string target, string initial) {
    int targetLength = target.length(), initialLength = initial.length(), count = 0;
    vector<int> answer;
    int prefixArray[targetLength + initialLength + 1];
    for (auto i = 0; i < (targetLength + initialLength + 1); i++) {
        prefixArray[i] = 0;
    }
    prefixFunction(target + "~" + initial, prefixArray);
    for (auto j = 0; j < initialLength; j++) {
        if (prefixArray[targetLength + 1 + j] == targetLength) {
            answer.push_back(j - targetLength + 1);
            count++;
        }
    }
    return answer;
}

int main() {
    string origin, temp;
    cin >> origin >> temp;
    for (auto pos : knutMorrisPratt(temp, origin)) {
        cout << pos << " ";
    }
    cout << endl;
    return 0;
}