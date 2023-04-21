#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MAXNODES 4 // MINNODES <= MAXNODES / 2
#define MINNODES 2
#define DIMENSIONS 2 // can be 3

struct RTreeRect {
    int min_x, min_y, max_x, max_y;
};

struct Chunk {
    size_t size;
    uint32_t freeSize;
    // run_t *run_list;
    struct Chunk *parent;
    struct Chunk *child;
    struct Chunk *sibling;
};

struct Branch {
    struct RTreeRect m_rect; ///< Bounds
    union {
        struct RTreeNode *children[MAXNODES]; ///< Child node
        struct Chunk data;                    ///< Data Id or Ptr
    };
};

struct RTreeNode {
    uint64_t m_count;                 ///< Count
    uint64_t m_level;                 ///< Leaf is zero, others positive
    struct Branch m_branch[MAXNODES]; ///< Branch
    struct RTreeNode *parent;
};

extern bool isLeaf(struct RTreeNode *node);
// Searches the R-tree for a given rectangle, starting at the given node
extern struct Chunk *RTreeSearch(struct RTreeNode *node, struct RTreeRect rect);

// Returns the bounding rectangle that covers all child rectangles of a given node
extern struct RTreeRect RTreeNodeCoverRect(struct RTreeNode *node);

#define MAX_NODES 100
static struct RTreeNode node_buffer[0xFF];
static int node_buffer_index = 0;

extern struct RTreeNode *allocate_rtree_node();

// Inserts a new rectangle into the R-tree
void RTreeInsertRect(struct RTreeRect rect, struct Chunk data, struct RTreeNode **root) {
    if (*root == NULL) {
        // If the root is null, create a new leaf node and make it the root
        *root = allocate_rtree_node();
        (*root)->m_count = 0;
        (*root)->m_level = 0;
        (*root)->parent = NULL;
        (*root)->m_branch[0].m_rect = rect;
        (*root)->m_branch[0].data = data;
        (*root)->m_count++;
    } else {
        struct RTreeNode *node = (*root);
        struct RTreeNode *parent = NULL;
        struct Branch branch;
        int child;
        // Traverse the R-tree to find the best node for the new rectangle
        while (!isLeaf(node)) {
            // Choose the child node that requires the least overlap expansion to add the new rectangle to
            int least_overlap_expansion = INT_MAX;
            struct RTreeRect expanded_rect;
            for (int i = 0; i < node->m_count; i++) {
                int overlap_expansion = 0;
                expanded_rect.min_x = MIN(rect.min_x, node->m_branch[i].m_rect.min_x);
                expanded_rect.max_x = MAX(rect.max_x, node->m_branch[i].m_rect.max_x);
                expanded_rect.min_y = MIN(rect.min_y, node->m_branch[i].m_rect.min_y);
                expanded_rect.max_y = MAX(rect.max_y, node->m_branch[i].m_rect.max_y);
                overlap_expansion += (expanded_rect.max_x - expanded_rect.min_x) -
                                     (node->m_branch[i].m_rect.max_x - node->m_branch[i].m_rect.min_x);
                overlap_expansion += (expanded_rect.max_y - expanded_rect.min_y) -
                                     (node->m_branch[i].m_rect.max_y - node->m_branch[i].m_rect.min_y);
                if (overlap_expansion < least_overlap_expansion) {
                    least_overlap_expansion = overlap_expansion;
                    branch = node->m_branch[i];
                    child = i;
                }
            }
            parent = node;
            node = node->m_branch[child].children[0];
        }
        // If the leaf node is not full, add the new rectangle to it
        if (node->m_count < MAXNODES) {
            node->m_branch[node->m_count].m_rect = rect;
            node->m_branch[node->m_count].data = data;
            node->m_count++;
        } else {
            // If the leaf node is full, split it into two new leaf nodes
            struct RTreeNode *new_node = NULL;
            new_node = allocate_rtree_node();
            new_node->m_count = 0;
            new_node->m_level = 0;
            new_node->parent = parent;
            int split_point = MAXNODES / 2;
            for (int i = split_point; i < MAXNODES; i++) {
                new_node->m_branch[new_node->m_count] = node->m_branch[i];
                new_node->m_count++;
            }
            node->m_count = split_point;
            // Add the new rectangle to the appropriate leaf node
            if (child >= split_point) {
                new_node->m_branch[new_node->m_count].m_rect = rect;
                new_node->m_branch[new_node->m_count].data = data;
                new_node->m_count++;
            } else {
                node->m_branch[node->m_count].m_rect = rect;
                node->m_branch[node->m_count].data = data;
                node->m_count++;
            }
            // Update the parent node
            if (parent != NULL) {
                int i;
                for (i = 0; i < parent->m_count; i++) {
                    if (parent->m_branch[i].children[0] == node) {
                        break;
                    }
                }
                parent->m_branch[i].children[0] = node;
                parent->m_branch[i].children[1] = new_node;
                if (parent->m_count < MAXNODES) {
                    parent->m_count++;
                } else {
                    RTreeInsertRect(branch.m_rect, branch.data, &parent);
                }
            } else {
                // If the root was split, create a new root
                struct RTreeNode *new_root = NULL;
                new_node = allocate_rtree_node();
                new_root->m_count = 1;
                new_root->m_level = node->m_level + 1;
                new_root->parent = NULL;
                new_root->m_branch[0].children[0] = node;
                new_root->m_branch[0].children[1] = new_node;
                new_root->m_branch[0].m_rect = RTreeNodeCoverRect(node);
                new_root->m_branch[1].m_rect = RTreeNodeCoverRect(new_node);
                (*root) = new_root;
            }
        }
    }
}

#ifdef __cplusplus
}
#endif
