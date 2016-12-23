/*
 * test_except.c
 * Tests except.c.
 */

/* Import test subject */
#include "except.h"


/* Import test framework */
#include "cutest.h"

/* Tests except(). */
void test_except_except() {
    except("Testing");
}

/* Tests error(). */
void test_except_error() {
    error("Testing");
}

TEST_LIST = {
    {"except_except", test_except_except},
    {"except_error", test_except_error},
    {0}
};
