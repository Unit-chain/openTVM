//
// Created by Kirill Zhukov on 23.11.2022.
//

#ifndef VM_WITH_HEAP_PAIRINGHEAP_H
#define VM_WITH_HEAP_PAIRINGHEAP_H
#include "iostream"

using namespace std;

// Heap structure
struct HeapNode {
    int key;
    HeapNode *leftChild;
    HeapNode *nextSibling;

    HeapNode():leftChild(nullptr) {}

    // creates a new node
    HeapNode(int key_, HeapNode *leftChild_, HeapNode *nextSibling_):
            key(key_), leftChild(leftChild_), nextSibling(nextSibling_) {}

    // Adds a child and sibling to the node
    void addChild(HeapNode *node) {
        if(leftChild == nullptr)
            leftChild = node;
        else {
            node->nextSibling = leftChild;
            leftChild = node;
        }
    }
};

// Returns true if root of the tree
// is nullptr otherwise returns false
bool empty(HeapNode *node) {
    return (node == nullptr);
}

// Function to merge two heaps
HeapNode *merge(HeapNode *A, HeapNode *B)
{
    // If any of the two-nodes is nullptr
    // the return the not nullptr node
    if(A == nullptr) return B;
    if(B == nullptr) return A;

    // To maintain the min heap condition compare
    // the nodes and node with minimum value become
    // parent of the other node
    if(A->key < B->key) {
        A->addChild(B);
        return A;
    }
    else {
        B->addChild(A);
        return B;
    }

    return nullptr; // Unreachable
}

// Returns the root value of the heap
int Top(HeapNode *node) {
    return node->key;
}

// Function to insert the new node in the heap
HeapNode *insert(HeapNode *node, int key) {
    return merge(node, new HeapNode(key, nullptr, nullptr));
}

// This method is used when we want to delete root node
HeapNode *twoPassMerge(HeapNode *node) {
    if(node == nullptr || node->nextSibling == nullptr)
        return node;
    else {
        HeapNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = nullptr;
        B->nextSibling = nullptr;

        return merge(merge(A, B), twoPassMerge(newNode));
    }

    return nullptr; // Unreachable
}

// Function to delete the root node in heap
HeapNode *deleteNode(HeapNode *node) {
    return twoPassMerge(node->leftChild);
}

struct PairingHeap {
    HeapNode *root;

    PairingHeap():
            root(nullptr) {}

    bool empty(void) {
        return ::empty(root);
    }

    int top(void) {
        return ::Top(root);
    }

    void insert(int key) {
        root = ::insert(root, key);
    }

    void deleteRootNode(void) {
        root = ::deleteNode(root);
    }

    void join(PairingHeap other) {
        root = ::merge(root, other.root);
    }

};
#endif //VM_WITH_HEAP_PAIRINGHEAP_H
