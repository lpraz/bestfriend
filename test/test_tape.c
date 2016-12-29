/*
 * test_tape.c
 * Tests tape.c.
 */

/* Import test subject */
#include "tape.h"

/* Import test framework */
#include "cutest.h"

/* Stdlib imports */
#include <stdbool.h>

/* Tests tape_init */
void test_tape_init() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    
    TEST_CHECK(tape.ptr == 0);
    TEST_CHECK(tape.cwidth == INT8_T);
    TEST_CHECK(tape.wrap == true);
    TEST_CHECK(tape.max_fwdsize == INFINITE);
    TEST_CHECK(tape.max_revsize == INFINITE);
    
    tape_free(&tape);
}

/* Tests tape_seek. */
void test_tape_seek() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape.ptr == 0);
    
    tape_seek(&tape, 5);
    TEST_CHECK(tape.ptr == 5);
    
    tape_seek(&tape, -2);
    TEST_CHECK(tape.ptr == 3);
    
    tape_seek(&tape, 0);
    TEST_CHECK(tape.ptr == 3)
    ;
    tape_free(&tape);
}

/* Tests tape_chg. */
void test_tape_chg() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape_get(&tape) == 0);
    
    tape_chg(&tape, 5);
    TEST_CHECK(tape_get(&tape) == 5);
    
    tape_chg(&tape, -2);
    TEST_CHECK(tape_get(&tape) == 3);
    
    tape_chg(&tape, 0);
    TEST_CHECK(tape_get(&tape) == 3);
    
    tape_free(&tape);
}

/* Tests tape_set. */
void test_tape_set_get() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape_get(&tape) == 0);
    
    tape_set(&tape, 3);
    TEST_CHECK(tape_get(&tape) == 3);
    
    tape_set(&tape, -3);
    TEST_CHECK(tape_get(&tape) == -3);
    
    tape_free(&tape);
}

TEST_LIST = {
    {"tape_init", test_tape_init},
    {"tape_seek", test_tape_seek},
    {"tape_chg", test_tape_chg},
    {"tape_set/tape_get", test_tape_set_get},
    {0}
};
