#include <iostream>

using namespace std;

struct Node {
    string data;
    Node* next;

    Node(string value): data(value), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool isEmpty() {
        return first == nullptr;
    }

    void add(string value) {
        Node* p = new Node(value);
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (isEmpty()) {
            return;
        }
        Node* p = first;
        while (p) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    list l;
    l.add("123");
    l.add("321");
    l.add("asda");
    l.print();
    return 0;
}