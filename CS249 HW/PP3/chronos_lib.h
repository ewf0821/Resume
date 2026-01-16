// include guards
#ifndef CHRONOS_LIB_H
#define CHRONOS_LIB_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// global constants
#define SIZE 12  // size of the array used in all tasks
#define NOT_FOUND -1
#define CHARACTERS 256 // number of ASCII symbols

// Function prototypes
/**
 * Function: unique_code
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the unique integer that appears only once in the array
 * Dependencies: none
 */
int unique_code(int array[], int size);

/**
 * Function: balance
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the index where the sum of elements on the left equals the sum on the right
 * Dependencies: none
 */
int balance(int array[], int size);

/**
 * Function: decode
 * Input argument: scrambled_message as a string, reference_message as a string
 * Output argument: none
 * Return: boolean value indicating if the messages are anagrams
 * Dependencies: none
 */
bool decode(const char *scrambled_message, const char *reference_message);

/**
 * Function: uncover
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the maximum sum of a contiguous subarray
 * Dependencies: none
 */
int uncover(int array[], int size);

/**
 * Function: navigate
 * Input argument: array as a 1D array of integers, size as an integer, data_element as an integer
 * Output argument: none
 * Return: the index of the data_element in the rotated sorted array
 * Dependencies: none
 */
int navigate(int array[], int size, int data_element);

/**
 * Function: critical_minimum
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the minimum value in a rotated sorted array
 * Dependencies: none
 */
int critical_minimum(int array[], int size);

#endif // CHRONOS_LIB_H
