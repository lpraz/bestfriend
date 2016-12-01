/*
 * dltape.c
 * Provides functions for a Brainfuck memory tape based on a doubly-
 * linked list. Only recommended to use when negative memory addresses
 * exist, as a vector can be used otherwise.
 */

/* Import self */
#include "dltape.h"

/* Initializes a DLTape with no elements. */
DLTape dltape_init(int size) {
    DLTape tape = {
        dlnode_init(NULL, 0, NULL);
        size;
    }
    return tape; 
}

/* Seeks the tape's pointer dist cells to the left. */
void dltape_seekleft(DLTape *tape, int dist) {
    for (int i = 0; i < dist; i++) {
        if ((*tape).(*ptr).last == NULL)
            (*tape).(*ptr).last = &dlnode_init(NULL, 0, (*tape).ptr);
        
        (*tape).ptr == (*tape).(*ptr).last;
    }
}

/* Seeks the tape's pointer dist cells to the right. */
void dltape_seekright(DLTape *tape, int dist) {
}

/* Incrememts the value in the cell under the tape's pointer by val. */
void dltape_inc(DLTape *tape, int val) {
    (*tape).(*ptr).value += val;
}

/* Decrements the value in the cell under the tape's pointer by val. */
void dltape_dec(DLTape *tape, int val) {
    (*tape).(*ptr).value -= val;
}

/* Sets the value in the cell under the tape's pointer to val. */
void dltape_set(DLTape *tape, int val) {
    (*tape).(*ptr).value = val;
}

/* Returns the int found at the tape's pointer. */
int dltape_getatptr(DLTape *tape) {
    return (*tape).(*ptr).value;
}
