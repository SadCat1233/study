#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;

void heapifyDown(int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int smallest = index;
    while (true) {
        if (left < heap.size() - 1 && heap[left] < heap[index]) {
            smallest = left;
        }
        if (right < heap.size() - 1 && heap[right] < heap[index]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void eraseMinKanat() {
    if (heap.empty()) {
        return;
    }
    int topElement = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
}

void insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void printHeap() {
    for (auto val : heap) {
        cout << val << " ";
    }
}

int main() {
    int n;
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        cin >> input[n];
        insert(input[n]);
    }
    printHeap();
    return 0;
}