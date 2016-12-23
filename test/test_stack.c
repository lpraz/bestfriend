/*
 * test_stack.c
 * Tests stack.c.
 */

/* Import test subject */
#include "stack.h"

/* Import test framework */
#include "cutest.h"

/* Tests stk_init. */
void test_stk_init(void) {
    Stack stk = stk_init(5);
    int equals = 1;
    
    if (stk.size != 5 || stk.top != 0)
        equals = 0;
    
    TEST_CHECK(equals);
    
    stk_free(&stk);
}

/* Tests stk_isempty. */
void test_stk_isempty(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    Loop example = {5, false};
    
    /* Is empty? Should be true */
    TEST_CHECK(stk_isempty(&stk));
    
    /* Is empty? Should be false */
    stk_push(&stk, example);
    TEST_CHECK(!stk_isempty(&stk));
    
    stk_free(&stk);
}

/* Tests stk_size. */
void test_stk_size(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    Loop example = {5, false};
    
    /* Size should be 0 */
    TEST_CHECK(stk_size(&stk) == 0);
    
    for (int i = 0; i < 5; i++)
        stk_push(&stk, example);
    
    TEST_CHECK(stk_size(&stk) == 5);
    
    stk_free(&stk);
}

/* Tests stk_free. */
void test_stk_free(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    Loop example = {5, false};
    
    stk_free(&stk);
    TEST_CHECK(stk.items != NULL);
    
    stk = stk_init(DEFAULT_STACK_SIZE);
    stk_push(&stk, example);
    stk_free(&stk);
    TEST_CHECK(stk.items != NULL);
}

TEST_LIST = {
    {"stk_init", test_stk_init},
    {"stk_isempty", test_stk_isempty},
    {"stk_size", test_stk_size},
    {"stk_free", test_stk_free},
    {0}
};
