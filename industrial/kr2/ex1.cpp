#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

class Node {
public:
    int value;
    unique_ptr<Node> next;

    Node() : value(0), next(nullptr) {}

    Node(int val) : value(val), next(nullptr) {}

    Node(double val) : Node(static_cast<int>(round(val))) {}

    Node(const Node& other) : value(other.value), next(nullptr) {
        if (other.next) {
            next = make_unique<Node>(*other.next);
        }
    }

    Node(Node&& other) noexcept : value(other.value), next(move(other.next)) {}

    ~Node() {
        cout << "~Node(" << to_string(value) << ")" << endl;
    }
};