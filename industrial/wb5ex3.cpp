#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int data[n];
    int ans = 0;
    for (auto i = 0; i < n; i++) {
        cin >> data[i];
    }
    for (int iter = 0; iter < n; iter++) {
        for (auto i = 0; i < n; i++) {
            if ((data[i] == data[i + 1]) && (data[i] != -1)) {
                int j = i;
                while (data[j] == data[j + 1]) {
                    j++;
                }
                j += 1;
                int delta = j - i;
                ans += delta;
                for (int k = j; k < n; k++) {
                    data[k - delta] = data[k];
                    data[k] = -1;
                }
            }
        }
    }
    cout << ans;
}