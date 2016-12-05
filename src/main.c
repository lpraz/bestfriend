/*
 * main.c
 * Provides top-level functions for the BestFrield interpreter.
 */

/* Local imports */
#include "loop.h"
#include "stack.h"
#include "tape.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /* Declarations - data */
    Tape tape = tape_init();
    Stack loops = stk_init(DEFAULT_STACK_SIZE);
    
    /* Declarations - brainfuck file */
    char *bfpath = "in.bf"; /* TODO: make user-specifiable */
    FILE *bfsrc = fopen(bfpath, "r");
    char cmd;
    int file_ptr;
    
    /* Declarations - user interaction */
    char in;
    
    if (bfsrc == NULL) {
        printf("Exception - couldn't open %s!\n", bfpath);
        exit(EXIT_FAILURE);
    }
    
    while (cmd = fgetc(bfsrc), cmd != EOF) {
        switch(cmd) {
            case '+': /* Increment cell at ptr */
                tape_inc(&tape, 1);
                break;
            case '-': /* Decrement cell at ptr */
                tape_dec(&tape, 1);
                break;
            case '>': /* Seek right */
                tape_seekr(&tape, 1);
                break;
            case '<': /* Seek left */
                tape_seekl(&tape, 1);
                break;
            case '.': /* Output cell as char */
                printf("%c", (char)tape_get(&tape));
                break;
            case ',': /* Input char to cell */
                tape_set(&tape, getchar());
                break;
            case '[': /* Begin loop, jump to end if cell == 0 */
                if (loop_start(&loops, tape_get(&tape), file_ptr))
                    while (cmd = fgetc(bfsrc), cmd != EOF && cmd != ']');
                break;
            case ']': /* End loop, jump to start if cell != 0 */
                if (loop_end(&loops, tape_get(&tape)) == false) {
                    if (fseek(bfsrc, file_ptr - stk_top(&loops), SEEK_CUR)
                            != 0) {
                        printf("Error in seeking file!\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
                        
        }
        file_ptr++;
    }
    
    printf("\n");
    
    /* Cleanup - close */
    if (fclose(bfsrc) != 0) {
        printf("Error in closing %s!\n", bfpath);
        exit(EXIT_FAILURE);
    }
    
    /* Cleanup - free memory */
    stk_free(&loops);
    tape_free(&tape);
    
    return 0;
}
