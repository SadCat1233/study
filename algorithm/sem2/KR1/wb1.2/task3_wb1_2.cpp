#include <iostream>

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
};


void addNode(Node*& head, int n) {
    Node* node = new Node{nullptr, nullptr, n};

    if (head == nullptr) {
        node->next = node;
        node->prev = node;
        head = node;
    } else {
        Node* last = head->prev;

        node->next = head;
        node->prev = last;

        last->next = node;
        head->prev = node;
    }
}


void eraseNode(Node*& head, int n) {
    if (head == nullptr) return;

    Node* cur = head;
    do {
        if (cur->value == n) {
            if (cur->next == cur) {
                delete cur;
                head = nullptr;
                return;
            }
            Node* left = cur->prev;
            Node* right = cur->next;

            left->next = right;
            right->prev = left;
            
            if (head == cur) head = right;
            delete cur;
            return;
        }
        cur = cur->next;
    } while (cur != head);
}


void printList(Node* head) {
    if (head == nullptr) {
        cout << "nullptr" << endl; return;
    }
    Node* cur = head;
    do {
        cout << cur->value << "<->";
        cur = cur->next;
    } while (cur != head);
    cout << "(back to head)" << endl;
}



void clearList(Node* head) {
    if (head == nullptr) return;

    Node* cur = head->next;
    while (cur != head) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete head;
    head = nullptr;
}


int main() {
    Node* head = nullptr;
    addNode(head, 3);
    addNode(head, 5);
    addNode(head, 8);
    printList(head);
    eraseNode(head, 3);
    printList(head);
}