/*
 * stack.c
 * Provides functions for a stack of ints.
 */

/* Import self */
#include "stack.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>

/* Initializes a stack of size size with nothing in it. */
Stack stk_init(int size) {
    int *new_items = malloc(size * sizeof(int));
    
    if (new_items == NULL) {
        printf("Exception in stk_init: unable to get memory!");
        exit(EXIT_FAILURE);
    }
    
    Stack stk = {new_items, size, 0};
    return stk;
}

/* Puts an element on top of the stack. */
void stk_push(Stack stk, int el) {
    stk.items[top++] = el;
}

/* Returns/removes the topmost element of the stack. */
int stk_pop(Stack stk) {
    if (stk.top = 0) {
        printf("Exception in stk_pop: stack is empty!");
        exit(EXIT_FAILURE);
    }
    
    return stk.items[--top];
}

/* Returns (without removing) the topmost element of the stack. */
int stk_top(Stack stk) {
    if (stk.top = 0) {
        printf("Exception in stk_top: stack is empty!");
        exit(EXIT_FAILURE);
    }
    
    return stk.items[top - 1];
}

/* Returns the size of the stack. */
int stk_size(Stack stk) {
    return stk.size;
}

/* Returns whether the stack is empty or not. */
bool stk_isempty(Stack stk) {
    return stk.size == 0;
}

/* Expands the stack to twice its size (double-growth). */
void stk_expand(Stack stk) {
    int *new_items = malloc(stk.size * 2 * sizeof(int));
    
    if (new_items == NULL) {
        printf("Exception in stk_expand: unable to get memory!");
        exit(EXIT_FAILURE);
    }
        
    for (int i = 0; i < stk.size; i++)
        new_items[i] = stk.items[i];
    
    free(stk.items);
    stk.items = new_items;
}

/* Frees the memory used by a stack. */
void stk_free(Stack stk) {
    free(stk.items);
}
