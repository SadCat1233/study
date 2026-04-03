#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node{
    int l;
    int r;

    Node* left;
    Node* right;

    int max_value, min_value, sum, odd, even;

    Node(int l, int r, int val) : 
        l(l), r(r), left(nullptr), right(nullptr),
        max_value(val), min_value(val),
        sum(val), odd(val % 2), even(!(val % 2)){
    }
    Node(int l, int r, Node* leftChild, Node* rightChild) : 
        l(l), r(r), left(leftChild), right(rightChild),
        max_value(max(leftChild->max_value, rightChild->max_value)),
        min_value(min(leftChild->min_value, rightChild->min_value)),   
        sum(leftChild->sum + rightChild->sum),
        odd(leftChild->odd + rightChild->odd),
        even(leftChild->even + rightChild->even){}
};

Node* buildTree(const vector<int>& data, int l, int r) {
    if (l == r) {
        return new Node(l, r, data[l]);
    }
    int mid = (l + r) / 2;
    Node* leftChild = buildTree(data, l, mid);
    Node* rightChild = buildTree(data, mid + 1, r);
    return new Node(l, r, leftChild, rightChild);
}

int findMax(Node* node, int tl, int tr) {
    if (node == nullptr) return -1e9;
    if (tl > node->r || tr < node->l) return -1e9;
    if (tl <= node->l && tr >= node->r) return node->max_value;
    return max(findMax(node->left, tl, tr), findMax(node->right, tl, tr));
}

int findMin(Node* node, int tl, int tr) {
    if (node == nullptr) return 1e9;
    if (node->l > tr || tl > node->r) return 1e9;
    if (node->l >= tl && tr >= node->r) return node->min_value;
    return min(findMin(node->left, tl, tr), findMin(node->right, tl, tr));
}

int findSum(Node* node, int tl, int tr) {
    if (node == nullptr) return 0;
    if (tl > node->r || tr < node->l) return 0;
    if (tl <= node->l && node->r <= tr) return node->sum;
    return findSum(node->left, tl, tr) + findSum(node->right, tl, tr);
}

int countOdd(Node* node, int tl, int tr) {
    if (node == nullptr) return 0;
    if (node->l > tr || tl > node->r) return 0;
    if (tl <= node->l && node->r <= tr) return node->odd;
    return countOdd(node->left, tl, tr) + countOdd(node->right, tl, tr);
}

int countEven(Node* node, int tl, int tr) {
    if (node == nullptr) return 0;
    if (node->l > tr || tl > node->r) return 0;
    if (tl <= node->l && node->r <= tr) return node->even;
    return countEven(node->left, tl, tr) + countEven(node->right, tl, tr);
}

void printTree(Node* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "[" << node->l << "," << node->r << "]";
    cout << " max=" << node->max_value;
    cout << " min=" << node->min_value;
    cout << " sum=" << node->sum;
    cout << " odd=" << node->odd;
    cout << " even=" << node->even << endl;
    printTree(node->left, depth + 1);
    printTree(node->right, depth + 1);
}

void update(Node* node, int index, int newValue) {
    if (node->l == node->r) {
        node->max_value = newValue;
        return;
    }
    int mid = (node->l + node->r) / 2;
    if (index <= mid) {
        update(node->left, index, newValue);
    } else {
        update(node->right, index, newValue);
    }
    node->max_value = max(node->left->max_value, node->right->max_value);
}

void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    int n;
    cin >> n;
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
    Node* root = buildTree(data, 0, n - 1);
    printTree(root);
    cout << "----------------------------------------" << endl;
    cout << "max=" << findMax(root, 4, 4) << endl;
    cout << "min=" << findMin(root, 3, 6) << endl;
    cout << "sum=" << findSum(root, 3, 6) << endl;
    cout << "odd=" << countOdd(root, 3, 6) << endl;
    cout << "even=" << countEven(root, 3, 6) << endl;
    return 0;
}