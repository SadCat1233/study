#include <iostream>
#include <vector>

using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;
};


void addNode(Node*& root, int data) {
    if (root == nullptr) {
        root = new Node{data, nullptr, nullptr};
        return;
    }
    if (data < root->data) {
        addNode(root->left, data);
    }
    else {
        addNode(root->right, data);
    }
    return;
}


void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}


int treeDepth(Node* root) {
    if (!root) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    }
    return 1 + max(treeDepth(root->left), treeDepth(root->right));
}


Node* findNode(Node* root, int target) {
    if (!root) return nullptr;
    if (root->right == nullptr && root->left == nullptr && root->data != target) return nullptr;
    if (target < root->data) {
        return findNode(root->left, target);
    }
    else if (target > root->data) {
        return findNode(root->right, target);
    }
    return root;
}


Node* findMax(Node* root) {
    while (root && root->right) root = root->right;
    return root;
}


Node* eraseNode(Node* root, int value) {
    if (!root) return nullptr;
    if (value < root->data) {
        root->left = eraseNode(root->left, value);
    } else if (value > root->data) {
        root->right = eraseNode(root->right, value);
    } else {
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        if (!root->left) {
            Node* r = root->right;
            delete root;
            return r;
        }
        if (!root->right) {
            Node* l = root->left;
            delete root;
            return l;
        }

        Node* succ = findMax(root->left);
        root->data = succ->data;
        root->left = eraseNode(root->left, succ->data);
    }
    return root;
}


int main() {
    int n;
    cin >> n;
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        addNode(root, value);
    }
    cout << treeDepth(root) << endl;
    Node* node = findNode(root, 4);
    if (node) {
        cout << node->data << endl;
        eraseNode(root, node->data);
    }
    else {
        cout << "Element not found" << endl;
    }
    return 0;
}