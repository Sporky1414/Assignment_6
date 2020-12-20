# Assignment_6

## Identifying Information:
1. AJ Keenan
1. Student ID: 2316808
1. akeenan@chapman.edu
1. CPSC 350-02
1. Assignment: Assignment 6

## Application Purpose
The purpose of this application is to sort through double values (passed in as a file) and see how long each of the five sorts (Quick, Merge, Insertion, Selection, and Bubble) takes for a given dataset. Predominately, the first two sorts (Quick and Merge) will take the shortest amount of time, the next two (Insertion and Selection) will take much longer (with Insertion sometimes beating out Selection if the data is already partially sorted), and the last (Bubble) will take the longest.

## Source Files
1. FileIO.cpp
1. FileIO.h
1. main.cpp
1. Simulation.cpp
1. Simulation.h
1. Sorter.cpp
1. Sorter.h
1. Makefile

## Other Files Present
1. Assignment 6 Write Up.pdf
1. README.md

## Known Errors:
1. All sorting results also include the amount of time needed to copy the data. Throughout testing (including with 10 million doubles), this did not have any impact on the results of the simulation, but it should be noted anyway.
1. The file must contain nothing except the one integer at the top and the decimals numbers afterwards. This includes extra lines/spaces at the end of the file.

## References
1. Zybooks (All sorting pseudo code except Bubble Sort)
1. Class Notes (Bubble Sort Pseudo Code)
1. Stack Overflow (rand() and srand() are not declared in this scope)
1. CPlusPlus.com (time, Data type conversion int to double within function)

## Compilation Instructions
Use the "make all" command, courtesy of the included MAKEFILE, to compile all source files. To run the program, run the assignment6.exe program from any linux terminal, such as in docker. As a command line argument, pass through the file you wish to test with. If you forget this command line argument, the program will ask for it from you after starting the program.
