/*
 * main.c
 * Provides top-level functions for the BestFrield interpreter.
 */

/* Local imports */
#include "stack.h"
#include "tape.h"

/* Stdlib imports */


int main(int argc, char **argv) {
    /* Declarations - data */
    Tape tape = tape_init();
    Stack loops = stk_init();
    
    /* Declarations - brainfuck file */
    char *bfpath = "in.bf" /* TODO: make user-specifiable */
    FILE *bfsrc = fopen(bfpath, "r");
    char cmd;
    int file_ptr;
    
    /* Declarations - user interaction */
    char in;
    
    if (bfsrc == NULL) {
        printf("Exception - couldn't open %s!", bfpath);
        exit(EXIT_FAILURE);
    }
    
    while (cmd = fgetc(bfsrc); cmd != EOF) {
        switch(cmd) {
            case '+': /* Increment cell at ptr */
                tape_inc(&tape, 1);
                break;
            case '-': /* Decrement cell at ptr */
                tape_dec(&tape, 1);
                break;
            case '>': /* Seek right */
                tape_seekr(&tape);
                break;
            case '<': /* Seek left */
                tape_seekl(&tape);
            case '.': /* Output cell as char */
                printf("%c", (char)tape_get(&tape));
            case ',': /* Input char to cell */
                tape_set(&tape, getchar());
            case '[': /* Begin loop, jump to end if cell == 0 */
            case ']': /* End loop, jump to start if cell != 0 */
        }
        file_ptr++;
    }
    
    /* Cleanup - close */
    if (fclose(bfsrc) != 0)
        printf("Error in closing file");
    
    /* Cleanup - free memory */
    stk_free(&loops);
    tape_free(&tape);
}
