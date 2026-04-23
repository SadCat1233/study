#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(int value) : value(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {};
};

void balanceTree(Node*& root, Node*& newNode);


void redDadAndUncle(Node*& root, Node* newNode, Node* dad, Node* uncle, Node* grandpa) {
    if (uncle) uncle->color = BLACK;
    dad->color = BLACK;
    if (grandpa->parent) {
        grandpa->color = RED;
        balanceTree(root, grandpa);
    }
}


void blackUncleOneSide(Node*& root, Node* newNode, Node* dad, Node* uncle, Node* grandpa) {
    Node* greatGrandpa = grandpa->parent;

    if (grandpa->left == dad) {
        grandpa->left = dad->right;
        if (dad->right) dad->right->parent = grandpa;
        dad->right = grandpa;
    } else {
        grandpa->right = dad->left;
        if (dad->left) dad->left->parent = grandpa;
        dad->left = grandpa;
    }

    grandpa->parent = dad;
    dad->parent = greatGrandpa;

    if (greatGrandpa) {
        if (greatGrandpa->left == grandpa) greatGrandpa->left = dad;
        else greatGrandpa->right = dad;
    } else {
        root = dad;
    }

    dad->color = BLACK;
    grandpa->color = RED;
}


void blackUncleDifferentSide(Node*& root, Node* newNode, Node* dad, Node* uncle, Node* grandpa) {
    if (grandpa->left == dad) {
        grandpa->left = newNode;
        dad->parent = newNode;
        dad->right = newNode->left;
        if (newNode->left) newNode->left->parent = dad;
        newNode->left = dad;
        newNode->parent = grandpa;
    }
    if (grandpa->right == dad) {
        grandpa->right = newNode;
        dad->parent = newNode;
        dad->left = newNode->right;
        if (newNode->right) newNode->right->parent = dad;
        newNode->right = dad;
        newNode->parent = grandpa;
    }
    blackUncleOneSide(root, dad, newNode, uncle, grandpa);
}


void balanceTree(Node*& root, Node*& newNode) {
    if (!newNode->parent->parent) {
        return;
    }
    Node* dad = newNode->parent;
    Node* grandpa = dad->parent;
    Node* uncle = nullptr;
    if (grandpa->left && grandpa->left == dad) {
        uncle = grandpa->right;
    } else if(grandpa->right && grandpa->right == dad) {
        uncle = grandpa->left;
    }
    if (dad->color == RED && uncle && uncle->color == RED) {
        redDadAndUncle(root, newNode, dad, uncle, grandpa);
    }
    if (dad->color == RED && (uncle == nullptr || uncle->color == BLACK)) {
        if ((newNode == dad->right && dad == grandpa->left) || (grandpa->right == dad && dad->left == newNode)) {
            blackUncleDifferentSide(root, newNode, dad, uncle, grandpa);
        }
        else {
            blackUncleOneSide(root, newNode, dad, uncle, grandpa);
        }
    }
}


void insertNode(Node*& root, int value) {
    if (!root) {
        root = new Node(value);
        root->color = BLACK;
        return;
    }
    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (value < current->value) current = current->left;
        else if (value > current->value) current = current->right;
        else return;
    }
    Node* curNode = new Node(value);
    curNode->parent = parent;
    if (!parent) {
        root = curNode;
    }
    else if (value < parent->value) {
        parent->left  = curNode;
    }
    else {
        parent->right = curNode;
    }
    balanceTree(root, curNode);
}


Node* treeMinimum(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}


void replaceChild(Node*& root, Node* parent, Node* oldChild, Node* newChild) {
    if (!parent) {
        root = newChild;
    } else if (parent->left == oldChild) {
        parent->left = newChild;
    } else {
        parent->right = newChild;
    }
    if (newChild) newChild->parent = parent;
}

