#ifndef MOSAIC_LIB_H
#define MOSAIC_LIB_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// global constants
#define SIZE 6
#define STEPS 3
#define ARRAY_SIZE 36

// Function prototypes
/**
 * Function: transpose (Task 1)
 * Input argument: the mural as a 2D array of integer
 * Output argument: the tranposed mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void transpose(int matrix[SIZE][SIZE]);

/**
 * Function: rotate (Task 2)
 * Input argument: the mural as a 2D array of integer
 * Output argument: the rotated mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void rotate(int matrix[SIZE][SIZE]);

/**
 * Function: zeroMatrix (Task 3)
 * Input argument: the mural as a 2D array of integer
 * Output argument: the restored mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void zeroMatrix(int matrix[SIZE][SIZE]);

/**
 * Function: rotateRow (Task 4)
 * Input argument: the mural as a 2D array of integer, k number of steps
 * Output argument: the mural with a rotated row as a 2D array of integer
 * Return: none
 * Dependencies: stdlib.h - rand
 */
void rotateRow(int matrix[SIZE][SIZE], int k);

/**
 * Function: spiralOrder (Task 5)
 * Input argument: the mural as a 2D array of integer
 * Output argument: none
 * Return: dynamically allocated array of integers
 * Dependencies: none
 */
int* spiralOrder(int matrix[SIZE][SIZE]);

/**
 * Function: printMatrix (provided)
 * Input argument: the mural as a constant 2D array of integer
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void printMatrix(const int matrix[SIZE][SIZE]);

#endif // MOSAIC_LIB_H
