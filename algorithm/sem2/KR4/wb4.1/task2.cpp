#include <iostream>

#include <vector>

#include <string>

using namespace std;

vector<pair<int, string>> heap;

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].first <= heap[index].first) {
            break;
        }
        swap(heap[parent], heap[index]);
        index = parent;
    }
}

void heapifyDown(int index) {
    size_t n = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < n && heap[left].first < heap[index].first) {
            smallest = left;
        } if (right < n && heap[right].first < heap[index].first) {
            smallest = right;
        } if (smallest == index) {
            break;
        }
        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void addHomework(int time, string student) {
    heap.push_back({time, student});
    heapifyUp(heap.size() - 1);
}

pair<int, string> extractHomework() {
    pair<int, string> result = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return result;
}

int main() {
    addHomework(10, "Ivan");
    addHomework(5, "Anna");
    addHomework(8, "Petr");
    addHomework(3, "Maria");
    while (!heap.empty()) {
        pair<int, string> homework = extractHomework();
        cout << homework.second << " сдал в " << homework.first << endl;
    }
    return 0;
}