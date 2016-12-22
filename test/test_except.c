/*
 * test_except.c
 * Tests except.c.
 */

/* Import test subject */
#include "except.h"

/* Stdlib imports */
#include <stdio.h>

/* Import test framework (GLib) */
#include <glib.h>

/* Runs tests. */
static void test_except() {
    g_assert(1 == 1) /* To get the hang of this */
    //g_assert_cmpstr(except("Test"), ==, "Exception: Test\n");
}

/* Main method */
int main(int argc, char **argv) {
    gtk_test_init(&argc, &argv, NULL);
    g_test_add_func("/test_except", test_except)
    return g_test_run();
}
