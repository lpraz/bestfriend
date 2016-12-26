/*
 * test_loop.c
 * Tests loop.c.
 */

/* Import test subject */
#include "loop.h"

/* Import test framework */
#include "cutest.h"

/* Tests loop_start. */
void test_loop_start(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    Loop loop;
    
    loop_start(&stk, 0, 5);
    loop = stk_pop(&stk);
    TEST_CHECK(loop.skip == true);
    TEST_CHECK(loop.start == 5);
    
    loop_start(&stk, 4, 8);
    loop = stk_pop(&stk);
    TEST_CHECK(loop.skip == false);
    TEST_CHECK(loop.start == 8);
}

/* Tests loop_end. */
void test_loop_end(void) {
    Stack stk = stk_init(DEFAULT_STACK_SIZE);
    
    loop_start(&stk, 1, 5);
    TEST_CHECK(loop_end(&stk, 1) == true);
    TEST_CHECK(loop_end(&stk, 0) == false);
}

TEST_LIST = {
    {"loop_start", test_loop_start},
    {"loop_end", test_loop_end},
    {0}
};
