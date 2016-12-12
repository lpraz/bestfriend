/*
 * main.c
 * Provides top-level functions for the BestFrield interpreter.
 */

/* Local imports */
#include "args.h"
#include "loop.h"
#include "stack.h"
#include "tape.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Debug */
#include <unistd.h>

int main(int argc, char **argv) {
    /* Declarations - data */
    Tape tape = tape_init();
    Stack loops = stk_init(DEFAULT_STACK_SIZE);
    
    /* Declarations - brainfuck file */
    char *bfpath;
    FILE *bfsrc;
    char cmd;
    int file_ptr = 0;
    
    /* Declarations - user interaction */
    char in;
    
    /* Get command-line arguments, quit if necessary */
    if (!args(argc, argv, bfpath))
        return 0;
    
    /* Open file. Did it work? */
    /* TODO: Make user-definable */
    bfsrc = fopen("in.bf", "r");
    if (bfsrc == NULL) {
        printf("Exception - couldn't open %s!\n", bfpath);
        return 1;
    }
    
    /* Main program loop */
    while ((cmd = fgetc(bfsrc)) != EOF) {
        switch(cmd) {
            case '+': /* Increment cell at ptr */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_inc(&tape, 1);
                printf("Up to %d ", tape_get(&tape)); /* Debug */
                break;
            case '-': /* Decrement cell at ptr */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_dec(&tape, 1);
                printf("Down to %d ", tape_get(&tape)); /* Debug */
                break;
            case '>': /* Seek right */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_seekr(&tape, 1);
                printf("Right to %d ", tape.ptr); /* Debug */
                break;
            case '<': /* Seek left */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_seekl(&tape, 1);
                printf("Left to %d ", tape.ptr); /* Debug */
                break;
            case '.': /* Output cell as char */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    printf("%c", (char)tape_get(&tape));
                break;
            case ',': /* Input char to cell */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_set(&tape, getchar());
                break;
            case '[': /* Begin loop, jump to end if cell == 0 */
                loop_start(&loops, tape_get(&tape), file_ptr);
                break;
            case ']': /* End loop, jump to start if cell != 0 */
                if (loop_end(&loops, tape_get(&tape))) {
                    if (fseek(bfsrc, stk_top(&loops).start, SEEK_SET)
                            != 0) {
                        printf("Error in seeking file!\n");
                        exit(EXIT_FAILURE);
                    }
                    file_ptr = stk_top(&loops).start;
                }
                sleep(1); /* Debug */
                break;
        }
        printf("%d\n", file_ptr); /* Debug */
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
