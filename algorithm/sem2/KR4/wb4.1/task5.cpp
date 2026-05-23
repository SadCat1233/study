#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

bool isHeap(Node* root) {
    if (root == nullptr) {
        return true;
    }

    queue<Node*> q;
    q.push(root);

    bool mustBeLeaf = false;

    bool isMaxHeap = true;
    bool isMinHeap = true;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left) {
            if (mustBeLeaf) {
                return false;
            }

            if (current->value < current->left->value) {
                isMaxHeap = false;
            }

            if (current->value > current->left->value) {
                isMinHeap = false;
            }

            q.push(current->left);
        } else {
            mustBeLeaf = true;
        }

        if (current->right) {
            if (mustBeLeaf) {
                return false;
            }

            if (current->value < current->right->value) {
                isMaxHeap = false;
            }

            if (current->value > current->right->value) {
                isMinHeap = false;
            }

            q.push(current->right);
        } else {
            mustBeLeaf = true;
        }
    }

    return isMaxHeap || isMinHeap;
}