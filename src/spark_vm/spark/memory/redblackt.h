//
// Created by Kirill Zhukov on 27.02.2023.
//

#ifndef VM_WITH_HEAP_REDBLACKT_H
#define VM_WITH_HEAP_REDBLACKT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include "pages.h"
#include "chunk.h"

//#define TNULL NULL

#define rbTree(a_type)                                                                  \
struct rb_node##a_type {                                                                \
    a_type *ch;                                                                         \
    struct rb_node##a_type *parent;                                                     \
    struct rb_node##a_type *left;                                                       \
    struct rb_node##a_type *right;                                                      \
    bool color;                                                                         \
};                                                                                      \
                                                                                        \
struct rb_tree##a_type {                                                                \
    struct rb_node##a_type *root = NULL;                                                \
    struct rb_node##a_type *TNULL = NULL;                                               \
};                                                                                      \
void preOrderHelper(struct rb_node##a_type *node) {                                     \
    if (node != TNULL) {                                                                \
        printf("%lu\n", node->ch->size);                                                \
        preOrderHelper(node->left);                                                     \
        preOrderHelper(node->right);                                                    \
    }                                                                                   \
}                                                                                       \
void inOrderHelper(struct rb_node##a_type *node) {                                      \
    if (node != TNULL) {                                                                \
        inOrderHelper(node->left);                                                      \
        printf("%lu\n", node->ch->size);                                                \
        inOrderHelper(node->right);                                                     \
    }                                                                                   \
}                                                                                       \
void postOrderHelper(struct rb_node##a_type *node) {                                    \
    if (node != TNULL) {                                                                \
        postOrderHelper(node->left);                                                    \
        postOrderHelper(node->right);                                                   \
        printf("%lu\n", node->ch->size);                                                \
    }                                                                                   \
}                                                                                       \
struct rb_node##a_type *searchTreeHelper(struct rb_node##a_type *node, size_t key) {    \
    if (node == TNULL || key == node->ch->size) {                                       \
        return node;                                                                    \
    }                                                                                   \
    if (key < node->ch->size) {                                                         \
        return searchTreeHelper(node->left, key);                                       \
    }                                                                                   \
    return searchTreeHelper(node->right, key);                                          \
}                                                                                       \
void deleteFix(struct rb_node##a_type *root, struct rb_node##a_type *x) {               \
    struct rb_node##a_type *s;                                                          \
    while (x != root && x->color == false) {                                            \
        if (x == x->parent->left) {                                                     \
            s = x->parent->right;                                                       \
            if (s->color == true) {                                                     \
                s->color = false;                                                       \
                x->parent->color = true;                                                \
                leftRotate(x->parent);                                                  \
                s = x->parent->right;                                                   \
            }                                                                           \
            if (s->left->color == false && s->right->color == false) {                  \
                s->color = true;                                                        \
                x = x->parent;                                                          \
            } else {                                                                    \
                if (s->right->color == false) {                                         \
                    s->left->color = false;                                             \
                    s->color = true;                                                    \
                    rightRotate(s);                                                     \
                    s = x->parent->right;                                               \
                }                                                                       \
                s->color = x->parent->color;                                            \
                x->parent->color = false;                                               \
                s->right->color = false;                                                \
                leftRotate(x->parent);                                                  \
                x = root;                                                               \
            }                                                                           \
        } else {                                                                        \
            s = x->parent->left;                                                        \
            if (s->color == true) {                                                     \
                s->color = false;                                                       \
                x->parent->color = true;                                                \
                rightRotate(x->parent);                                                 \
                s = x->parent->left;                                                    \
            }                                                                           \
            if (s->right->color == false && s->right->color == false) {                 \
                s->color = true;                                                        \
                x = x->parent;                                                          \
            } else {                                                                    \
                if (s->left->color == false) {                                          \
                    s->right->color = false;                                            \
                    s->color = true;                                                    \
                    leftRotate(s);                                                      \
                    s = x->parent->left;                                                \
                }                                                                       \
                s->color = x->parent->color;                                            \
                x->parent->color = false;                                               \
                s->left->color = false;                                                 \
                rightRotate(x->parent);                                                 \
                x = root;                                                               \
            }                                                                           \
        }                                                                               \
    }                                                                                   \
    x->color = false;                                                                   \
}                                                                                       \
void rbTransplant(struct rb_node##a_type *u, struct rb_node##a_type *v) {               \
    if (u->parent == nullptr) {                                                         \
        root = v;                                                                       \
    } else if (u == u->parent->left) {                                                  \
        u->parent->left = v;                                                            \
    } else {                                                                            \
        u->parent->right = v;                                                           \
    }                                                                                   \
    v->parent = u->parent;                                                              \
}                                                                                       \
void deleteNodeHelper(struct rb_node##a_type *node, size_t key) {                       \
    struct rb_node##a_type *z = TNULL;                                                  \
    struct rb_node##a_type *x, *y;                                                      \
    while (node != TNULL) {                                                             \
        if (node->ch->size == key) {                                                    \
            z = node;                                                                   \
        }                                                                               \
        if (node->ch->size <= key) {                                                    \
            node = node->right;                                                         \
        } else {                                                                        \
            node = node->left;                                                          \
        }                                                                               \
    }                                                                                   \
    if (z == TNULL) {                                                                   \
        puts("Key not found in the tree");                                              \
        return;                                                                         \
    }                                                                                   \
    y = z;                                                                              \
    bool y_original_color = y->color;                                                   \
    if (z->left == TNULL) {                                                             \
        x = z->right;                                                                   \
        rbTransplant(z, z->right);                                                      \
    } else if (z->right == TNULL) {                                                     \
        x = z->left;                                                                    \
        rbTransplant(z, z->left);                                                       \
    } else {                                                                            \
        y = minimum(z->right);                                                          \
        y_original_color = y->color;                                                    \
        x = y->right;                                                                   \
        if (y->parent == z) {                                                           \
            x->parent = y;                                                              \
        } else {                                                                        \
            rbTransplant(y, y->right);                                                  \
            y->right = z->right;                                                        \
            y->right->parent = y;                                                       \
        }                                                                               \
        rbTransplant(z, y);                                                             \
        y->left = z->left;                                                              \
        y->left->parent = y;                                                            \
        y->color = z->color;                                                            \
    }                                                                                   \
    /*                                                                                  \
    #ifdef _WIN32                                                                       \
        VirtualFree((void *)z, sizeof(rbNode), MEM_RELEASE);                            \
    #endif                                                                              \
    */                                                                                  \
    if (y_original_color == false) {                                                    \
        deleteFix(x);                                                                   \
    }                                                                                   \
}                                                                                       \
void insertFix(struct rb_node##a_type *root, struct rb_node##a_type *k) {               \
    struct rb_node##a_type *u;                                                          \
    while (k->parent->color == true) {                                                  \
        if (k->parent == k->parent->parent->right) {                                    \
            u = k->parent->parent->left;                                                \
            if (u->color == true) {                                                     \
                u->color = false;                                                       \
                k->parent->color = false;                                               \
                k->parent->parent->color = true;                                        \
                k = k->parent->parent;                                                  \
            } else {                                                                    \
                if (k == k->parent->left) {                                             \
                    k = k->parent;                                                      \
                    rightRotate(k);                                                     \
                }                                                                       \
                k->parent->color = false;                                               \
                k->parent->parent->color = true;                                        \
                leftRotate(k->parent->parent);                                          \
            }                                                                           \
        } else {                                                                        \
            u = k->parent->parent->right;                                               \
            if (u->color == true) {                                                     \
                u->color = false;                                                       \
                k->parent->color = false;                                               \
                k->parent->parent->color = true;                                        \
                k = k->parent->parent;                                                  \
            } else {                                                                    \
                if (k == k->parent->right) {                                            \
                    k = k->parent;                                                      \
                    leftRotate(k);                                                      \
                }                                                                       \
                k->parent->color = false;                                               \
                k->parent->parent->color = true;                                        \
                rightRotate(k->parent->parent);                                         \
            }                                                                           \
        }                                                                               \
        if (k == root) {                                                                \
            break;                                                                      \
        }                                                                               \
    }                                                                                   \
    root->color = false;                                                                \
}                                                                                       \
void preorder(struct rb_node##a_type *root) {                                           \
    preOrderHelper(root);                                                               \
}                                                                                       \
void inorder(struct rb_node##a_type *root) {                                            \
    inOrderHelper(root);                                                                \
}                                                                                       \
void postorder(struct rb_node##a_type *root) {                                          \
    postOrderHelper(root);                                                              \
}                                                                                       \
struct rb_node##a_type *searchTree(struct rb_node##a_type *root, size_t k) {            \
    return searchTreeHelper(root, k);                                                   \
}                                                                                       \
/*                                                                                      \
void printHelper(struct rb_node##a_type *root, char* indent, bool last) {               \
    if (root != TNULL) {                                                                \
        puts(indent);                                                                   \
        if (last) {                                                                     \
            puts("R----");                                                              \
            indent += "   ";                                                            \
        } else {                                                                        \
            std::cout << "L----";                                                       \
            indent += "|  ";                                                            \
        }                                                                               \
        std::string sColor = root->color ? "RED" : "BLACK";                             \
        std::cout << root->ch->size << "(" << sColor << ")" << std::endl;               \
        printHelper(root->left, indent, false);                                         \
        printHelper(root->right, indent, true);                                         \
    }                                                                                   \
}                                                                                       \
*/                                                                                      \
struct rb_node##a_type *minimum(struct rb_node##a_type *node) {                         \
    while (node->left != TNULL) {                                                       \
        node = node->left;                                                              \
    }                                                                                   \
    return node;                                                                        \
}                                                                                       \
struct rb_node##a_type *maximum(struct rb_node##a_type *node) {                         \
    while (node->right != TNULL) {                                                      \
        node = node->right;                                                             \
    }                                                                                   \
    return node;                                                                        \
}                                                                                       \
struct rb_node##a_type *successor(struct rb_node##a_type *x) {                          \
    if (x->right != TNULL) {                                                            \
        return minimum(x->right);                                                       \
    }                                                                                   \
    struct rb_node##a_type *y = x->parent;                                              \
    while (y != TNULL && x == y->right) {                                               \
        x = y;                                                                          \
        y = y->parent;                                                                  \
    }                                                                                   \
    return y;                                                                           \
}                                                                                       \
struct rb_node##a_type *predecessor(struct rb_node##a_type *x) {                        \
    if (x->left != TNULL) {                                                             \
        return maximum(x->left);                                                        \
    }                                                                                   \
    struct rb_node##a_type *y = x->parent;                                              \
    while (y != TNULL && x == y->left) {                                                \
        x = y;                                                                          \
        y = y->parent;                                                                  \
    }                                                                                   \
    return y;                                                                           \
}                                                                                       \
void leftRotate(struct rb_node##a_type *root, struct rb_node##a_type *x) {              \
    struct rb_node##a_type *y = x->right;                                               \
    x->right = y->left;                                                                 \
    if (y->left != TNULL) {                                                             \
        y->left->parent = x;                                                            \
    }                                                                                   \
    y->parent = x->parent;                                                              \
    if (x->parent == NULL) {                                                            \
        root = y;                                                                       \
    } else if (x == x->parent->left) {                                                  \
        x->parent->left = y;                                                            \
    } else {                                                                            \
        x->parent->right = y;                                                           \
    }                                                                                   \
    y->left = x;                                                                        \
    x->parent = y;                                                                      \
}                                                                                       \
void rightRotate(struct rb_node##a_type *root, struct rb_node##a_type *x) {             \
    struct rb_node##a_type *y = x->left;                                                \
    x->left = y->right;                                                                 \
    if (y->right != TNULL) {                                                            \
        y->right->parent = x;                                                           \
    }                                                                                   \
    y->parent = x->parent;                                                              \
    if (x->parent == NULL) {                                                            \
        root = y;                                                                       \
    } else if (x == x->parent->right) {                                                 \
        x->parent->right = y;                                                           \
    } else {                                                                            \
        x->parent->left = y;                                                            \
    }                                                                                   \
    y->right = x;                                                                       \
    x->parent = y;                                                                      \
}                                                                                       \
void insert(struct rb_node##a_type *root, void *ptr) {                                  \
    if (root == NULL) {                                                                 \
        TNULL = (struct rb_node##a_type *) ptr;                                         \
        *TNULL = {.left = NULL, .right = NULL, .color = false};                         \
        root = TNULL;                                                                   \
    }                                                                                   \
    struct rb_node##a_type  *node = (rb_node##a_type *) ptr;                                     \
    *node = {.parent = NULL, .left = TNULL, .right = TNULL, .color = true};             \
    struct rb_node##a_type *y = NULL;                                                   \
    struct rb_node##a_type *x = root;                                                   \
    while (x != TNULL) {                                                                \
        y = x;                                                                          \
        if (node->ch->size < x->ch->size) {                                             \
            x = x->left;                                                                \
        } else {                                                                        \
            x = x->right;                                                               \
        }                                                                               \
    }                                                                                   \
    node->parent = y;                                                                   \
    if (y == NULL) {                                                                    \
        root = node;                                                                    \
    } else if (node->ch->size < y->ch->size) {                                          \
        y->left = node;                                                                 \
    } else {                                                                            \
        y->right = node;                                                                \
    }                                                                                   \
    if (node->parent == NULL) {                                                         \
        node->color = false;                                                            \
        return;                                                                         \
    }                                                                                   \
    if (node->parent->parent == NULL) {                                                 \
        return;                                                                         \
    }                                                                                   \
    insertFix(node);                                                                    \
}                                                                                       \
void deleteNode(struct rb_node##a_type *root, size_t size) {                            \
    deleteNodeHelper(root, size);                                                       \
}                                                                                       \
void printTree(struct rb_node##a_type * root) {                                         \
    if (root) {                                                                         \
        printHelper(root, "", true);                                                    \
    }                                                                                   \
}


struct rb_node {
    chunk_t ch;
    struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;
    bool color;
};

struct rb_tree {
    struct rb_node *TNULL = NULL;
    struct rb_node *root = NULL;
};
void preOrderHelper(struct rb_node *TNULL, struct rb_node *node) {
    if (node != TNULL) {
        printf("%lu\n", node->ch->size);
        preOrderHelper(TNULL, node->left);
        preOrderHelper(TNULL, node->right);
    }
}
void inOrderHelper(struct rb_node *TNULL, struct rb_node *node) {
    if (node != TNULL) {
        inOrderHelper(TNULL, node->left);
        printf("%lu\n", node->ch->size);
        inOrderHelper(TNULL, node->right);
    }
}
void postOrderHelper(struct rb_node *TNULL, struct rb_node *node) {
    if (node != TNULL) {
        postOrderHelper(TNULL, node->left);
        postOrderHelper(TNULL, node->right);
        printf("%lu\n", node->ch->size);
    }
}
struct rb_node *searchTreeHelper(struct rb_node *node, struct rb_node *TNULL, size_t key) {
    if (node == TNULL || key == node->ch->size) {
        return node;
    }
    if (key < node->ch->size) {
        return searchTreeHelper(node->left, TNULL, key);
    }
    return searchTreeHelper(node->right, TNULL, key);
}
void leftRotate(struct rb_node *root, struct rb_node *TNULL, struct rb_node *x) {
    struct rb_node *y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void rightRotate(struct rb_node *root, struct rb_node *TNULL, struct rb_node *x) {
    struct rb_node *y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
struct rb_node *minimum(struct rb_node *TNULL, struct rb_node *node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}
struct rb_node *maximum(struct rb_node *TNULL, struct rb_node *node) {
    while (node->right != TNULL) {
        node = node->right;
    }
    return node;
}
struct rb_node *successor(struct rb_node *TNULL, struct rb_node *x) {
    if (x->right != TNULL) {
        return minimum(TNULL, x->right);
    }
    struct rb_node *y = x->parent;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}
struct rb_node *predecessor(struct rb_node *TNULL, struct rb_node *x) {
    if (x->left != TNULL) {
        return maximum(TNULL, x->left);
    }
    struct rb_node *y = x->parent;
    while (y != TNULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}
void deleteFix(struct rb_node *root, struct rb_node *TNULL, struct rb_node *x) {
    struct rb_node *s;
    while (x != root && x->color == false) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == true) {
                s->color = false;
                x->parent->color = true;
                leftRotate(root, TNULL, x->parent);
                s = x->parent->right;
            }
            if (s->left->color == false && s->right->color == false) {
                s->color = true;
                x = x->parent;
            } else {
                if (s->right->color == false) {
                    s->left->color = false;
                    s->color = true;
                    rightRotate(root, TNULL, s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = false;
                s->right->color = false;
                leftRotate(root, TNULL, x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == true) {
                s->color = false;
                x->parent->color = true;
                rightRotate(root, TNULL, x->parent);
                s = x->parent->left;
            }
            if (s->right->color == false && s->right->color == false) {
                s->color = true;
                x = x->parent;
            } else {
                if (s->left->color == false) {
                    s->right->color = false;
                    s->color = true;
                    leftRotate(root, TNULL, s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = false;
                s->left->color = false;
                rightRotate(root, TNULL, x->parent);
                x = root;
            }
        }
    }
    x->color = false;
}
void rbTransplant(struct rb_node *root, struct rb_node *u, struct rb_node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}
void deleteNodeHelper(struct rb_node *root, struct rb_node *TNULL, struct rb_node *node, size_t key) {
    struct rb_node *z = TNULL;
    struct rb_node *x, *y;
    while (node != TNULL) {
        if (node->ch->size == key) {
            z = node;
        }
        if (node->ch->size <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (z == TNULL) {
        puts("Key not found in the tree");
        return;
    }
    y = z;
    bool y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(root, z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(root, z, z->left);
    } else {
        y = minimum(TNULL, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    /*
    #ifdef _WIN32
        VirtualFree((void *)z, sizeof(rbNode), MEM_RELEASE);
    #endif
    */
    if (!y_original_color) {
        deleteFix(root, TNULL, x);
    }
}
void insertFix(struct rb_node *root, struct rb_node *TNULL, struct rb_node *k) {
    struct rb_node *u;
    while (k->parent->color) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color) {
                u->color = false;
                k->parent->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(root, TNULL, k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                leftRotate(root, TNULL, k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color) {
                u->color = false;
                k->parent->color = false;
                k->parent->parent->color = true;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(root, TNULL, k);
                }
                k->parent->color = false;
                k->parent->parent->color = true;
                rightRotate(root, TNULL, k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = false;
}
void preorder(struct rb_node *root, struct rb_node *TNULL) {
    preOrderHelper(root, TNULL);
}
void inorder(struct rb_node *root, struct rb_node *TNULL) {
    inOrderHelper(root, TNULL);
}
void postorder(struct rb_node *root, struct rb_node *TNULL) {
    postOrderHelper(root, TNULL);
}
struct rb_node *searchTree(struct rb_node *root, struct rb_node *TNULL, size_t k) {
    return searchTreeHelper(root, TNULL, k);
}
//void insert(struct rb_node *root, struct rb_node *TNULL, void *ptr) {
//    if (root == NULL) {
//        TNULL = (struct rb_node *) ptr;
//        *TNULL = {.left = NULL, .right = NULL, .color = false};
//        root = TNULL;
//    }
//    struct rb_node  *node = (rb_node *) ptr;
//    *node = {.parent = NULL, .left = TNULL, .right = TNULL, .color = true};
//    struct rb_node *y = NULL;
//    struct rb_node *x = root;
//    while (x != NULL) {
//        y = x;
//        if (node->ch->size < x->ch->size) {
//            x = x->left;
//        } else {
//            x = x->right;
//        }
//    }
//    node->parent = y;
//    if (y == NULL) {
//        root = node;
//    } else if (node->ch->size < y->ch->size) {
//        y->left = node;
//    } else {
//        y->right = node;
//    }
//    if (node->parent == NULL) {
//        node->color = false;
//        return;
//    }
//    if (node->parent->parent == NULL) {
//        return;
//    }
//    insertFix(root, TNULL, node);
}

void insert(struct rb_node *root, struct rb_node *TNULL, void *ptr, size_t key) {
    if (root == nullptr) {
        TNULL = (rb_node *) ptr;
        *TNULL = {.left = nullptr, .right = nullptr, .color = false};
        root = TNULL;
    }
    struct rb_node *node = (rb_node *) ptr;
    *node = {.parent = NULL, .left = TNULL, .right = TNULL, .color = true};
    rb_node *y = nullptr;
    rb_node *x = root;

    while (x != TNULL) {
        y = x;
        if (node->ch->size < x->ch->size) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->ch->size < y->ch->size) {
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

    insertFix(root, TNULL, node);
}

void deleteNode(struct rb_node *root, struct rb_node *TNULL, size_t size) {
    rb_node *node = root;
    deleteNodeHelper(root, TNULL, node, size);
}

//void printHelper(struct rb_node *root, struct rb_node *TNULL, std::string indent, bool last) {
//    if (root != TNULL) {
//        puts(indent.c_str());
//        if (last) {
//            puts("R----");
//            indent += "   ";
//        } else {
//            std::cout << "L----";
//            indent += "|  ";
//        }
//        std::string sColor = root->color ? "RED" : "BLACK";
//        std::cout << root->ch->size << "(" << sColor << ")" << std::endl;
//        printHelper(root->left, TNULL, indent, false);
//        printHelper(root->right, TNULL, indent, true);
//    }
//}
//
//void printTree(struct rb_node *root, struct rb_node *TNULL) {
//    if (root) {
//        printHelper(root, TNULL, "", true);
//    }
//}



#endif //VM_WITH_HEAP_REDBLACKT_H
