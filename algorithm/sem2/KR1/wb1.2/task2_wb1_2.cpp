#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node* next; 
};

Node* createNode(int nodeValue) {
    Node* node = new Node;
    node->value = nodeValue;
    node->next = nullptr;
    return node;
}


Node* constructList(vector<int>& data) {
    Node* head = createNode(data[0]);
    Node* last = createNode(data[1]);
    head->next = last;

    for (int i = 2; i < data.size(); i++) {
        Node* nextNode = createNode(data[i]);
        last->next = nextNode;
        last = nextNode;
    }
    return head;
}


pair<Node*, Node*> splitNodeList(Node* head, int target) {
    Node* less = nullptr;
    Node* greaterEqual = nullptr;

    Node* lessTail = nullptr;
    Node* greaterTail = nullptr;

    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        current->next = nullptr;

        if (current->value < target) {
            if (less == nullptr) {
                less = lessTail = current;
            }
            else {
                lessTail->next = current;
                lessTail = current;
            }
        }
        else {
            if (greaterEqual == nullptr) {
                greaterEqual = greaterTail = current;
            }
            else {
                greaterTail->next = current;
                greaterTail = current;
            }
        }
        current = nextNode;
    }
    return {less, greaterEqual};
}


void printList(Node* head) {
    Node* ptr = head;
    while(ptr) {
        cout << ptr->value << "->";
        ptr = ptr->next;
    }
    cout << "nullptr";
    cout << endl;
}


int main() {
    int n, target;
    cin >> n;
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
    cin >> target;
    Node* first = constructList(data);
    pair<Node*, Node*> lists = splitNodeList(first, target);
    cout << "Less list: ";
    printList(lists.first);
    cout << "Greater-equal list: ";
    printList(lists.second);
}