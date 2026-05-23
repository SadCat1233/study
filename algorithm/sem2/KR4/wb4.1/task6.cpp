#include <iostream>
using namespace std;

class PriorityQueue {
private:
    struct Node {
        int value;
        int priority;
        Node* next;

        Node(int value, int priority) {
            this->value = value;
            this->priority = priority;
            this->next = nullptr;
        }
    };

    Node* head;

public:
    PriorityQueue() {
        head = nullptr;
    }

    ~PriorityQueue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void push(int value, int priority) {
        Node* newNode = new Node(value, priority);

        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;

        while (current->next != nullptr &&
               current->next->priority >= priority) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    int top() const {
        if (isEmpty()) {
            throw runtime_error("Очередь пуста");
        }

        return head->value;
    }

    void pop() {
        if (isEmpty()) {
            throw runtime_error("Очередь пуста");
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void print() const {
        Node* current = head;

        while (current != nullptr) {
            cout << "value: " << current->value
                 << ", priority: " << current->priority << endl;

            current = current->next;
        }
    }
};