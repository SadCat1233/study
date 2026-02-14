#include <iostream>
#include <vector>

using namespace std;

int backpack(int weight[], int value[], int W, int n) {
    if (W == 0 || n == 0) {
        return 0;
    }
    if (weight[n] > W) {
        return backpack(weight, value, W, n - 1);
    }
    return max(value[n - 1] + backpack(weight, value, W - weight[n - 1], n - 1), backpack(weight, value, W, n - 1));
}


int main() {
    int n, W;
    cin >> n >> W;
    int value[n], weight[n];
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }
    cout << backpack(weight, value, W, n);
    return 0;
}