/*
 * tape.c
 * Provides methods for a Brainfuck tape of ints made using an array.
 */

/* Import self */
#include "tape.h"

/* Initializes a tape. */
Tape tape_init() {
    int *fwd = (int*)calloc(DEFAULT_FORWARD_SIZE, sizeof(int));
    int *rev = (int*)calloc(DEFAULT_REVERSE_SIZE, sizeof(int));
    Tape tape = {0, fwd, rev, DEFAULT_FORWARD_SIZE, DEFAULT_REVERSE_SIZE};
    return tape;
}

/* Seeks the tape's pointer dist cells to the left. */
void tape_seekl(Tape *tape, int dist) {
    (*tape).ptr -= dist;
}

/* Seeks the tape's pointer dist cells to the right. */
void tape_seekr(Tape *tape, int dist) {
    (*tape).ptr += dist;
}

/* Seeks the tape pointer to pos. */
void tape_seeks(Tape *tape, int pos) {
    (*tape).ptr = pos;
}

/* Increments the cell at the tape's pointer by val. */
void tape_inc(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        (*tape).fwd[(*tape).ptr] += val;
    } else {
        while (1 - (*tape).ptr < (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[1 - (*tape).ptr] += val;
    }
}

/* Decrements the cell at the tape's pointer by val. */
void tape_dec(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        (*tape).fwd[(*tape).ptr] -= val;
    } else {
        while (1 - (*tape).ptr < (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[1 - (*tape).ptr] += val;
    }
}

/* Sets the cell at the tape's pointer to val. */
void tape_set(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        (*tape).fwd[(*tape).ptr] = val;    
    } else {
        while (1 - (*tape).ptr < (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[1 - (*tape).ptr] = val;
    }
}

/* Returns the value of the cell at the tape's pointer. */
int tape_get(Tape *tape) {
    realloc((*tape).fwd, 2 * (*tape).fwdsize * sizeof(int));
    for (int i = (*tape).fwdsize; i < (*tape).fwdsize * 2; i++)
        (*tape).fwd[i] = 0;
    (*tape).fwdsize *= 2;
}

/* Grows the right half of the tape (double-growth). */
void tape_fwdgrow(Tape *tape) {
    realloc((*tape).rev, 2 * (*tape).revsize * sizeof(int));
    for (int i = (*tape).revsize; i < (*tape).revsize * 2; i++)
        (*tape).rev[i] = 0;
    (*tape).revsize *= 2;
}

/* Grows the left half of the tape (double-growth). */
void tape_revgrow(Tape *tape) {
    int *newrev = malloc(2 * (*tape).revsize * sizeof(int));
    for (int i = 0; i < (*tape).revsize; i++)
        newrev[i]
}

/* Frees the memory used by a tape. */
void tape_free(Tape *tape) {
    free(tape.fwd);
    free(tape.rev);
}
