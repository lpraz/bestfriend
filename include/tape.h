/*
 * tape.h
 * Defines structure and abstract methods for a Brainfuck tape of ints
 * made using an array.
 */

#ifndef TAPE_H
#define TAPE_H

/* Stdlib imports */
#include <stdbool.h>

/* Constants - default tape size */
#define DEFAULT_FWDSIZE 2
#define DEFAULT_REVSIZE 1

/* Constants - cell width flags */
#define INT32_T 1
#define INT16_T 2
#define INT8_T 3

/* Constants - predefined tape bounds */
#define INFINITE -1

/* Structure */
typedef struct Tape {
    int ptr;
    void *fwd;
    void *rev;
    int fwdsize;
    int revsize;
    int cwidth;
    bool wrap;
    int max_fwdsize;
    int max_revsize;
} Tape;

/* Initializes a tape. */
Tape tape_init(int cwidth, bool wrap, int max_fwdsize, int max_revsize);

/* Seeks the tape's pointer dist cells to the left. */
void tape_seekl(Tape *tape, int dist);

/* Seeks the tape's pointer dist cells to the right. */
void tape_seekr(Tape *tape, int dist);

/* Seeks the tape pointer to pos. */
void tape_seeks(Tape *tape, int pos);

/* Increments the cell at the tape's pointer by val. */
void tape_inc(Tape *tape, int val);

/* Decrements the cell at the tape's pointer by val. */
void tape_dec(Tape *tape, int val);

/* Sets the cell at the tape's pointer to val. */
void tape_set(Tape *tape, int val);

/* Returns the value of the cell at the tape's pointer. */
int tape_get(Tape *tape);

/* Grows the right half of the tape (double-growth). */
void tape_fwdgrow(Tape *tape);

/* Grows the left half of the tape (double-growth). */
void tape_revgrow(Tape *tape);

/* Frees the memory used by a tape. */
void tape_free(Tape *tape);

#endif
