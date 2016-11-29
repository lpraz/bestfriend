/*
 * dltape.h
 * Defines structure and abstract functions for a Brainfuck memory
 * tape based on a doubly-linked list. Only recommended to use when
 * negative memory addresses exist, as a vector can be used otherwise.
 */

#ifndef DLTAPE_H
#define DLTAPE_H

/* Constants */
#define INFINITE -1

typedef struct DLTape {
    /* Not sure if these are required yet:
    DLNode *head;
    DLNode *tail;
    */
    DLNode *ptr;
    int size;
}

/* Initializes a DLTape with no elements. */
DLTape dltape_init(int size);

/* Seeks the tape's pointer dist cells to the left. */
void dltape_seekleft(DLTape *tape, int dist);

/* Seeks the tape's pointer dist cells to the right. */
void dltape_seekright(DLTape *tape, int dist);

/* Incrememts the value in the cell under the tape's pointer by val. */
void dltape_inc(DLTape *tape, int val);

/* Decrements the value in the cell under the tape's pointer by val. */
void dltape_dec(DLTape *tape, int val);

/* Sets the value in the cell under the tape's pointer to val. */
void dltape_set(DLTape *tape, int val);

/* Returns the int found at the tape's pointer. */
int dltape_getatptr(DLTape *tape);

/* Frees the memory used by a DLTape. */
void dltape_free(DLTape *tape);

#endif
