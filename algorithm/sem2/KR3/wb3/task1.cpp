#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int balance;
};

void addNode(Node*& root, int value) {
    if (!root) {
        root = new Node{value, nullptr, nullptr, 0};
        return;
    }
    if (root->value > value) {
        addNode(root->left, value);
    } else {
        addNode(root->right, value);
    }
    return;
}

int height(Node* root) {
    if (root == nullptr)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

void calculateBalance(Node* root) {
    if (!root) return;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    root->balance = abs(leftHeight - rightHeight);
    calculateBalance(root->left);
    calculateBalance(root->right);
}

void printTree(Node* root, const std::string& prefix = "", bool isLeft = false) {
    if (!root) {
        std::cout << prefix << (isLeft ? "├── " : "└── ") << "(null)\n";
        return;
    }
    std::cout << prefix
              << (isLeft ? "├── " : "└── ")
              << root->value << "(" << root->balance << ")"
              << "]\n";

    if (root->left || root->right) {
        printTree(root->left,  prefix + (isLeft ? "│   " : "    "), true);
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

void deleteTree(Node*& root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = NULL;
    addNode(root, 40);
    addNode(root, 20);
    addNode(root, 30);
    addNode(root, 50);
    addNode(root, 10);
    addNode(root, 5);
    calculateBalance(root);
    printTree(root, "   ", false);
    return 0;
}