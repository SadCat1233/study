#include <iostream>

using namespace std;


struct Node {
    int value;
    Node* next;
};


Node* createNode(int value) {
    return new Node{value, nullptr};
}


Node* constructList(int length) {
    if (length == 1) return createNode(rand() % 10);
    Node* head = createNode(rand() % 10);
    Node* last = createNode(rand() % 10);
    head->next = last;
    for (int i = 2; i < length; i++) {
        Node* newNode = createNode(rand() % 10);
        last->next = newNode;
        last = newNode;
    }
    return head;
}


Node* nodeListSort(Node* head) {
    if (head == nullptr) return nullptr;

    Node* evenHead = nullptr;
    Node* evenTail = nullptr;
    Node* oddHead = nullptr;
    Node* oddTail = nullptr;

    Node* cur = head;

    while (cur) {
        Node* next = cur->next;
        cur->next = nullptr;
        
        if (cur->value % 2 == 0) {
            if (evenHead == nullptr) {
                evenHead = evenTail = cur;
            } else {
                evenTail->next = cur;
                evenTail = cur;
            }
        } else {
            if (oddHead == nullptr) {
                oddHead = oddTail = cur;
            } else {
                oddTail->next = cur;
                oddTail = cur;
            }
        }
        cur = next;
    }
    if (evenHead == nullptr) return oddHead;
    evenTail->next = oddHead;
    return evenHead;
}


void printList(Node* head) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        cout << cur->value << " ";
    }
    cout << endl;
}


int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    
    Node* start = constructList(n);
    printList(start);

    Node* newStart = nodeListSort(start);
    printList(newStart);
    return 0;
}