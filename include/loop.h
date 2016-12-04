/*
 * loop.h
 * Defines structure of, and abstract functions for, dealing with
 * Brainfuck loop constructs.
 */

#ifndef LOOP_H
#define LOOP_H

/* Local imports */
#include "stack.h"

/* Stdlib imports */
#include <stdbool.h>

/* Used at start of loop, returns whether loop should be skipped. */
bool loop_start(Stack *stk, int cell, int pos);

/* Used at end of loop, returns whether loop should be repeated. */
bool loop_end(Stack *stk, int cell);

#endif
