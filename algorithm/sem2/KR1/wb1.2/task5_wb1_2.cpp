#include <iostream>
#include <vector>

using namespace std;


struct Node {
    int value;
    Node* next;
};


Node* createNode() {
    Node* node = new Node{rand() % 10, nullptr};
    return node;
}


Node* constructList(int length) {
    if (length == 1) {
        return createNode();
    }
    else {
        Node* head = createNode();
        Node* last = createNode();
        head->next = last;

        for (int i = 2; i < length; i++) {
            Node* nextNode = createNode();
            last->next = nextNode;
            last = nextNode;
        }
        return head;
    }
}


int getNumber(Node* head, bool reverse, int length) {
    int multiplier = (reverse) ? 1 : pow(10, length - 1);
    int result = 0;
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        result += cur->value * multiplier;
        multiplier = (reverse) ? multiplier * 10 : multiplier / 10;
    }
    return result;
}


Node* nodeListFromNumber(int number) {
    if (number < 10) return new Node{number, nullptr};
    Node* head = new Node{number % 10, nullptr};
    number /= 10;
    Node* last = new Node{number % 10, nullptr};
    number /= 10;
    head->next = last;
    while (number >= 1) {
        Node* newNode = new Node{number % 10, nullptr};
        number /= 10;
        last->next = newNode;
        last = newNode;
    }
    return head;
}


int reverseDigits(int num)
{
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}


void printList(Node* head) {
    for (Node* cur = head; cur != nullptr; cur = cur->next) {
        cout << cur->value << " ";
    }
    cout << endl;
}


int main() {
    srand(time(NULL));
    int len1, len2;
    bool reverse;
    cin >> len1 >> len2;
    cin >> reverse;

    Node* firstHead = constructList(len1);
    Node* secondHead = constructList(len2);
    printList(firstHead);
    printList(secondHead);

    int ans = getNumber(firstHead, reverse, len1) + getNumber(secondHead, reverse, len2);
    if (!reverse) ans = reverseDigits(ans);
    
    Node* ansHead = nodeListFromNumber(ans);
    printList(ansHead);
}