#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int popElement(vector<int>& priorityQueue) {
    auto topElement = priorityQueue[priorityQueue.size() - 1];
    priorityQueue.erase(priorityQueue.begin() + priorityQueue.size() - 1);
    return topElement;
}


void pushElement(vector<int>& priorityQueue, int value, string direction) {
    if (direction == "increase") {
        auto it = lower_bound(priorityQueue.begin(), priorityQueue.end(), value);
        priorityQueue.insert(it, value);
    }
    else {
        auto it = lower_bound(priorityQueue.begin(), priorityQueue.end(), value, greater<int>());
        priorityQueue.insert(it, value);
    }
}

int main() {
    vector<int> priorityQueue;
    string direction;
    cout << "Enter increase or decrease ";
    cin >> direction;
    string command;
    while (command != "end") {
        cin >> command;
        if (command == "push") {
            int value;
            cout << "enter value to push the queue ";
            cin >> value;
            pushElement(priorityQueue, value, direction);
        }
        else if (command == "pop") {
            popElement(priorityQueue);
        }
    }
    for (auto i : priorityQueue) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}