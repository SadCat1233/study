#include <iostream>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    Node* parent;
    int value;
    
    Node(int value) : value(value), left(nullptr), right(nullptr), parent(nullptr) {};
};


void rotateRight(Node*& root, Node* node) {
    Node* leftChild = node->left;
    if (!leftChild) return;

    node->left = leftChild->right;
    if (leftChild->right) leftChild->right->parent = node;

    leftChild->parent = node->parent;
    if (!node->parent) {
        root = leftChild;
    } else if (node->parent->left == node) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }
}


Node* rotateLeft(Node*& root, Node* node) {
    Node* rightChild = node->right;
    if (!rightChild) return;

    node->right = rightChild->left;
    if (rightChild->left) rightChild->left->parent = node;

    rightChild->parent = node->parent;
    if (!node->parent) {
        root = rightChild;
    } else if (node->parent->left == node) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
}


void splay(Node*& root, Node* node) {
    if (!node) return;

    while (node->parent) {
        Node* dad = node->parent;
        Node* grandpa = dad->parent;

        if (!grandpa) {
            if (dad->left == node) {
                rotateRight(root, dad);
            } else {
                rotateLeft(root, dad);
            }
        } else {
            if (grandpa->left == dad && dad->left == node) {
                rotateRight(root, grandpa);
                rotateRight(root, dad);
            } else if (grandpa->right == dad && dad->right == node) {
                rotateLeft(root, grandpa);
                rotateLeft(root, dad);
            } else if(grandpa->right == dad && dad->left == node) {
                rotateLeft(root, dad);
                rotateRight(root, grandpa);
            } else {
                rotateRight(root, dad);
                rotateLeft(root, grandpa);
            }
        }
    }
    root = node;
}


Node* findNode(Node*& root, int targetvalue) {
    if (!root) return nullptr;

    Node* current = root;
    Node* last = nullptr;
    while (current) {
        last = current;
        if (current->value > targetvalue) {
            current = current->left;
        } else if (current->value < targetvalue) {
            current = current->right;
        } else {
            splay(root, current);
            return current;
        }
    }
    if (last) splay(root, last);
    return nullptr;
}


void insertNode(Node*& root, int value) {
    if (!root) {
        root = new Node(value);
    }
    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (current->value > value) {
            current = current->left;
        } else if (current->value < value) {
            current = current->right;
        } else {
            splay(root, current);
            return;
        }
    }

    Node* newNode = new Node(value);
    newNode->parent = parent;
    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    splay(root, newNode);
}


Node* findMax(Node*& root) {
    if (!root) return nullptr;
    while (root->right) root = root->right;
    splay(root, root);
    return root;
}


void eraseNode(Node*& root, int value) {
    if (!root) return;

    if (!findNode(root, value)) return;

    Node* leftChild = root->left;
    Node* rightChild = root->right;

        delete root;
    
    if (!leftChild) {
        root = rightChild;
        if (root) root->parent = nullptr;
        return;
    }
    
    if (!rightChild) {
        root = leftChild;
        if (root) root->parent = nullptr;
        return;
    }
    
    leftChild->parent = nullptr;
    rightChild->parent = nullptr;
    
    root = leftChild;
    Node* maxLeft = findMax(root);
    
    maxLeft->right = rightChild;
    rightChild->parent = maxLeft;
}


int main() {
    return 0;
}