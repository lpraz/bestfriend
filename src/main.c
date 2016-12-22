/*
 * main.c
 * Provides top-level functions for the BestFrield interpreter.
 */

/* Local imports */
#include "args.h"
#include "except.h"
#include "loop.h"
#include "stack.h"
#include "tape.h"

/* Stdlib imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Contains the main program loop, performs I/O, etc. */
int main(int argc, char **argv) {
    /* Declarations - environment */
    Tape tape;
    Stack loops = stk_init(DEFAULT_STACK_SIZE);
    int cwidth = INT32_T;
    char eofval = -1;
    bool wrap = true;
    int max_fwdsize = INFINITE;
    int max_revsize = INFINITE;
    
    /* Declarations - brainfuck file */
    char *bfpath = malloc(256 * sizeof(char));
    FILE *bfsrc;
    char cmd;
    int file_ptr = 1;
    
    /* Declarations - user interaction */
    char in;
    
    /* Get command-line arguments, quit if necessary */
    bfpath[0] = '\0';
    if (!args(argc, argv, bfpath, &cwidth, &eofval, &wrap, &max_fwdsize, 
            &max_revsize))
        return EXIT_SUCCESS;
    
    /* Set up tape */
    tape = tape_init(cwidth, wrap, max_fwdsize, max_revsize);
    
    /* Open file. Did it work? */
    if (bfpath[0] == '\0')
        except("No file specified");
    
    bfsrc = fopen(bfpath, "r");
    
    if (bfsrc == NULL)
        except("Couldn't open file");
    
    /* Main program loop */
    while ((cmd = fgetc(bfsrc)) != EOF) {
        switch(cmd) {
            case '+': /* Increment cell at ptr */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_inc(&tape, 1);
                break;
            case '-': /* Decrement cell at ptr */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_dec(&tape, 1);
                break;
            case '>': /* Seek right */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_seekr(&tape, 1);
                break;
            case '<': /* Seek left */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    tape_seekl(&tape, 1);
                break;
            case '.': /* Output cell as char */
                if (stk_isempty(&loops) || !stk_top(&loops).skip)
                    printf("%c", (char)tape_get(&tape));
                break;
            case ',': /* Input char to cell */
                if (stk_isempty(&loops) || !stk_top(&loops).skip) {
                    in = getchar();
                    if (in == EOF && eofval != EOF_NO_CHANGE)
                        tape_set(&tape, eofval);
                    else if (in != EOF)
                        tape_set(&tape, in);
                }
                break;
            case '[': /* Begin loop, jump to end if cell == 0 */
                loop_start(&loops, tape_get(&tape), file_ptr);
                break;
            case ']': /* End loop, jump to start if cell != 0 */
                if (loop_end(&loops, tape_get(&tape))) {
                    if (fseek(bfsrc, stk_top(&loops).start, SEEK_SET)
                            != 0)
                        error("Couldn't seek file");
                    
                    file_ptr = stk_top(&loops).start;
                }
                break;
        }
        file_ptr++;
    }
    
    /* Cleanup - check that stack is empty */
    if (!stk_isempty(&loops))
        except("'[' with no matching ']'");
    
    /* Cleanup - close */
    if (fclose(bfsrc) != 0)
        error("Couldn't close file");
    
    /* Cleanup - free memory */
    stk_free(&loops);
    tape_free(&tape);
    free(bfpath);
    
    return EXIT_SUCCESS;
}
