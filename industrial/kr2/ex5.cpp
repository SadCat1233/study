#include <iostream>
#include <algorithm>

using namespace std;

class Buffer {
    public:
        int* data;
        size_t size;
        Buffer() : data(nullptr), size(0) {}

        Buffer(size_t n) : data(new int[n]{}), size(n) {}

        Buffer(initializer_list<int> list) : Buffer(list.size()) {
            copy(list.begin(), list.end(), data);
        }

        Buffer(const Buffer& other) : Buffer(other.size) {
            copy(other.data, other.data + other.size, data);
        }

        Buffer(Buffer&& other) : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
        }

        ~Buffer() {
            delete[] data;
        }

        void print() const {
            for (size_t i = 0; i < size; i++) {
                cout << data[i];
                if (i < size - 1) cout << " ";
            }
            cout << endl;
        }

        void resize(size_t newSize) {
            int* newData = new int[newSize]{};
            copy(data, data + min(size, newSize), newData);
            delete[] data;
            data = newData;
            size = newSize;
        }
};