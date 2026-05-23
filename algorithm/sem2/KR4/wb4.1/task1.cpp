#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;

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
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    for (auto num : nums) {
        insert(num);
    }
    printHeap();
}   