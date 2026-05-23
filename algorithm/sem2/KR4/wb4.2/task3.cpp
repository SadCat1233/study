#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> events;
    events.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int start;
        int finish;
        cin >> start >> finish;

        events.push_back({start, 1});
        events.push_back({finish, -1});
    }

    sort(events.begin(), events.end(), [](const auto& left, const auto& right) {
        if (left.first != right.first) {
            return left.first < right.first;
        }

        return left.second < right.second;
    });

    int currentRooms = 0;
    int answer = 0;

    for (const auto& event : events) {
        currentRooms += event.second;
        answer = max(answer, currentRooms);
    }

    cout << answer << endl;

    return 0;
}
