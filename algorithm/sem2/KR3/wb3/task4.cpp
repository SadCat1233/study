#include <iostream>
#include <climits>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int    value;
    Color  color;
    Node*  left;
    Node*  right;
    Node*  parent;
};

Node* newNode(int value) {
    Node* n   = new Node;
    n->value    = value;
    n->color  = RED;
    n->left   = nullptr;
    n->right  = nullptr;
    n->parent = nullptr;
    return n;
}

bool isRootBlack(Node* root) {
    if (root && root->color == BLACK) {
        return true;
    }
    return false;
}

bool doubleRed(Node* root) {
    if (!root) return true;
    if (root->color == RED) {
        if (root->left && root->left->color == RED) {
            return false;
        }
        if (root->right && root->right->color == RED) {
            return false;
        }
    }
    return doubleRed(root->left) && doubleRed(root->right);
}

int blackHeight(Node* node) {
    if (node == nullptr)
        return 1;

    int leftHeight  = blackHeight(node->left);
    int rightHeight = blackHeight(node->right);

    if (leftHeight == -1 || rightHeight == -1)
        return -1;

    if (leftHeight != rightHeight)
        return -1;

    return leftHeight + (node->color == BLACK ? 1 : 0);
}

int main() {
    cout << sizeof(Node);
    return 0;
}