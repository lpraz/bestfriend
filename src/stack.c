/*
 * stack.c
 * Provides functions for a stack of Loops.
 */

/* Import self */
#include "stack.h"

/* Local imports */
#include "except.h"
#include "loop.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Initializes a stack of size size with nothing in it. */
Stack stk_init(int size) {
    Loop *new_items = malloc(size * sizeof(Loop));
    
    if (new_items == NULL)
        error("Unable to get memory while initializing stack");
    
    Stack stk = {new_items, size, 0};
    return stk;
}

/* Puts an element on top of the stack. */
void stk_push(Stack *stk, Loop el) {
    (*stk).items[(*stk).top++] = el;
}

/* Returns/removes the topmost element of the stack. */
Loop stk_pop(Stack *stk) {
    if (stk_isempty(stk))
        error("Tried to pop from an empty stack");
    
    return (*stk).items[--(*stk).top];
}

/* Returns (without removing) the topmost element of the stack. */
Loop stk_top(Stack *stk) {
    if (stk_isempty(stk))
        error("Tried to get top element of empty stack");
    
    return (*stk).items[(*stk).top - 1];
}

/* Returns the size of the stack. */
int stk_size(Stack *stk) {
    return (*stk).top;
}

/* Returns whether the stack is empty or not. */
bool stk_isempty(Stack *stk) {
    return (*stk).top == 0;
}

/* Expands the stack to twice its size (double-growth). */
void stk_expand(Stack *stk) {
    Loop *new_items = malloc((*stk).size * 2 * sizeof(Loop));
    
    if (new_items == NULL)
        error("Unable to get memory when expanding stack");
        
    for (int i = 0; i < (*stk).size; i++)
        new_items[i] = (*stk).items[i];
    
    free((*stk).items);
    (*stk).items = new_items;
}

/* Frees the memory used by a stack. */
void stk_free(Stack *stk) {
    while (!stk_isempty(stk))
        stk_pop(stk);
    
    free((*stk).items);
}
