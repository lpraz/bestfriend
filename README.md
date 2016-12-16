# BestFriend
A flexible Brainfuck interpreter written in C.

## Objectives
* Support as many environments as possible, so programs written for different environments can still be run under the same interpreter.
* Be fast - optimize repeated processes.

## Features
* Configurable cell width (8, 16 and 32-bit signed integers)
* Unbounded tape in *both* directions!

## TODO
* Provide options for bounding tape, EOF, other environmental parameters
* Support TrivialBrainfuckSubstitution languages

## Building
On Linux systems, just `git clone` this repository, then `make` in its root directory. Your binary will be in `bin/a.out`.
