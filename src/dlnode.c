/*
 * dlnode.c
 * Provides functions for a node in a doubly linked list.
 */

/* Import self */
#include "dlnode.h"

/* Initializes a doubly linked list node. */
DLNode dlnode_init(DLNode *last, int value, DLNode *next) {
    DLNode node = {last, value, next};
    return node;
}
