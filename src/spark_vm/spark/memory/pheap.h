//
// Created by Kirill Zhukov on 03.01.2023.
//

#ifndef VM_WITH_HEAP_PHEAP_H
#define VM_WITH_HEAP_PHEAP_H
#include <cstdio>
#include "share/s_ti.h"

extern "C" {
    ///              ________________________
    ///             | pairing_heap_min_node |
    ///             ------------------------
    ///            /                        \
    ///           /                          \
    ///          /                            \
    ///       ___________                  ___________
    ///      | HeapNode |                 | HeapNode |
    ///      -----------                  -----------
    struct HeapNode {
        int key{};
        HeapNode *leftChild;
        HeapNode *nextSibling;
        tvalue *obj{};

        HeapNode() : leftChild(NULL), nextSibling(NULL) {}
        // creates a new node
        HeapNode(int key_, HeapNode *leftChild_, HeapNode *nextSibling_) : key(key_), leftChild(leftChild_), nextSibling(nextSibling_) {}

        // Adds a child and sibling to the node
        void addChild(HeapNode *node) {
            if (leftChild == NULL) leftChild = node;
            else {
                node->nextSibling = leftChild;
                leftChild = node;
            }
        }
    };

    // Returns true if root of the tree
    // is null otherwise returns false
    bool empty(HeapNode *node) {
        return (node == NULL);
    }

    // Function to merge two heaps
    HeapNode *merge(HeapNode *A, HeapNode *B) {
        // If any of the two-nodes is null
        // the return the not null node
        if (A == NULL) return B;
        if (B == NULL) return A;

        // To maintain the min heap condition compare
        // the nodes and node with minimum value become
        // parent of the other node
        if (A->key < B->key) {
            A->addChild(B);
            return A;
        } else {
            B->addChild(A);
            return B;
        }

        return NULL; // Unreachable
    }

    // Returns the root value of the heap
    int Top(HeapNode *node) {
        return node->key;
    }

    // Function to insert the new node in the heap
    HeapNode *insert(HeapNode *node, int key) {
        return merge(node, new HeapNode(key, NULL, NULL));
    }

    // This method is used when we want to delete root node
    HeapNode *twoPassMerge(HeapNode *node) {
        if (node == NULL || node->nextSibling == NULL)
            return node;
        else {
            HeapNode *A, *B, *newNode;
            A = node;
            B = node->nextSibling;
            newNode = node->nextSibling->nextSibling;

            A->nextSibling = NULL;
            B->nextSibling = NULL;

            return merge(merge(A, B), twoPassMerge(newNode));
        }

        return NULL; // Unreachable
    }

    // Function to delete the root node in heap
    HeapNode *deleteNode(HeapNode *node) {
        return twoPassMerge(node->leftChild);
    }

    struct PairingHeap {
        HeapNode *root;

        PairingHeap() : root(NULL) {}

        bool empty() const {
            return ::empty(root);
        }

        int top() const {
            return ::Top(root);
        }

        void insert(int key) {
            root = ::insert(root, key);
        }

        void deleteRootNode() {
            root = ::deleteNode(root);
        }

        void join(PairingHeap other) {
            root = ::merge(root, other.root);
        }

    };
};

#endif //VM_WITH_HEAP_PHEAP_H
