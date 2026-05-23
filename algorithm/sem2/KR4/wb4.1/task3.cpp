#include <iostream>
#include <vector>

using namespace std;

class BinaryHeap {
    private:
        void heapifyDown(int index) {
            size_t n = heap.size();
            while (true) {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int smallest = index;
                if (left < n && heap[left] > heap[index]) {
                    smallest = left;
                } if (right < n && heap[right] > heap[index]) {
                    smallest = right;
                } if (smallest == index) {
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
    public:
        vector<int> heap;

        BinaryHeap() {};
        BinaryHeap(vector<int> nums) : heap(nums) {
            if (heap.empty()) return;
            for (int i = heap.size() / 2 - 1; i >= 0; i++) {
                heapifyDown(i);
            }
        }

        int get_max() {
            if (!heap.empty()) {
                return heap[0];
            }
        }

        void insert(int value) {
            heap.push_back(value);
            heapifyUp(heap.size() - 1);
        }

        int extract_max() {
            if (heap.empty()) return -1;
            int maxValue = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                heapifyDown(0);
            }
            return maxValue;
        }
};