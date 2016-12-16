/*
 * loop.c
 * Provides functions for dealing with Brainfuck loop constructs.
 */

/* Import self */
#include "loop.h"

/* Local imports */
#include "except.h"
#include "stack.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Starts a loop. */
void loop_start(Stack *stk, int cell, int pos) {
    Loop loop = {pos, false};
    
    if (cell == 0) 
        loop.skip = true;
    
    stk_push(stk, loop);
}

/* Used at end of loop, returns whether loop should be repeated. */
bool loop_end(Stack *stk, int cell) {
    if (cell == 0) {
        if (!stk_isempty(stk))
            stk_pop(stk);
        else
            except("']' without matching '['");
        
        return false;
    }
    
    return true;
}
