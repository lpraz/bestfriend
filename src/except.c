/*
 * except.c
 * Provides functions for dealing with exceptional situations and
 * errors caused when running a Brainfuck program.
 */

/* Import self */
#include "except.h"

/* Stdlib imports */
#include <stdio.h>
#include <stdlib.h>

/* Prints an error message and quits the program. */
void error(char *message) {
    printf("Error: %s\n", message);
    exit(EXIT_FAILURE);
}

/* Prints an exception message and quits the program. */
void except(char *message) {
    printf("Exception: %s\n", message);
    exit(EXIT_FAILURE);
}
