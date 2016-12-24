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

/* Tests tape_seekl. */
void test_tape_seekl() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape.ptr == 0);
    
    tape_seekl(&tape, 5);
    TEST_CHECK(tape.ptr == -5);
    
    tape_seekl(&tape, -2);
    TEST_CHECK(tape.ptr == -3);
    
    tape_seekl(&tape, 0);
    TEST_CHECK(tape.ptr == -3);
    
    tape_free(&tape);
}

/* Tests tape_seekr. */
void test_tape_seekr() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape.ptr == 0);
    
    tape_seekr(&tape, 5);
    TEST_CHECK(tape.ptr == 5);
    
    tape_seekr(&tape, -2);
    TEST_CHECK(tape.ptr == 3);
    
    tape_seekr(&tape, 0);
    TEST_CHECK(tape.ptr == 3)
    ;
    tape_free(&tape);
}

/* Tests tape_inc. */
void test_tape_inc() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape_get(&tape) == 0);
    
    tape_inc(&tape, 5);
    TEST_CHECK(tape_get(&tape) == 5);
    
    tape_inc(&tape, -2);
    TEST_CHECK(tape_get(&tape) == 3);
    
    tape_inc(&tape, 0);
    TEST_CHECK(tape_get(&tape) == 3);
    
    tape_free(&tape);
}

/* Tests tape_dec. */
void test_tape_dec() {
    Tape tape = tape_init(INT8_T, true, INFINITE, INFINITE);
    TEST_CHECK(tape_get(&tape) == 0);
    
    tape_dec(&tape, 5);
    TEST_CHECK(tape_get(&tape) == -5);
    
    tape_dec(&tape, -2);
    TEST_CHECK(tape_get(&tape) == -3);
    
    tape_dec(&tape, 0);
    TEST_CHECK(tape_get(&tape) == -3);
    
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
    {"tape_seekl", test_tape_seekl},
    {"tape_seekr", test_tape_seekr},
    {"tape_inc", test_tape_inc},
    {"tape_dec", test_tape_dec},
    {"tape_set/tape_get", test_tape_set_get},
    {0}
};
