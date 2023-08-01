# Data Structure in C

## About

This repo is just for me learning data structures and algorithms in C.

## Usage

I assume you are using Linux or WSL.

1. Clone this repo `git clone https://github.com/rvyhvn/data-structure`
1. After the repo has cloned into your machine, go to the repo directory by executing `cd data-structure`
1. Compile the files into binary using Makefile by executing `make`

The `make` command will generate the `main` binary file, which you can use to interact with the sorting algorithms and data structures.

-   Run the sorting algorithms by using `./main sort <sorting_algorithm>`.
    Available sorting algorithms: bubble, heap, insertion, selection, merge, quick
-   Run the data structures by using `./main <command> [options]`.
    Available data structures (command): stack, bag, queue

Note: the program will tell you what to do with the commands.

## Usage Example

Usage example for data structure:
`./main stack push stack.csv 1`

Usage example for sorting algorithm:
`./main sort bubble`
