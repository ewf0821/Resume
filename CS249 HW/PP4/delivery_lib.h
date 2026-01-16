#ifndef DELIVERY_LIB_H 
#define DELIVERY_LIB_H 

// header files
#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

// global definitions
#define ERROR -1
#define SUCCESS 0

// enum for order categories
typedef enum 
{
    FOOD = 0, 
    DRINKS = 1, 
    DESSERTS = 2 
}
Category;

// struct to represent an order
typedef struct 
{
    int id; 
    char clientName[50];
    Category category;
    int priority;
    int staffScore;
    char cuisine[50]; 
    int customerSatisfaction; 
}
Order;

// function prototypes
/**
 * Function: swapOrders (provided)
 * Input argument: two pointer to orders
 * Output argument: swapped orders
 * Return: none
 * Dependencies: none
 */
void swapOrders(Order* leftOrder, Order* rightOrder);

/**
 * Function: sortOrders
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by category
 * Return: none
 * Dependencies: swapOrders (provided), stdio.h
 */
void sortOrders(Order orders[], int size); 

/**
 * Function: findKthHighestPriority
 * Input argument: - array of orders
 *                 - an integer value representing the array size
 *                 - integer value representing k
 * Output argument: none
 * Return: integer value representing the k-th priority
 * Dependencies: mergesort, stdlib.h
 */
int findKthHighestPriority(const Order orders[], int size, int k); 

/**
 * Function: merge
 * Input argument: - array of integers
 *                 - left, middle and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: stdlib.h
 */
void merge(int arr[], int left, int mid, int right); 

/**
 * Function: mergesort
 * Input argument: - array of integers
 *                 - left and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: mergesort (recursive), merge
 */
void mergeSort(int arr[], int left, int right);

/**
 * Function: containsDuplicateOrder
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: true if there are duplicates, false otherwise
 * Dependencies: string.h
 */
bool containsDuplicateOrder(const Order orders[], int size); 

/**
 * Function: findTriplets
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: error code when memory allocation fails; success code otherwise
 * Dependencies: quicksort, stdlib.h - malloc, free
 */
int findTriplets(const Order orders[], int size);

/**
 * Function: partition
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: sorted array
 * Return: the index of the pivot element after partitioning
 * Dependencies: swap
 */
int partition(int arr[], int left, int right);

/**
 * Function: quicksort
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: sorted array
 * Return: none
 * Dependencies: partition, quicksort
 */
void quicksort(int arr[], int left, int right);

/**
 * Function: groupOrders
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: insertionsort, string.h, stdio.h
 */
void groupOrders(Order orders[], int size); 

/**
 * Function: insertionsort
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: string.h
 */
void insertionsort(Order orders[], int size);

/**
 * Function: sortStaffFromOrders
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void sortStaffFromOrders(Order orders[], int size); 

/**
 * Function: displayMenu (provided)
 * Input argument: none
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void displayMenu();

/**
 * Function: readCSV (provided)
 * Input argument: filename, array of orders, a pointer to the array size
 * Output argument: filled array of orders, updated array size
 * Return: success or error code
 * Dependencies: stdio.h
 */
int readCSV(const char* filename, Order orders[], int* size); 

/**
 * Function: printOrders (provided)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void printOrders(const Order orders[], int size);

#endif // DELIVERY_LIB_H 
