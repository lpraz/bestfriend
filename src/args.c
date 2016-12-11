/*
 * args.c
 * Provides functions for processing command-line arguments.
 */

/* Import self */
#include "args.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Processes arguments, returns whether the program should continue. */
/* TODO: Make more capable as more interpreter features added */
bool args(int argc, char *argv[], char *bfpath) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            printf("BestFriend brainfuck interpreter\n");
            return false;
        }
    }
    
    bfpath = argv[1];
    return true;
}
