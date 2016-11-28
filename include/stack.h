/*
 * stack.h
 * Defines abstract functions and the structure for a stack of ints.
 */

#ifndef STACK_H
#define STACK_H

/* Stdlib imports */
#include <stdbool.h>

typedef struct stack {
    int *items;
    int top;
} stack;

/* Initializes a stack of size size with nothing in it. */
stack stk_init(int size);

/* Puts an element on top of the stack. */
void stk_push(stack stk, int el);

/* Returns/removes the topmost element of the stack. */
int stk_pop(stack stk);

/* Returns (without removing) the topmost element of the stack. */
int stk_top(stack stk);

/* Returns the size of the stack. */
int stk_size(stack stk);

/* Returns whether the stack is empty or not. */
bool stk_isempty(stack stk);

/* Expands the stack to twice its size (double-growth). */
void stk_expand(stack stk);

#endif
