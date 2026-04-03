//Преподаватель хранит баллы студентов в двоичном дереве поиска (BST). Все баллы различны. Появился новый результат x. Нужно найти уже существующий балл, который ближе всего к x. Если ближайших несколько, то выберите наименьший балл.

#include <iostream>

using namespace std;


struct Node {
    int value;
    Node* left;
    Node* right;
};


void addNode(Node*& root, int value) {
    if (root == nullptr) {
        root = new Node{value, nullptr, nullptr};
        return;
    }
    if (value < root->value) {
        addNode(root->left, value);
    }
    else {
        addNode(root->right, value);
    }
    return;
}


int closestValue(Node* root, int x) {
    int closest = root->value;
    Node* current = root;

    while (current != nullptr) {
        if (abs(current->value - x) < abs(closest - x)) {
            closest = current->value;
        }
        else if (abs(current->value - x) == abs(closest - x)) {
            closest = min(closest, current->value);
        }

        if (x < current->value) {
            current = current->left;
        } else if (x > current->value) {
            current = current->right;
        } else {
            return current->value;
        }
    }

    return closest;
}


int main() {
    int n;
    cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int score;
        cin >> score;
        addNode(root, score);
    }
    int x;
    cin >> x;
    int closest = closestValue(root, x);
    cout << closest << endl;
    return 0;
}