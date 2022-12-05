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
bool Empty(HeapNode *node) {
    return (node == nullptr);
}

// Function to merge two heaps
HeapNode *Merge(HeapNode *A, HeapNode *B)
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
HeapNode *Insert(HeapNode *node, int key) {
    return Merge(node, new HeapNode(key, nullptr, nullptr));
}

// This method is used when we want to delete root node
HeapNode *TwoPassMerge(HeapNode *node) {
    if(node == nullptr || node->nextSibling == nullptr)
        return node;
    else {
        HeapNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = nullptr;
        B->nextSibling = nullptr;

        return Merge(Merge(A, B), TwoPassMerge(newNode));
    }

    return nullptr; // Unreachable
}

// Function to delete the root node in heap
HeapNode *Delete(HeapNode *node) {
    return TwoPassMerge(node->leftChild);
}

struct PairingHeap {
    HeapNode *root;

    PairingHeap():
            root(nullptr) {}

    bool Empty(void) {
        return ::Empty(root);
    }

    int Top(void) {
        return ::Top(root);
    }

    void Insert(int key) {
        root = ::Insert(root, key);
    }

    void Delete(void) {
        root = ::Delete(root);
    }

    void Join(PairingHeap other) {
        root = ::Merge(root, other.root);
    }

};
#endif //VM_WITH_HEAP_PAIRINGHEAP_H
