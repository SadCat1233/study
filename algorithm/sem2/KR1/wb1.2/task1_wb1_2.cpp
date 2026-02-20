#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

enum class Status {
    OK,
    NULL_HEAD_WITH_NONEMPTY,     
    HEAD_NOT_IN_LIST,            
    NEXT_NOT_IN_LIST,            
    PROSKOK,                     
    PERESKOK,                    
    WRONG_NEXT                   // next не равен ожидаемому nodes[i+1]/nullptr
};

struct CheckResult {
    Status st{Status::OK};
    string status;
};

int indexOf(Node* node, vector<Node*>& nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == node) return i;
    }
    return -1;
}

CheckResult check(Node* head, vector<Node*>& nodes) {
    int n = nodes.size();
    if (n == 0) {
        if (head == nullptr) return {Status::OK, "OK"};
        return {Status::HEAD_NOT_IN_LIST, "head not nullptr, but list is empty"};
    }
    if (head == nullptr) return {Status::NULL_HEAD_WITH_NONEMPTY, "head is nullptr, but list is not empty"};

    int i = 0;
    Node* cur = head;
    for (int steps = 0; steps < n; steps++) {
        if (cur == nullptr) {
            if (i == n) return {Status::OK, "OK"};
            return {Status::WRONG_NEXT, "Proskok"};
        }
        int j = indexOf(cur, nodes);
        if (j == -1) {
            return {Status::HEAD_NOT_IN_LIST, "current node not in list (nodes[" + to_string(i) + "])"};
        }
        if (j > i) {
            return {Status::PROSKOK, "expected nodes[" + to_string(i + 1) + "], got nodes[" + to_string(j + 1) + "]"};
        }
        if (j < i) {
            return {Status::PERESKOK, "expected nodes[" + to_string(i + 1) + "], got nodes[" + to_string(j + 1) + "]"};
        }

        Node* expectedNext = (i == n - 1) ? nullptr : nodes[i + 1];
        if (cur->next != expectedNext) {
            if (cur->next == nullptr) {
                return {Status::WRONG_NEXT, "incorrect next pointer"};
            }
            int k = indexOf(cur->next, nodes);
            if (k == -1) {
                return {Status::NEXT_NOT_IN_LIST, "next not in list"};
            }
            if (k > i + 1) {
                return {Status::PROSKOK, "expected nodes[" + to_string(i + 1) + "], got nodes[" + to_string(k + 1) + "]"};
            }
            if (k <= i) {
                return {Status::PERESKOK, "123expected nodes[" + to_string(i + 1) + "], got nodes[" + to_string(k + 1) + "]"};
            }
        }
        cur = cur->next;
        i++;

        if (n == i && cur == nullptr) return {Status::OK, "OK"};
    }
    return {Status::PERESKOK, "too many steps"};
}


Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->next = nullptr;
    return node;
}

vector<Node*> constructList(int n) {
    vector<Node*> nodes;

    nodes.push_back(newNode(1));
    nodes.push_back(newNode(2));
    nodes[0]->next = nodes[1];

    for (int i = 3; i < n + 1; i++) {
        Node* nextNode = newNode(i);
        nodes[nodes.size() - 1]->next = nextNode;
        nodes.push_back(nextNode);
    }
    return nodes;
}


void runTest(string message, Node* head, vector<Node*>& testNodes) {
    auto res = check(head, testNodes);
    cout << message << ": " << res.status << endl;
}


void printList(vector<Node*>& nodes) {
    Node* ptr = nodes[0];
    while (ptr) {
        cout << ptr->data << endl;
        ptr = ptr->next;
    }
}


int main() { 
    // test1: correct list
    {
        vector<Node*> testNodes = constructList(6);
        runTest("OK linear", testNodes[0], testNodes);
    }

    // test2: proskok (1 -> 3)
    {
        vector<Node*> testNodes = constructList(6);
        testNodes[0]->next = testNodes[2];
        runTest("PROSKOK 1->3", testNodes[0], testNodes);
    }

    // test3: pereskok (4 -> 2)
    {
        vector<Node*> testNodes = constructList(6);
        testNodes[3]->next = testNodes[1];
        runTest("PERESKOK 4->2", testNodes[0], testNodes);
    }

    // test4: cycle (3 -> 3)
    {
        vector<Node*> testNodes = constructList(6);
        testNodes[2]->next = testNodes[2];
        runTest("PERESKOK self-loop", testNodes[0], testNodes);
    }

    // test5: early nullptr (break)
    {
        vector<Node*> testNodes = constructList(6);
        testNodes[1]->next = nullptr;
        runTest("WRONG early null", testNodes[0], testNodes);
    }

    // test6: head not first node (proskok)
    {
        vector<Node*> testNodes = constructList(6);
        runTest("PROSKOK head=3rd", testNodes[2], testNodes);
    }

    // test7: wrong next ptr (point out of list)
    {
        vector<Node*> testNodes = constructList(6);
        Node wrong;
        testNodes[0]->next = &wrong;
        runTest("NEXT not in pool", testNodes[0], testNodes);
    }
    return 0;
}