// Восстановление свойств КЧД после удаления чёрного узла.
// x — узел, занявший место удалённого (может быть nullptr).
// xParent — его родитель (нужен, потому что x может быть nullptr).
void deleteFixup(Node*& root, Node* x, Node* xParent) {
    while (x != root && (!x || x->color == BLACK)) {
        if (xParent->left == x) {
            Node* w = xParent->right; // брат x

            // Случай 1: брат красный
            // Перекрашиваем, делаем левый поворот — брат становится чёрным,
            // сводим задачу к случаям 2–4.
            if (w && w->color == RED) {
                w->color       = BLACK;
                xParent->color = RED;
                // левый поворот вокруг xParent
                Node* grandpa = xParent->parent;
                replaceChild(root, grandpa, xParent, w);
                xParent->right = w->left;
                if (w->left) w->left->parent = xParent;
                w->left = xParent;
                xParent->parent = w;
                // обновляем брата — теперь это левый ребёнок нового родителя
                w = xParent->right;
            }

            bool wLeftBlack  = (!w || !w->left  || w->left->color  == BLACK);
            bool wRightBlack = (!w || !w->right || w->right->color == BLACK);

            // Случай 2: брат чёрный, оба племянника чёрные
            // Перекрашиваем брата в красный, поднимаемся вверх.
            if (wLeftBlack && wRightBlack) {
                if (w) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Случай 3: брат чёрный, правый племянник чёрный, левый красный
                // Правый поворот вокруг брата — переходим к случаю 4.
                if (wRightBlack) {
                    if (w->left) w->left->color = BLACK;
                    if (w) w->color = RED;
                    // правый поворот вокруг w
                    Node* wLeft = w->left;
                    xParent->right = wLeft;
                    if (wLeft) wLeft->parent = xParent;
                    w->left = wLeft ? wLeft->right : nullptr;
                    if (wLeft && wLeft->right) wLeft->right->parent = w;
                    if (wLeft) wLeft->right = w;
                    w->parent = wLeft;
                    w = xParent->right;
                }
                // Случай 4: брат чёрный, правый племянник красный
                // Левый поворот вокруг родителя — дерево восстановлено, выходим.
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->right) w->right->color = BLACK;
                // левый поворот вокруг xParent
                Node* grandpa = xParent->parent;
                replaceChild(root, grandpa, xParent, w);
                if (w) {
                    xParent->right = w->left;
                    if (w->left) w->left->parent = xParent;
                    w->left = xParent;
                    xParent->parent = w;
                }
                x = root; // выход из цикла
            }
        } else {
            // Симметричные случаи: x — правый ребёнок
            Node* w = xParent->left;

            // Случай 1 (симметрия)
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                Node* grandpa = xParent->parent;
                replaceChild(root, grandpa, xParent, w);
                xParent->left = w->right;
                if (w->right) w->right->parent = xParent;
                w->right = xParent;
                xParent->parent = w;
                w = xParent->left;
            }

            bool wLeftBlack  = (!w || !w->left  || w->left->color  == BLACK);
            bool wRightBlack = (!w || !w->right || w->right->color == BLACK);

            // Случай 2 (симметрия)
            if (wLeftBlack && wRightBlack) {
                if (w) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Случай 3 (симметрия)
                if (wLeftBlack) {
                    if (w->right) w->right->color = BLACK;
                    if (w) w->color = RED;
                    Node* wRight = w->right;
                    xParent->left = wRight;
                    if (wRight) wRight->parent = xParent;
                    w->right = wRight ? wRight->left : nullptr;
                    if (wRight && wRight->left) wRight->left->parent = w;
                    if (wRight) wRight->left = w;
                    w->parent = wRight;
                    w = xParent->left;
                }
                // Случай 4 (симметрия)
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->left) w->left->color = BLACK;
                Node* grandpa = xParent->parent;
                replaceChild(root, grandpa, xParent, w);
                if (w) {
                    xParent->left = w->right;
                    if (w->right) w->right->parent = xParent;
                    w->right = xParent;
                    xParent->parent = w;
                }
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}

void deleteNode(Node*& root, int value) {
    // Ищем узел
    Node* z = root;
    while (z && z->value != value) {
        z = (value < z->value) ? z->left : z->right;
    }
    if (!z) return; // узел не найден

    Node* xParent = nullptr; // родитель узла, который займёт место удалённого
    Node* x = nullptr; // узел, который займёт место удалённого
    Color removedColor;      // цвет физически удалённого узла

    if (!z->left || !z->right) {
        // ── Узел имеет не более одного ребёнка ─────────────────────────────
        // Удаляем z напрямую, поднимая единственного ребёнка (или nullptr).
        removedColor = z->color;
        x = z->left ? z->left : z->right;
        xParent = z->parent;
        replaceChild(root, z->parent, z, x);
        delete z;
    } else {
        // ── У узла два ребёнка ──────────────────────────────────────────────
        // Находим in-order преемника (минимум в правом поддереве),
        // копируем его значение в z, затем физически удаляем преемника.
        Node* successor = treeMinimum(z->right);
        z->value = successor->value; // заменяем значение, не узел
        removedColor = successor->color;
        x = successor->right; // у преемника нет левого ребёнка
        xParent = successor->parent == z ? z : successor->parent;
        replaceChild(root, successor->parent, successor, x);
        delete successor;
    }

    // Если удалили чёрный узел — нарушена чёрная высота, исправляем.
    if (removedColor == BLACK)
        deleteFixup(root, x, xParent);
}


void printTree(Node* root, const string& prefix = "", bool isLeft = false) {
    if (!root) {
        cout << prefix << (isLeft ? "├── " : "└── ") << "(null)\n";
        return;
    }
    const char* c = (root->color == RED) ? "R" : "B";
    cout << prefix
              << (isLeft ? "├── " : "└── ")
              << root->value
              << " [" << "c=" << *c << "]\n";

    if (root->left || root->right) {
        printTree(root->left,  prefix + (isLeft ? "│   " : "    "), true);
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}






































void inorder(Node* node, std::vector<int>& out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->value);
    inorder(node->right, out);
}

