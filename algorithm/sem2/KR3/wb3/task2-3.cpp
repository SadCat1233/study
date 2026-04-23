#include <iostream>

using namespace std;

struct Node {
    int value;
    int height;
    Node* left;
    Node* right;
};

int height(Node* node) {
    if (!node) return 0;
    return node->height;
}

void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

int balanceFactor(Node* node) {
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* rotateRight(Node* root) {
    Node* leftChild = root->left;
    Node* rightLeftChild = leftChild->right;
    leftChild->right = root;
    root->left = rightLeftChild;

    updateHeight(root);
    updateHeight(leftChild);

    return leftChild;
}

Node* rotateLeft(Node* root) {
    Node* rightChild = root->right;
    Node* leftRightChild = rightChild->left;

    rightChild->left = root;
    root->right = leftRightChild;

    updateHeight(root);
    updateHeight(rightChild);

    return rightChild;
}

Node* balance(Node* root) {
    updateHeight(root);
    int rootBalanceFactor = balanceFactor(root);

    if (rootBalanceFactor > 1 && balanceFactor(root->left) >= 0) {
        return rotateRight(root);
    } if (rootBalanceFactor < -1 && balanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    } if (rootBalanceFactor > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    } if (rootBalanceFactor < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* insertNode(Node* root, int value) {
    if (!root) {
        return new Node{value, 1, nullptr, nullptr};
    }
    if (root->value > value) {
        root->left = insertNode(root->left, value);
    } else if (root->value < value) {
        root->right = insertNode(root->right, value);
    } else {
        return root;
    }
    return balance(root);
}

Node* findMin(Node* root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

Node* eraseNode(Node* root, int value) {
    if (!root) return nullptr;

    if (root->value > value) {
        root->left = eraseNode(root->left, value);
    } else if (root->value < value) {
        root->right = eraseNode(root->right, value);
    } else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left || !root->right) {
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        } else {
            Node* temp = findMin(root->right);
            root->value = temp->value;
            root->right = eraseNode(root->right, temp->value);
        }
    }

    return balance(root);
}

void printTree(Node* root, const string& prefix = "", bool isLeft = false) {
    if (!root) {
        cout << prefix << (isLeft ? "├── " : "└── ") << "(null)\n";
        return;
    }
    cout << prefix
              << (isLeft ? "├── " : "└── ")
              << root->value
              << " [h=" << root->height
              << ", bf=" << balanceFactor(root) << "]\n";

    if (root->left || root->right) {
        printTree(root->left,  prefix + (isLeft ? "│   " : "    "), true);
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = insertNode(nullptr, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 10);
    root = insertNode(root, 25);
    root = insertNode(root, 35);
    root = insertNode(root, 50);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    root = insertNode(root, 28);
    printTree(root);
    root = insertNode(root, 2);
    printTree(root);
}