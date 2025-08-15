#include <iostream>
#include <queue>

using namespace std;

// 节点颜色枚举
enum Color { RED, BLACK };

// 红黑树节点类
template <typename T>
class RBTreeNode {
public:
    T data;                 // 节点存储的数据
    Color color;            // 节点颜色
    RBTreeNode* left;       // 左孩子
    RBTreeNode* right;      // 右孩子
    RBTreeNode* parent;     // 父节点

    // 构造函数
    RBTreeNode(T val, Color c = RED, RBTreeNode* l = nullptr, RBTreeNode* r = nullptr, RBTreeNode* p = nullptr)
        : data(val), color(c), left(l), right(r), parent(p) {}
};

// 红黑树类
template <typename T>
class RBTree {
private:
    RBTreeNode<T>* root;    // 根节点
    RBTreeNode<T>* nil;     // 哨兵节点（代表空节点）

    // 初始化哨兵节点
    void initNil() {
        nil = new RBTreeNode<T>(T(), BLACK);
        nil->left = nil->right = nil->parent = nil;
    }

public:
    // 构造函数
    RBTree() {
        initNil();
        root = nil;
    }

    // 析构函数
    ~RBTree() {
        destroy(root);
        delete nil;
    }

    // 销毁红黑树
    void destroy(RBTreeNode<T>* node) {
        if (node != nil) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    // 左旋
    void leftRotate(RBTreeNode<T>* x) {
        RBTreeNode<T>* y = x->right;    // 设置y为x的右孩子
        x->right = y->left;             // 将y的左子树变为x的右子树

        if (y->left != nil) {
            y->left->parent = x;        // 如果y的左子树非空，设置其父节点为x
        }

        y->parent = x->parent;          // 将y的父节点设为x的父节点

        if (x->parent == nil) {
            root = y;                   // 如果x是根节点，则y成为新的根节点
        } else if (x == x->parent->left) {
            x->parent->left = y;        // 如果x是其父节点的左孩子，则y成为其父节点的左孩子
        } else {
            x->parent->right = y;      // 如果x是其父节点的右孩子，则y成为其父节点的右孩子
        }

        y->left = x;                    // 将x设为y的左孩子
        x->parent = y;                  // 将x的父节点设为y
    }

    // 右旋（与左旋对称）
    void rightRotate(RBTreeNode<T>* y) {
        RBTreeNode<T>* x = y->left;
        y->left = x->right;

        if (x->right != nil) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nil) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    // 插入节点
    void insert(const T& val) {
        RBTreeNode<T>* z = new RBTreeNode<T>(val, RED, nil, nil, nil);
        RBTreeNode<T>* y = nil;
        RBTreeNode<T>* x = root;

        // 寻找插入位置
        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;                   // 树为空，z成为根节点
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        z->left = z->right = nil;
        z->color = RED;               // 新插入节点初始为红色

        insertFixup(z);                // 调整红黑树性质
    }

    // 插入后调整红黑树性质
    void insertFixup(RBTreeNode<T>* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBTreeNode<T>* y = z->parent->parent->right;  // y是z的叔节点

                if (y->color == RED) {                        // 情况3：叔节点是红色
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {             // 情况4：z是右孩子
                        z = z->parent;
                        leftRotate(z);
                    }
                    // 情况5：z是左孩子
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {  // 对称情况，父节点是右孩子
                RBTreeNode<T>* y = z->parent->parent->left;

                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;  // 确保根节点为黑色
    }

    // 查找节点
    RBTreeNode<T>* search(const T& val) const {
        RBTreeNode<T>* x = root;
        while (x != nil && x->data != val) {
            if (val < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }

    // 查找最小节点
    RBTreeNode<T>* minimum(RBTreeNode<T>* x) const {
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }

    // 查找最大节点
    RBTreeNode<T>* maximum(RBTreeNode<T>* x) const {
        while (x->right != nil) {
            x = x->right;
        }
        return x;
    }

    // 用v替换u
    void transplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // 删除节点
    void remove(const T& val) {
        RBTreeNode<T>* z = search(val);
        if (z == nil) return;  // 节点不存在

        RBTreeNode<T>* y = z;
        RBTreeNode<T>* x;
        Color y_original_color = y->color;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK) {
            removeFixup(x);  // 如果删除的是黑色节点，需要调整
        }
    }

    // 删除后调整红黑树性质
    void removeFixup(RBTreeNode<T>* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTreeNode<T>* w = x->parent->right;  // w是x的兄弟节点

                if (w->color == RED) {              // 情况1：兄弟节点是红色
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK && w->right->color == BLACK) {  // 情况2：兄弟的两个孩子都是黑色
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {   // 情况3：兄弟的右孩子是黑色
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // 情况4：兄弟的右孩子是红色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {  // 对称情况，x是右孩子
                RBTreeNode<T>* w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // 中序遍历（递归辅助函数）
    void inOrderHelper(RBTreeNode<T>* node) const {
        if (node != nil) {
            inOrderHelper(node->left);
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inOrderHelper(node->right);
        }
    }

    // 中序遍历
    void inOrder() const {
        inOrderHelper(root);
        cout << endl;
    }

    // 层序遍历（用于打印树结构）
    void levelOrder() const {
        if (root == nil) return;

        queue<RBTreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            RBTreeNode<T>* node = q.front();
            q.pop();

            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";

            if (node->left != nil) q.push(node->left);
            if (node->right != nil) q.push(node->right);
        }
        cout << endl;
    }
};

// 测试代码
int main() {
    RBTree<int> rbTree;

    // 插入测试
    cout << "Inserting 10, 20, 30, 15, 25, 5, 35, 12, 18:" << endl;
    rbTree.insert(10);
    rbTree.insert(20);
    rbTree.insert(30);
    rbTree.insert(15);
    rbTree.insert(25);
    rbTree.insert(5);
    rbTree.insert(35);
    rbTree.insert(12);
    rbTree.insert(18);

    cout << "In-order traversal: ";
    rbTree.inOrder();

    cout << "Level-order traversal: ";
    rbTree.levelOrder();

    // 查找测试
    cout << "\nSearching for 15: ";
    auto node = rbTree.search(15);
    if (node != nullptr) {
        cout << "Found: " << node->data << endl;
    } else {
        cout << "Not found" << endl;
    }

    // 删除测试
    cout << "\nDeleting 20, 5:" << endl;
    rbTree.remove(20);
    rbTree.remove(5);

    cout << "In-order traversal after deletion: ";
    rbTree.inOrder();

    cout << "Level-order traversal after deletion: ";
    rbTree.levelOrder();

    return 0;
}

