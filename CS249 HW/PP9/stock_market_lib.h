#ifndef STOCK_MARKET_LIB_H
#define STOCK_MARKET_LIB_H

// header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// global definitions
#define MAX_STOCKS 1000

// data types
typedef struct 
{
    char identifier[20];
    float performance;
}
Stock;

typedef struct 
{
    Stock stocks[MAX_STOCKS];
    int size;
}
Market;

// function prototypes
/**
 * Function: addStock
 * Input arguments: market - a pointer to the Market heap
 *                  identifier - a string representing the stock identifier
 *                  performance - a float representing the stock performance in 
 *                                percentage
 * Output argument: the market is updated
 * Return: true if the stock is successfully added or false otherwise
 * Dependencies: upHeapify
 */
bool addStock(Market *market, const char *identifier, float performance);

/**
 * Function: removeStock
 * Input arguments: market - a pointer to the Market heap
 *                  identifier - a string representing the stock identifier
 * Output argument: the market is updated
 * Return: true if the stock is successfully removed, false otherwise
 * Dependencies: downHeapify
 */
bool removeStock(Market *market, const char *identifier);

/**
 * Function: viewAllStocks
 * Input argument: market - a pointer to the Market heap
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void viewAllStocks(const Market *market);

/**
 * Function: sortStocks
 * Input argument: market - a pointer to the Market heap
 * Output argument: the Market heap is sorted
 * Return: none
 * Dependencies: downHeapify, swap, viewAllStocks
 *               stdlib.h - malloc, free
 */
void sortStocks(const Market *market);

/**
 * Function: findKthLargest
 * Input arguments: market - a pointer to the Market heap
 *                  k - an integer value representing the kth largest stock
 * Output argument: none
 * Return: pointer to the Kth largest stock
 *         NULL if k is invalid
 * Dependencies: removeStock
 *               stdlib.h - malloc, free
 */
Stock* findKthLargest(Market *market, int k);

/**
 * Function: topFreqStocks
 * Input arguments: market - a pointer to the Market heap
 *                  k - an integer representing the number of stocks to show
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void topFreqStocks(Market *market, int k);

// heap functions
/**
 * Function: upHeapify
 * Input arguments: market - a pointer to the Market heap
 *                  index - the index of the root of the subtree to heapify
 * Output argument: the subtree in the market is heapified
 * Return: none
 * Dependencies: swap, upHeapify (recursive)
 */
void upHeapify(Market *market, int index);

/**
 * Function: downHeapify
 * Input arguments: market - a pointer to the Market heap
 *                  index - the index of the root of the subtree to heapify
 * Output argument: the subtree in the market is heapified
 * Return: none
 * Dependencies: swap, downHeapify (recursive)
 */
void downHeapify(Market *market, int index);

/**
 * Function: swap
 * Input arguments: a, b - pointers to a stock
 * Output argument: none
 * Return: none
 * Dependencies: none
 */
void swap(Stock *a, Stock *b);

#endif // STOCK_MARKET_LIB_H
