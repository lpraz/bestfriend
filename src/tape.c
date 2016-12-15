/*
 * tape.c
 * Provides methods for a Brainfuck tape of ints made using an array.
 * TODO: Fix the remaining void pointer problems
 */

/* Import self */
#include "tape.h"

/* Stdlib imports */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* Initializes a tape. */
Tape tape_init(int cwidth) {
    void *fwd, *rev;
    
    switch (cwidth) {
        case INT32_T:
            fwd = (int32_t*)calloc(DEFAULT_FWDSIZE, sizeof(int32_t));
            rev = (int32_t*)calloc(DEFAULT_REVSIZE, sizeof(int32_t));
            break;
        case INT16_T:
            fwd = (int16_t*)calloc(DEFAULT_FWDSIZE, sizeof(int16_t));
            rev = (int16_t*)calloc(DEFAULT_REVSIZE, sizeof(int16_t));
            break;
        case INT8_T:
            fwd = (int8_t*)calloc(DEFAULT_FWDSIZE, sizeof(int8_t));
            rev = (int8_t*)calloc(DEFAULT_REVSIZE, sizeof(int8_t));
            break;
    }
    
    Tape tape = {
        0,
        fwd,
        rev,
        DEFAULT_FWDSIZE,
        DEFAULT_REVSIZE,
        cwidth
    };
    
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
        
        switch ((*tape).cwidth) {
            case INT32_T:
                (*tape).fwd[(*tape).ptr] += val;
                break;
            case INT16_T:
                (*tape).fwd[(*tape).ptr] += val;
                break;
            case INT8_T:
                (*tape).fwd[(*tape).ptr] += val;
                break;
        }
    } else {
        while ((-(*tape).ptr - 1) >= (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[-(*tape).ptr - 1] += val;
    }
}

/* Decrements the cell at the tape's pointer by val. */
void tape_dec(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        switch ((*tape).cwidth) {
            case INT32_T:
                (*tape).fwd[(*tape).ptr] -= val;
                break;
            case INT16_T:
                (*tape).fwd[(*tape).ptr] -= val;
                break;
            case INT8_T:
                (*tape).fwd[(*tape).ptr] -= val;
                break;
        }
    } else {
        while ((-(*tape).ptr - 1) >= (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[-(*tape).ptr - 1] -= val;
    }
}

/* Sets the cell at the tape's pointer to val. */
void tape_set(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        (*tape).fwd[(*tape).ptr] = val;    
    } else {
        while ((-(*tape).ptr - 1) >= (*tape).revsize)
            tape_revgrow(tape);
        
        (*tape).rev[-(*tape).ptr - 1] = val;
    }
}

/* Returns the value of the cell at the tape's pointer. */
int tape_get(Tape *tape) {
    if ((*tape).ptr >= 0 && (*tape).ptr < (*tape).fwdsize)
        return (*tape).fwd[(*tape).ptr];
    else if ((*tape).ptr < 0 && (-(*tape).ptr - 1) < (*tape).revsize)
        return (*tape).rev[-(*tape).ptr - 1];
    
    return 0;
}

/* Grows the right half of the tape (double-growth). */
void tape_fwdgrow(Tape *tape) {
    switch((*tape).cwidth) {
        case INT32_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                2 * (*tape).fwdsize * sizeof(int32_t)
            );
            break;
        case INT16_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                2 * (*tape).fwdsize * sizeof(int16_t)
            );
            break;
        case INT8_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                2 * (*tape).fwdsize * sizeof(int8_t)
            );
            break;
    }
    
    if ((*tape).fwd == NULL) {
        printf("Error getting memory in tape_fwdgrow!\n");
        exit(EXIT_FAILURE);
    }
    
    switch ((*tape).cwidth) {
        case INT32_T:
            for (int i = (*tape).fwdsize; i < (*tape).fwdsize * 2; i++)
                ((int32_t*)((*tape).fwd))[i] = 0;
            break;
        case INT16_T:
            for (int i = (*tape).fwdsize; i < (*tape).fwdsize * 2; i++)
                ((int16_t*)((*tape).fwd))[i] = 0;
            break;
        case INT8_T:
            for (int i = (*tape).fwdsize; i < (*tape).fwdsize * 2; i++)
                ((int8_t*)((*tape).fwd))[i] = 0;
            break;
    }
    
    (*tape).fwdsize *= 2;
}

/* Grows the left half of the tape (double-growth). */
void tape_revgrow(Tape *tape) {
    switch ((*tape).cwidth) {
        case INT32_T:
            (*tape).rev = realloc(
                (*tape).rev,
                2 * (*tape).revsize * sizeof(int32_t)
            );
            break;
        case INT16_T:
            (*tape).rev = realloc(
                (*tape).rev,
                2 * (*tape).revsize * sizeof(int16_t)
            );
            break;
        case INT8_T:
            (*tape).rev = realloc(
                (*tape).rev,
                2 * (*tape).revsize * sizeof(int8_t)
            );
            break;
    }
    
    if ((*tape).rev == NULL) {
        printf("Error getting memory in tape_revgrow!\n");
        exit(EXIT_FAILURE);
    }
    
    switch ((*tape).cwidth) {
        case INT32_T:
            for (int i = (*tape).revsize; i < (*tape).revsize * 2; i++)
                ((int32_t*)((*tape).rev))[i] = 0;
            break;
        case INT16_T:
            for (int i = (*tape).revsize; i < (*tape).revsize * 2; i++)
                ((int16_t*)((*tape).rev))[i] = 0;
            break;
        case INT8_T:
            for (int i = (*tape).revsize; i < (*tape).revsize * 2; i++)
                ((int8_t*)((*tape).rev))[i] = 0;
            break;
    }
    
    (*tape).revsize *= 2;
}

/* Frees the memory used by a tape. */
void tape_free(Tape *tape) {
    free((*tape).fwd);
    free((*tape).rev);
}
