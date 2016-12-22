/*
 * test_stack.c
 * Tests stack.c.
 */

/* Import test subject */
#include "stack.h"

/* Import test framework */
#include "cutest.h"

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

void test_stk_size(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    Loop example = {5, false};
    
    /* Size should be 0 */
    TEST_CHECK(stk_size(&stk) == 0);
    
    for (int i = 1; i <= 5; i++) {
        stk_push(&stk, example);
        TEST_CHECK(stk_size(&stk) == i);
    }
    
}

TEST_LIST = {
    {"stk_isempty", test_stk_isempty},
    {"stk_size", test_stk_size},
    {0}
};
