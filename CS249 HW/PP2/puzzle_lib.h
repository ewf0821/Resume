#ifndef PUZZLE_LIB_H
#define PUZZLE_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constants
#define MAX_PATHS 100
#define MAX_LENGTH 100
#define N_BOXES 5
#define MAZE_SIZE 4
#define MAX_PATH_LENGTH 17
#define MAX_SUBSET_SIZE 4

// Function Prototypes
/**
 * Function: fillContainerBox (Task 1)
 * Arguments: - the size of the container
 *            - an array of boxes to be placed in the container
 *            - the number of boxes in the array
 *            - the index in the array where the placement should start
 * Return: true if a combination of boxe's sizes is equal to the container size
 *         false otherwise
 * Dependencies: fillContainerBox (recursive)
 */
bool fillContainerBox(
    int containerSize, int* boxSizes, int numBoxes, int index);

/**
 * Function: solveMaze (Task 2)
 * Arguments: - the maze size
 *            - the maze
 *            - the coordinates (x,y) for the current position in the maze
 *            - the path
 *            - the position to add the value in the path
 *            - the matrix of visited positions
 * Return: true if a combination of boxe's sizes is equal to the container size
 *         false otherwise
 * Dependencies: puzzle_lib.h - solveMaze (recursive), isSafe (provided)
 */
void solveMaze(
    int size, int maze[size][size], int x, int y, char *path, int pathIndex,
    bool visited[size][size]);

/**
 * Function: isSafe (provided)
 * Arguments: - the maze size
 *            - the maze
 *            - the coordinates (x,y) for the current position in the maze
 *            - the matrix of visited positions
 * Return: true if matrix in the given coordinate (x,y) is within bounds,
 *              it is an open path and it is not visited
 *         false otherwise
 * Dependencies: none
 */
bool isSafe(int size, int maze[size][size], int x, int y,
    bool visited[size][size]);

/**
 * Function: findSubsets (Task 3)
 * Arguments: - the list of investments
 *            - the number of available options
 *            - the target sum the investments must achieve
 *            - the index for the next considered investment
 *            - the current sum
 *            - the current subset of selected investments
 *            - the index representing the size of the current subset
 * Return: none
 * Dependencies: puzzle_lib.h - findSubsets (recursive)
 */
void findSubsets(
    int investments[], int numInvestments, int target, int index,
    int currentSum, int currentSubset[], int subsetIndex);

#endif // PUZZLE_LIB_H
