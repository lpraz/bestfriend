/*
 * stack.h
 * Defines abstract functions and the structure for a stack of Loops.
 */

#ifndef STACK_H
#define STACK_H

/* Local imports */
#include "loop.h"

/* Stdlib imports */
#include <stdbool.h>

/* Structure */
typedef struct Loop_ Loop;

typedef struct Stack_ Stack;
struct Stack_ {
    Loop *items;
    int size;
    int top;
};

/* Constants */
#define DEFAULT_STACK_SIZE 2

/* Initializes a stack of size size with nothing in it. */
Stack stk_init(int size);

/* Puts an element on top of the stack. */
void stk_push(Stack *stk, Loop el);

/* Returns/removes the topmost element of the stack. */
Loop stk_pop(Stack *stk);

/* Returns (without removing) the topmost element of the stack. */
Loop stk_top(Stack *stk);

/* Returns the size of the stack. */
int stk_size(Stack *stk);

/* Returns whether the stack is empty or not. */
bool stk_isempty(Stack *stk);

/* Expands the stack to twice its size (double-growth). */
void stk_expand(Stack *stk);

/* Frees up the memory occupied by a stack. */
void stk_free(Stack *stk);

#endif
