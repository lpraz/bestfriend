/*
 * args.c
 * Provides functions for processing command-line arguments.
 */

/* Import self */
#include "args.h"

/* Local imports */
#include "tape.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Processes arguments, returns whether the program should continue. */
/* TODO: Make more capable as more interpreter features added */
bool args(int argc, char **argv, char *bfpath, int *cwidth) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            printf("BestFriend brainfuck interpreter\n");
            return false;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: bestfriend [FILE]\n");
            printf("Runs FILE as a brainfuck program.\n");
            printf("If multiple FILEs are given, the last will be run.\n"); 
            return false;
        } else if (strncmp(argv[i], "--width=", 8) == 0) {
            if (strcmp(argv[i], "--width=32") == 0) {
                *cwidth = INT32_T;
            } else if (strcmp(argv[i], "--width=16") == 0) {
                *cwidth = INT16_T;
            } else if (strcmp(argv[i], "--width=8") == 0) {
                *cwidth = INT8_T;
            } else {
                printf("Invalid cell width, defaulting to 32-bit.\n");
            }
        } else {
            strcpy(bfpath, argv[i]);
        }
    }
    
    return true;
}