int blackHeight(Node* node) {
    if (!node) return 1;
    int left  = blackHeight(node->left);
    int right = blackHeight(node->right);
    if (left == -1 || right == -1 || left != right) return -1;
    return left + (node->color == BLACK ? 1 : 0);
}

bool noDoubleRed(Node* node) {
    if (!node) return true;
    if (node->color == RED) {
        if (node->left  && node->left->color  == RED) return false;
        if (node->right && node->right->color == RED) return false;
    }
    return noDoubleRed(node->left) && noDoubleRed(node->right);
}

bool validParents(Node* node, Node* expectedParent = nullptr) {
    if (!node) return true;
    if (node->parent != expectedParent) return false;
    return validParents(node->left, node) && validParents(node->right, node);
}

bool isValidRBTree(Node* root) {
    if (!root) return true;
    if (root->color != BLACK)    return false;
    if (!noDoubleRed(root))      return false;
    if (blackHeight(root) == -1) return false;
    if (!validParents(root))     return false;
    return true;
}

void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

Node* buildTree(const std::vector<int>& values) {
    Node* root = nullptr;
    for (int v : values) insertNode(root, v);
    return root;
}


// ─── Тесты вставки (исходные) ────────────────────────────────────────────────

TEST(RBTree, EmptyTree) {
    Node* root = nullptr;
    EXPECT_EQ(root, nullptr);
}

TEST(RBTree, SingleInsert_RootIsBlack) {
    Node* root = nullptr;
    insertNode(root, 42);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 42);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, DuplicateInsert_Ignored) {
    Node* root = nullptr;
    insertNode(root, 10);
    insertNode(root, 10);
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ(vals.size(), 1u);
    freeTree(root);
}

TEST(RBTree, InOrder_IsSorted) {
    std::vector<int> input = {5, 3, 7, 1, 4, 6, 8};
    Node* root = buildTree(input);
    std::vector<int> vals;
    inorder(root, vals);
    std::vector<int> sorted = input;
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(vals, sorted);
    freeTree(root);
}

TEST(RBTree, AscendingInserts_ValidRBTree) {
    Node* root = nullptr;
    for (int i = 1; i <= 15; ++i) insertNode(root, i);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, DescendingInserts_ValidRBTree) {
    Node* root = nullptr;
    for (int i = 15; i >= 1; --i) insertNode(root, i);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, RandomInserts_ValidRBTree) {
    std::vector<int> input = {20, 5, 30, 1, 15, 25, 40, 10, 18, 3};
    Node* root = buildTree(input);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, LargeInsert_ValidRBTree) {
    Node* root = nullptr;
    for (int i = 1; i <= 100; ++i) insertNode(root, i);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ((int)vals.size(), 100);
    freeTree(root);
}

TEST(RBTree, RootAlwaysBlack) {
    Node* root = nullptr;
    for (int i : {10, 20, 30, 15, 25, 5, 1}) {
        insertNode(root, i);
        EXPECT_EQ(root->color, BLACK);
    }
    freeTree(root);
}

TEST(RBTree, BlackHeight_Consistent) {
    std::vector<int> input = {10, 5, 20, 3, 7, 15, 25, 1, 4, 6, 8};
    Node* root = buildTree(input);
    EXPECT_NE(blackHeight(root), -1);
    freeTree(root);
}

TEST(RBTree, NoDoubleRed) {
    std::vector<int> input = {10, 5, 20, 3, 7, 15, 25, 1, 4};
    Node* root = buildTree(input);
    EXPECT_TRUE(noDoubleRed(root));
    freeTree(root);
}

TEST(RBTree, ParentPointers_Valid) {
    std::vector<int> input = {50, 25, 75, 10, 30, 60, 80};
    Node* root = buildTree(input);
    EXPECT_TRUE(validParents(root));
    freeTree(root);
}

TEST(RBTree, NegativeValues) {
    std::vector<int> input = {-5, -10, 0, -3, 5};
    Node* root = buildTree(input);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    std::vector<int> sorted = input;
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(vals, sorted);
    freeTree(root);
}

