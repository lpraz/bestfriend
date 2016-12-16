/*
 * except.h
 * Defines abstract functions for dealing with exceptional situations
 * and errors caused when running a Brainfuck program.
 */

#ifndef EXCEPT_H
#define EXCEPT_H

/* Prints an error message and quits the program. */
void error(char *message);

/* Throws an exception and quits the program. */
void except(char *message);

#endif
