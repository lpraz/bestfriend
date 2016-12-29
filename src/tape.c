/*
 * tape.c
 * Provides methods for a Brainfuck tape of ints made using an array.
 */

/* Import self */
#include "tape.h"

/* Local imports */
#include "except.h"

/* Stdlib imports */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Initializes a tape. */
Tape tape_init(int cwidth, bool wrap, int max_fwdsize, int max_revsize) {
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
        cwidth,
        wrap,
        max_fwdsize,
        max_revsize
    };
    
    return tape;
}

/* Seeks the tape's pointer dist cells away from the current position. */
void tape_seek(Tape *tape, int dist) {
    if ((*tape).ptr + dist >= 0
            && ((*tape).max_fwdsize == INFINITE
            || (*tape).ptr + dist < (*tape).max_fwdsize)
        || (*tape).ptr + dist < 0
            && ((*tape).max_revsize == INFINITE
            || (*tape).ptr + dist > -(*tape).max_revsize))
        (*tape).ptr += dist;
    else
        except("Seeked to a cell that is out of bounds");
}

/* Seeks the tape pointer to pos. */
void tape_seeks(Tape *tape, int pos) {
    if ((*tape).max_revsize == INFINITE && pos < 0
            || (*tape).max_fwdsize == INFINITE && pos >= 0
            || pos <= (*tape).max_fwdsize && pos >= (*tape).max_revsize)
        (*tape).ptr = pos;
    else
        except("Seeked to a cell that is out of bounds");
}

/* Transposes the cell at the tape's pointer by val. */
void tape_chg(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        switch ((*tape).cwidth) {
            case INT32_T:
                if ((*tape).wrap
                    || (val >= 0 && ((int32_t*)(*tape).fwd)[(*tape).ptr]
                        <= INT32_MAX - val)
                    || (val < 0 && ((int32_t*)(*tape).fwd)[(*tape).ptr]
                        >= INT32_MIN + val))
                    ((int32_t*)(*tape).fwd)[(*tape).ptr] += val;
                else
                    except("Overflowed a cell");
                break;
            case INT16_T:
                if ((*tape).wrap
                    || (val >= 0 && ((int16_t*)(*tape).fwd)[(*tape).ptr]
                        <= INT16_MAX - val)
                    || (val < 0 && ((int16_t*)(*tape).fwd)[(*tape).ptr]
                        >= INT16_MIN + val))
                    ((int16_t*)(*tape).fwd)[(*tape).ptr] += val;
                else
                    except("Overflowed a cell");
                break;
            case INT8_T:
                if ((*tape).wrap
                    || (val >= 0 && ((int8_t*)(*tape).fwd)[(*tape).ptr]
                        <= INT8_MAX - val)
                    || (val < 0 && ((int8_t*)(*tape).fwd)[(*tape).ptr]
                        >= INT8_MIN + val))
                    ((int8_t*)(*tape).fwd)[(*tape).ptr] += val;
                else
                    except("Overflowed a cell");
                break;
        }
    } else {
        while ((-(*tape).ptr - 1) >= (*tape).revsize)
            tape_revgrow(tape);
        
        switch ((*tape).cwidth) {
            case INT32_T:
                if ((*tape).wrap
                    || (val >= 0 && 
                        ((int32_t*)(*tape).rev)[-(*tape).ptr - 1]
                        <= INT32_MAX - val)
                    || (val < 0 &&
                        ((int32_t*)(*tape).rev)[-(*tape).ptr - 1]
                        >= INT32_MIN + val))
                    ((int32_t*)(*tape).rev)[-(*tape).ptr - 1] += val;
                else
                    except("Overflowed a cell");
                break;
            case INT16_T:
                if ((*tape).wrap
                    || (val >= 0 &&
                        ((int16_t*)(*tape).rev)[-(*tape).ptr - 1]
                        <= INT16_MAX - val)
                    || (val < 0 &&
                        ((int16_t*)(*tape).rev)[-(*tape).ptr - 1]
                        >= INT16_MIN + val))
                    ((int16_t*)(*tape).rev)[-(*tape).ptr - 1] += val;
                else
                    except("Overflowed a cell");
                break;
            case INT8_T:
                if ((*tape).wrap
                    || (val >= 0 &&
                        ((int8_t*)(*tape).fwd)[(*tape).ptr]
                        <= INT8_MAX - val)
                    || (val < 0 &&
                        ((int8_t*)(*tape).fwd)[(*tape).ptr]
                        >= INT8_MIN + val))
                    ((int8_t*)(*tape).rev)[-(*tape).ptr - 1] += val;
                else
                    except("Overflowed a cell");
                break;
        }
    }
}

