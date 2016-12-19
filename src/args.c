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
#include <stdlib.h>
#include <string.h>

/* Processes arguments, returns whether the program should continue. */
bool args(int argc, char **argv, char *bfpath, int *cwidth, char *eofval,
          bool *wrap, int *max_fwdsize, int *max_revsize) {
    char *temp;
    
    for (int i = 1; i < argc; i++) {
        /* Version */
        if (strcmp(argv[i], "--version") == 0) {
            printf("BestFriend brainfuck interpreter\n");
            return false;
        /* Help */
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: bestfriend [FILE]\n");
            printf("Runs FILE as a brainfuck program.\n");
            printf("If multiple FILEs are given, the last will be run.\n"); 
            return false;
        /* Cell width */
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
        /* End-of-file */
        } else if (strncmp(argv[i], "--eof=", 6) == 0) {
            if (strcmp(argv[i], "--eof=-1") == 0) {
                *eofval = -1;
            } else if (strcmp(argv[i], "--eof=0") == 0) {
                *eofval = 0;
            } else if (strcmp(argv[i], "--eof=nochg") == 0) {
                *eofval = EOF_NO_CHANGE;
            } else {
                printf("Invalid EOF behaviour, defaulting to -1.\n");
            }
        /* Overflow/wrapping */
        } else if (strncmp(argv[i], "--wrap=", 7) == 0) {
            if (strncmp(argv[i], "--wrap=y", 8) == 0) {
                *wrap = true;
            } else if (strncmp(argv[i], "--wrap=n", 8) == 0) {
                *wrap = false;
            }
        /* Fowrard bound */
        } else if (strncmp(argv[i], "--fwdbound=", 11) == 0) {
            temp = malloc((strlen(argv[i]) - 10) * sizeof(char));
            strcpy(temp, argv[i] + 11);
            *max_fwdsize = atoi(temp);
        /* Reverse bound */
        } else if (strncmp(argv[i], "--revbound=", 11) == 0) {
            temp = malloc((strlen(argv[i]) - 10) * sizeof(char));
            strcpy(temp, argv[i] + 11);
            *max_fwdsize = atoi(temp);
        } else {
            strcpy(bfpath, argv[i]);
        }
    }
    
    return true;
}
