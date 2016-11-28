/*
 * dlnode.h
 * Defines structure and abstract functions for a node in a doubly
 * linked list.
 */

#ifndef DLNODE_H
#define DLNODE_H

typedef struct DLNode {
    DLNode *last;
    int value;
    DLNode *next;
} DLNode;

/* Initializes a doubly linked list node. */
DLNode dlnode_init(DLNode *last, int value, DLNode *next);

#endif
