/*
 * args.h
 * Defines abstract functions for processing command-line arguments.
 */

#ifndef ARGS_H
#define ARGS_H

/* Stdlib imports */
#include <stdbool.h>

/* Processes arguments, returns whether the program should continue. */
bool args(int argc, char *argv[], char *bfpath);

#endif
