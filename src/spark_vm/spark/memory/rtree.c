//
// Created by Kirill Zhukov on 17.03.2023.
//
#include "rtree.h"

bool isLeaf(struct RTreeNode *node) {
    return (node->m_level == 0);
} // A leaf, contains data

struct Chunk *RTreeSearch(struct RTreeNode *node, struct RTreeRect rect) {
    if (isLeaf(node)) {
        // If the node is a leaf, check each data item for intersection with the search rectangle
        for (int i = 0; i < node->m_count; i++) {
            if (node->m_branch[i].m_rect.min_x <= rect.max_x &&
                node->m_branch[i].m_rect.max_x >= rect.min_x &&
                node->m_branch[i].m_rect.min_y <= rect.max_y &&
                node->m_branch[i].m_rect.max_y >= rect.min_y) {
                return &node->m_branch[i].data;
            }
        }
    } else {
        // If the node is not a leaf, check each child node for intersection with the search rectangle
        for (int i = 0; i < node->m_count; i++) {
            if (node->m_branch[i].m_rect.min_x <= rect.max_x &&
                node->m_branch[i].m_rect.max_x >= rect.min_x &&
                node->m_branch[i].m_rect.min_y <= rect.max_y &&
                node->m_branch[i].m_rect.max_y >= rect.min_y) {
                struct Chunk *result = RTreeSearch(node->m_branch[i].children[0], rect);
                if (result) {
                    return result;
                }
            }
        }
    }
    // No match found
    return NULL;
}

struct RTreeRect RTreeNodeCoverRect(struct RTreeNode *node) {
    struct RTreeRect rect = node->m_branch[0].m_rect;
    for (int i = 1; i < node->m_count; i++) {
        rect.min_x = MIN(rect.min_x, node->m_branch[i].m_rect.min_x);
        rect.max_x = MAX(rect.max_x, node->m_branch[i].m_rect.max_x);
        rect.min_y = MIN(rect.min_y, node->m_branch[i].m_rect.min_y);
        rect.max_y = MAX(rect.max_y, node->m_branch[i].m_rect.max_y);
    }
    return rect;
}

struct RTreeNode *allocate_rtree_node() {
    if (node_buffer_index < MAX_NODES) {
        return &node_buffer[++node_buffer_index];
    } else {
        return NULL; // No more space available in the buffer
    }
}