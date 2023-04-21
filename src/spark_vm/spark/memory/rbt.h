// Implementing Red-Black Tree in C++

#include <iostream>

using namespace std;

extern "C"
{
struct rbNode {
    size_t size;
    rbNode *parent;
    rbNode *left;
    rbNode *right;
    bool color;
};
};

class RedBlackTree {
private:
    rbNode *root = nullptr;
    rbNode *TNULL = nullptr;

    // Preorder
    void preOrderHelper(rbNode *node) {
        if (node != TNULL) {
            cout << node->size << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(rbNode *node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->size << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(rbNode *node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->size << " ";
        }
    }

    rbNode *searchTreeHelper(rbNode *node, size_t key) {
        if (node == TNULL || key == node->size) {
            return node;
        }

        if (key < node->size) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(rbNode *x) {
        rbNode *s;
        while (x != root && x->color == false) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == false && s->right->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->right->color == false) {
                        s->left->color = false;
                        s->color = true;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->right->color = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == true) {
                    s->color = false;
                    x->parent->color = true;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == false && s->right->color == false) {
                    s->color = true;
                    x = x->parent;
                } else {
                    if (s->left->color == false) {
                        s->right->color = false;
                        s->color = true;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->left->color = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = false;
    }

    void rbTransplant(rbNode *u, rbNode *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(rbNode *node, size_t key) {
        rbNode *z = TNULL;
        rbNode *x, *y;
        while (node != TNULL) {
            if (node->size == key) {
                z = node;
            }

            if (node->size <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        bool y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        #ifdef _WIN32
            VirtualFree((void *) z, sizeof(rbNode), MEM_RELEASE);
        #endif
        if (y_original_color == false) {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(rbNode *k) {
        rbNode *u;
        while (k->parent->color == true) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == true) {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = false;
    }

    void printHelper(rbNode *root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->size << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    void preorder() {
        preOrderHelper(this->root);
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    void postorder() {
        postOrderHelper(this->root);
    }

    rbNode *searchTree(size_t k) {
        return searchTreeHelper(this->root, k);
    }

    rbNode *minimum(rbNode *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    rbNode *maximum(rbNode *node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    rbNode *successor(rbNode *x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        rbNode *y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    rbNode *predecessor(rbNode *x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        rbNode *y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(rbNode *x) {
        rbNode *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(rbNode *x) {
        rbNode *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(void *ptr, size_t key) {
        if (root == nullptr) {
            TNULL = (rbNode *) ptr;
            *TNULL = {.left = nullptr, .right = nullptr, .color = false};
            root = TNULL;
        }
        rbNode *node = (rbNode *) ptr;
        *node = {.size = key, .parent = nullptr, .left = TNULL, .right = TNULL, .color = true};
        rbNode *y = nullptr;
        rbNode *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->size < x->size) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->size < y->size) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = false;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    rbNode *
    getRoot() {
        return this->root;
    }

    void deleteNode(size_t size) {
        deleteNodeHelper(this->root, size);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};
