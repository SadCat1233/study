#include <iostream>
#include <stack>

using namespace std;


struct Node {
    int value;
    Node* next;
    Node* prev;
};


void addNodeEnd(Node*& head, Node*& last, int value) {
    Node* node = new Node{value, nullptr, nullptr};

    if (head == nullptr) {
        head = node;
        last = head;
        return;
    }
    if (head->next == nullptr) {
        node->prev = head;
        last = node;
        head->next = last;
    } else {
        node->prev = last;
        last->next = node;
        last = node;
    }
}

void insertNode(Node*& head, Node*& last, int target, int value) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->value == target) {
            Node* newNode = new Node{value, cur, cur->prev};

            if (cur->prev) {
                Node* temp = cur->prev;
                temp->next = newNode;
            }
            else head = newNode;

            cur->prev = newNode;

            cur = cur->next;
        }
        cur = cur->next;
    }
}


void eraseNode(Node*& head, Node*& last, int n) {
    if (head == nullptr) return;
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;

        if (cur->value == n) {
            if (next == cur) {
                delete cur;
                head = nullptr;
                return;
            }
            Node* right = cur->next;
            if (head == cur) {
                head = right;
            } else {
                Node* left = cur->prev;
                left->next = right;
                right->prev = left;
            }
            delete cur;
        }
        cur = next;
    }
}

bool isPalindrome(Node* head, Node* tail) {
    if (!head) return true;          
    if (head == tail) return true;   

    Node* l = head;
    Node* r = tail;

    while (l != r && l->prev != r) { 
        if (l->value != r->value) return false;
        l = l->next;
        r = r->prev;
    }
    return true;
}


int listLength(Node* head, Node* last) {
    if (head == nullptr) return 0;
    Node* cur = head;
    int answer = 0;
    while (cur) {
        answer += 1;
        cur = cur->next;
    }
    return answer;
}


void printList(Node* head, Node* last, bool reverse) {
    if (head == nullptr) {
        cout << "nullptr" << endl; return;
    }
    Node* cur = (reverse) ? last : head;
    while (cur) {
        cout << cur->value << "<->";
        cur = (reverse) ? cur->prev : cur->next;
    }
    cout << "nullptr" << endl;
}


int main() {
    Node* head = nullptr;
    Node* last = nullptr;
    addNodeEnd(head, last, 3);
    addNodeEnd(head, last, 5);
    addNodeEnd(head, last, 7);
    addNodeEnd(head, last, 9);
    insertNode(head, last, 5, 4);
    addNodeEnd(head, last, 9);
    addNodeEnd(head, last, 7);
    addNodeEnd(head, last, 5);
    addNodeEnd(head, last, 3);
    eraseNode(head, last, 5);
    cout << isPalindrome(head, last) << endl;
    printList(head, last, false);
    cout << listLength(head, last) << endl;
    return 0;
}