TEST(RBTree, TwoElements_Structure) {
    Node* root = nullptr;
    insertNode(root, 10);
    insertNode(root, 5);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, ThreeAscending_LeftRotation) {
    Node* root = nullptr;
    insertNode(root, 1);
    insertNode(root, 2);
    insertNode(root, 3);
    EXPECT_EQ(root->value, 2);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

TEST(RBTree, ThreeDescending_RightRotation) {
    Node* root = nullptr;
    insertNode(root, 3);
    insertNode(root, 2);
    insertNode(root, 1);
    EXPECT_EQ(root->value, 2);
    EXPECT_EQ(root->color, BLACK);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}


// ─── Тесты удаления ──────────────────────────────────────────────────────────

// D1. Удаление несуществующего элемента не меняет деревоx
TEST(RBTreeDelete, DeleteNonExistent) {
    Node* root = buildTree({10, 5, 20});
    deleteNode(root, 99);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ(vals, (std::vector<int>{5, 10, 20}));
    freeTree(root);
}

// D2. Удаление единственного узла — дерево становится пустым
TEST(RBTreeDelete, DeleteOnlyNode) {
    Node* root = nullptr;
    insertNode(root, 42);
    deleteNode(root, 42);
    EXPECT_EQ(root, nullptr);
}

// D3. Удаление корня из дерева двух узлов
TEST(RBTreeDelete, DeleteRoot_TwoNodes) {
    Node* root = buildTree({10, 5});
    deleteNode(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->value, 5);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

// D4. После удаления in-order обход остаётся отсортированным
TEST(RBTreeDelete, DeleteMaintainsSortOrder) {
    Node* root = buildTree({5, 3, 7, 1, 4, 6, 8});
    deleteNode(root, 3);
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ(vals, (std::vector<int>{1, 4, 5, 6, 7, 8}));
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

// D5. Удаление красного листа
TEST(RBTreeDelete, DeleteRedLeaf) {
    Node* root = buildTree({10, 5, 20, 3});
    // 3 — красный лист
    deleteNode(root, 3);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ(vals, (std::vector<int>{5, 10, 20}));
    freeTree(root);
}

// D6. Удаление чёрного листа (требует fixup)
TEST(RBTreeDelete, DeleteBlackLeaf) {
    Node* root = buildTree({10, 5, 20});
    // 5 и 20 — чёрные листья
    deleteNode(root, 5);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

// D7. Удаление узла с двумя детьми
TEST(RBTreeDelete, DeleteNodeWithTwoChildren) {
    Node* root = buildTree({10, 5, 20, 3, 7, 15, 25});
    deleteNode(root, 10);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ(vals, (std::vector<int>{3, 5, 7, 15, 20, 25}));
    freeTree(root);
}

// D8. Последовательное удаление всех узлов
TEST(RBTreeDelete, DeleteAllNodes) {
    std::vector<int> vals = {10, 5, 20, 3, 7, 15, 25};
    Node* root = buildTree(vals);
    for (int v : vals) {
        deleteNode(root, v);
        if (root) EXPECT_TRUE(isValidRBTree(root));
    }
    EXPECT_EQ(root, nullptr);
}

// D9. Удаление из большого дерева сохраняет все инварианты
TEST(RBTreeDelete, LargeTree_DeleteHalf) {
    Node* root = nullptr;
    for (int i = 1; i <= 50; ++i) insertNode(root, i);
    for (int i = 1; i <= 50; i += 2) deleteNode(root, i); // удаляем нечётные
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    for (int i = 0; i < (int)vals.size(); ++i)
        EXPECT_EQ(vals[i], (i + 1) * 2);
    freeTree(root);
}

// D10. Удаление корня из большого дерева
TEST(RBTreeDelete, DeleteRoot_LargeTree) {
    Node* root = nullptr;
    for (int i = 1; i <= 20; ++i) insertNode(root, i);
    int rootVal = root->value;
    deleteNode(root, rootVal);
    EXPECT_TRUE(isValidRBTree(root));
    std::vector<int> vals;
    inorder(root, vals);
    EXPECT_EQ((int)vals.size(), 19);
    freeTree(root);
}

// D11. Повторное удаление одного значения — второй вызов безопасен
TEST(RBTreeDelete, DeleteSameValueTwice) {
    Node* root = buildTree({10, 5, 20});
    deleteNode(root, 5);
    EXPECT_TRUE(isValidRBTree(root));
    deleteNode(root, 5); // узла нет — ничего не должно сломаться
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

// D12. Удаление с последующей вставкой — дерево остаётся валидным
TEST(RBTreeDelete, DeleteThenInsert) {
    Node* root = buildTree({10, 5, 20, 3, 7});
    deleteNode(root, 5);
    insertNode(root, 6);
    EXPECT_TRUE(isValidRBTree(root));
    freeTree(root);
}

// D13. Случайный порядок удалений
TEST(RBTreeDelete, RandomDeleteOrder) {
    std::vector<int> input = {20, 5, 30, 1, 15, 25, 40, 10, 18, 3};
    Node* root = buildTree(input);
    std::vector<int> toDelete = {15, 1, 30, 5, 20};
    for (int v : toDelete) {
        deleteNode(root, v);
        EXPECT_TRUE(isValidRBTree(root));
    }
    freeTree(root);
}


// ─── Main ─────────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}