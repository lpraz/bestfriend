/*
 * loop.h
 * Defines structure of, and abstract functions for, Brainfuck loop
 * constructs.
 */

#ifndef LOOP_H
#define LOOP_H

/* Local imports */
#include "stack.h"

/* Stdlib imports */
#include <stdbool.h>

/* Structure */
typedef struct Stack_ Stack;

typedef struct Loop_ Loop;
struct Loop_ {
    int start;
    bool skip;
};

/* Starts a loop. */
void loop_start(Stack *stk, int cell, int pos);

/* Used at end of loop, returns whether loop should be repeated. */
bool loop_end(Stack *stk, int cell);

#endif