/* Sets the cell at the tape's pointer to val. */
void tape_set(Tape *tape, int val) {
    if ((*tape).ptr >= 0) {
        while ((*tape).ptr >= (*tape).fwdsize)
            tape_fwdgrow(tape);
        
        switch ((*tape).cwidth) {
            case INT32_T:
                ((int32_t*)(*tape).fwd)[(*tape).ptr] = val;
                break;
            case INT16_T:
                ((int16_t*)(*tape).fwd)[(*tape).ptr] = val;
                break;
            case INT8_T:
                ((int8_t*)(*tape).fwd)[(*tape).ptr] = val;
                break;
        }
    } else {
        while ((-(*tape).ptr - 1) >= (*tape).revsize)
            tape_revgrow(tape);
        
        switch ((*tape).cwidth) {
            case INT32_T:
                ((int32_t*)(*tape).rev)[-(*tape).ptr - 1] = val;
                break;
            case INT16_T:
                ((int16_t*)(*tape).rev)[-(*tape).ptr - 1] = val;
                break;
            case INT8_T:
                ((int8_t*)(*tape).rev)[-(*tape).ptr - 1] = val;
                break;
        }
    }
}

/* Returns the value of the cell at the tape's pointer. */
int tape_get(Tape *tape) {
    if ((*tape).ptr >= 0 && (*tape).ptr < (*tape).fwdsize)
        switch ((*tape).cwidth) {
            case INT32_T:
                return (int)(((int32_t*)(*tape).fwd)[(*tape).ptr]);
                break;
            case INT16_T:
                return (int)(((int16_t*)(*tape).fwd)[(*tape).ptr]);
                break;
            case INT8_T:
                return (int)(((int8_t*)(*tape).fwd)[(*tape).ptr]);
        }
    else if ((*tape).ptr < 0 && (-(*tape).ptr - 1) < (*tape).revsize)
        switch ((*tape).cwidth) {
            case INT32_T:
                return (int)(((int32_t*)(*tape).rev)[-(*tape).ptr - 1]);
                break;
            case INT16_T:
                return (int)(((int16_t*)(*tape).rev)[-(*tape).ptr - 1]);
                break;
            case INT8_T:
                return (int)(((int8_t*)(*tape).rev)[-(*tape).ptr - 1]);
                break;
        }
    
    return 0;
}

/* Grows the right half of the tape (double-growth). */
void tape_fwdgrow(Tape *tape) {
    int new_fwdsize;
    
    if ((*tape).max_fwdsize == INFINITE
            || (*tape).fwdsize * 2 <= (*tape).max_fwdsize)
        new_fwdsize = (*tape).fwdsize * 2;
    else
        new_fwdsize = (*tape).max_fwdsize;
    
    switch((*tape).cwidth) {
        case INT32_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                new_fwdsize * sizeof(int32_t)
            );
            break;
        case INT16_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                new_fwdsize * sizeof(int16_t)
            );
            break;
        case INT8_T:
            (*tape).fwd = realloc(
                (*tape).fwd,
                new_fwdsize * sizeof(int8_t)
            );
            break;
    }
    
    if ((*tape).fwd == NULL)
        error("Unable to get memory when growing forward part of tape");
    
    switch ((*tape).cwidth) {
        case INT32_T:
            for (int i = (*tape).fwdsize; i < new_fwdsize; i++)
                ((int32_t*)((*tape).fwd))[i] = 0;
            break;
        case INT16_T:
            for (int i = (*tape).fwdsize; i < new_fwdsize; i++)
                ((int16_t*)((*tape).fwd))[i] = 0;
            break;
        case INT8_T:
            for (int i = (*tape).fwdsize; i < new_fwdsize; i++)
                ((int8_t*)((*tape).fwd))[i] = 0;
            break;
    }
    
    (*tape).fwdsize = new_fwdsize;
}

/* Grows the left half of the tape (double-growth). */
void tape_revgrow(Tape *tape) {
    int new_revsize;
    
    if ((*tape).max_revsize == INFINITE
            || (*tape).revsize * 2 <= (*tape).max_revsize)
        new_revsize = (*tape).revsize * 2;
    else
        new_revsize = (*tape).revsize * 2;
    
    switch ((*tape).cwidth) {
        case INT32_T:
            (*tape).rev = realloc(
                (*tape).rev,
                new_revsize * sizeof(int32_t)
            );
            break;
        case INT16_T:
            (*tape).rev = realloc(
                (*tape).rev,
                new_revsize * sizeof(int16_t)
            );
            break;
        case INT8_T:
            (*tape).rev = realloc(
                (*tape).rev,
                new_revsize * sizeof(int8_t)
            );
            break;
    }
    
    if ((*tape).rev == NULL)
        error("Unable to get memory when growing reverse part of tape");
    
    switch ((*tape).cwidth) {
        case INT32_T:
            for (int i = (*tape).revsize; i < new_revsize * 2; i++)
                ((int32_t*)((*tape).rev))[i] = 0;
            break;
        case INT16_T:
            for (int i = (*tape).revsize; i < new_revsize * 2; i++)
                ((int16_t*)((*tape).rev))[i] = 0;
            break;
        case INT8_T:
            for (int i = (*tape).revsize; i < new_revsize * 2; i++)
                ((int8_t*)((*tape).rev))[i] = 0;
            break;
    }
    
    (*tape).revsize = new_revsize;
}

/* Frees the memory used by a tape. */
void tape_free(Tape *tape) {
    free((*tape).fwd);
    free((*tape).rev);
}
