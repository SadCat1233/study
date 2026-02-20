#include <iostream>
#include <vector>

using namespace std;


struct Node {
    int value;
    Node* next;
    Node* prev;
};


Node* createNode(int value) {
    return new Node{value, nullptr, nullptr};
}


Node* createList(vector<int> data) {
    if (data.size() == 1) return createNode(data[0]);
    Node* head = createNode(data[0]);
    Node* last = createNode(data[1]);
    head->next = last;
    last->prev = head;

    for (int i = 2; i < data.size(); i++) {
        Node* newNode = createNode(data[i]);
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    }
    return head;
}


Node* intersection(Node* head1, Node* head2) {
    Node* cur1 = head1;
    Node* cur2 = head2;

    Node* ansHead = nullptr;
    Node* ansLast = nullptr;

    while (cur1 != nullptr && cur2 != nullptr) {
        while (cur2 != nullptr && cur2->value < cur1->value) {
            cur2 = cur2->next;
        }
        if (cur2 == nullptr) break;

        if (cur1->value == cur2->value) {
            Node* node = new Node{cur1->value, nullptr, nullptr};
            if (ansHead == nullptr) {
                ansHead = ansLast = node;
            } else {
                ansLast->next = node;
                node->prev = ansLast;
                ansLast = node;
            }

            cur2 = cur2->next;
        }
        cur1 = cur1->next;
    }
    return ansHead;
}


void print(Node* head) {
    if (head == nullptr) {
        cout << "nullptr";
        return;
    }
    Node* cur = head;
    while (cur) {
        // cout << "[" << cur->prev << " " << cur << " " << cur->next << " " << cur->value << "]" << "<->";
        cout << cur->value << "<->";
        cur = cur->next;
    }
    cout << "(back to head)" << endl;
}


int main() {
    int len1, len2;
    cin >> len1 >> len2;
    vector<int> data1(len1);
    vector<int> data2(len2);
    for (int i = 0; i < len1; i++) {
        cin >> data1[i];
    }
    for (int i = 0; i < len2; i++) {
        cin >> data2[i];
    }
    Node* head1 = createList(data1);
    Node* head2 = createList(data2);
    print(head1);
    print(head2);
    Node* ansHeadNode = intersection(head1, head2);
    print(ansHeadNode);
}