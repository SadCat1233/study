#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> rates(n);
    for (int i = 0; i < n; i++) {
        cin >> rates[i];
    }
    int prev = rates[0];
    int counter = 1;
    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (prev == rates[i]) {
            counter += 1;
            if (counter > ans) {
                ans = counter;
            }
        }
        else {
            counter = 1;
        }
        prev = rates[i];
    }
    cout << ans << endl;
    return 0;
}