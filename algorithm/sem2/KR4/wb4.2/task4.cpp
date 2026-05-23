#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    int k;
    int limit;
    cin >> n >> k >> limit;

    vector<int> orders(n);

    for (int i = 0; i < n; i++) {
        cin >> orders[i];
    }

    sort(orders.rbegin(), orders.rend());

    vector<int> courierLoad;

    for (int distance : orders) {
        if (distance > limit) {
            cout << -1 << endl;
            return 0;
        }

        int bestCourier = -1;
        int bestLoadAfterAdding = -1;

        for (int i = 0; i < static_cast<int>(courierLoad.size()); i++) {
            int newLoad = courierLoad[i] + distance;

            if (newLoad <= limit && newLoad > bestLoadAfterAdding) {
                bestLoadAfterAdding = newLoad;
                bestCourier = i;
            }
        }

        if (bestCourier == -1) {
            if (static_cast<int>(courierLoad.size()) == k) {
                cout << -1 << endl;
                return 0;
            }

            courierLoad.push_back(distance);
        } else {
            courierLoad[bestCourier] += distance;
        }
    }

    cout << courierLoad.size() << endl;

    return 0;
}
