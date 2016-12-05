/*
 * loop.c
 * Provides functions for dealing with Brainfuck loop constructs.
 */

/* Import self */
#include "loop.h"

/* Local imports */
#include "stack.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Used at start of loop, returns whether loop should be skipped. */
bool loop_start(Stack *stk, int cell, int pos) {
    if (cell != 0) {
        stk_push(stk, pos);
        return false;
    }
    
    return true;
}

/* Used at end of loop, returns whether loop should be repeated. */
bool loop_end(Stack *stk, int cell) {
    if (!stk_isempty(stk)) {
        if (cell = 0) {
            stk_pop(stk);
            return true;
        }
    } else {
        printf("Exception: ']' without matching '['!\n");
        exit(EXIT_FAILURE);
    }
    
    return false;
}