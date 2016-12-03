/*
 * tape.h
 * Defines structure and abstract methods for a Brainfuck tape of ints
 * made using an array.
 */

#ifndef TAPE_H
#define TAPE_H

/* Constants */
#define DEFAULT_FORWARD_SIZE 2
#define DEFAULT_REVERSE_SIZE 1

/* Structure */
typedef struct Tape {
    int ptr;
    int *fwd;
    int *rev;
    int fwdsize;
    int revsize;
} Tape;

/* Initializes a tape. */
Tape tape_init();

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
