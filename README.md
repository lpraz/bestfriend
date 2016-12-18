# BestFriend
A flexible Brainfuck interpreter written in C.

## Objectives
* Support as many environments as possible, so programs written for
  different environments can still be run under the same interpreter.
* Be fast - optimize repeated processes.

## Features
* Configurable cell width (8, 16 and 32-bit signed integers)
* Configurable input EOF behaviour (set to -1, set to 0, or no change)
* Unbounded tape in *both* directions!

## TODO
* Provide options for bounding tape, other environmental parameters
* Support TrivialBrainfuckSubstitution languages

## Building and (Un)Installing
 * Installing: On Linux systems, just `git clone` this repository, then
   `make`, then (`sudo`) `make install`. Your binary will be installed to
   `/usr/bin/bestfriend` by default. If you don't like this, just chnage
   the `PREFIX` and `INSTTARGET` variables in the makefile.
 * Uninstalling: Just (`sudo`) `make uninstall`.
