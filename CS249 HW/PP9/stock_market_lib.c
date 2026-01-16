// Include the necessary header file for stock market functions
#include "stock_market_lib.h"

/**
 * Task 1: Add a New Stock
 * Input arguments: market - a pointer to the Market heap
 *                  identifier - a string representing the stock identifier
 *                  performance - a float representing the stock performance in 
 *                                percentage
 * Output argument: the market is updated
 * Return: true if the stock is successfully added or false otherwise
 * Dependencies: upHeapify
 */
bool addStock(Market *market, const char *identifier, float performance)
{
	//check if there is space to add new 
	if(market->size >= MAX_STOCKS)
	{
		//return false if no new space
		return false;
	}
	//set the index to the end
	int index = market->size;

	//put our given identifier and preformance into our new node
	strcpy(market->stocks[index].identifier, identifier);
	market->stocks[index].performance = performance;

	//increment the size
	market->size++;

	//call upheapify to sort
	upHeapify(market, index);
	return true;
}


/**
 * Task 2: Remove a Stock by identifier
 * Input arguments: market - a pointer to the Market heap
 *                  identifier - a string representing the stock identifier
 * Output argument: the market is updated
 * Return: true if the stock is successfully removed, false otherwise
 * Dependencies: downHeapify
 */
bool removeStock(Market *market, const char *identifier)
{
	int  index = -1;
	//find node to remove use id
	for (int i = 0; i < market->size; i++)
	{
		if(strcmp(market->stocks[i].identifier, identifier) == 0)
		{
			index = i;
		}
	}

	//return false if not found
	if (index == -1)
	{
		return false;
	}

	//replace stock with last stock only if found - downheapify
	market->stocks[index] = market->stocks[market->size - 1];

	downHeapify(market, index);

	return true;
}


/**
 * Task 3: Display all Stocks in the Market
 * Input argument: market - a pointer to the Market heap
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void viewAllStocks(const Market *market)
{
	//printf
	printf("Stocks in the market:");

	//for loop for each stock
	for(int i = 0; i < market->size; i++)
	{
		//print identifier and preformance
		printf("Identifier: %s, Preformance, %.2f\n", market->stocks[i].identifier,
		market->stocks[i].performance);
	}
}





/**
 * Task 4: Sort Stocks by Performance
 * Input argument: market - a pointer to the Market heap
 * Output argument: the Market heap is sorted
 * Return: none
 * Dependencies: downHeapify, swap, viewAllStocks
 *               stdlib.h - malloc, free
 */
void sortStocks(const Market *market)
{
	//allocate space
	Market *temp = malloc(sizeof(Market));

	//temp size = market size
	temp->size = market->size;

	//loop through the stocks and set temp stocks = market stocks
	for(int i = 0; i < market->size; i++)
	{
		temp->stocks[i] = market->stocks[i];
	}


	for(int i = temp->size - 1; i > 0; i--)
	{
		swap(&temp->stocks[0], &temp->stocks[i]);

		temp->size--;

		downHeapify(temp, i);
	}

	//reset temp size
	temp->size = market->size;

	viewAllStocks(temp);
	free(temp);
}


/**
 * Task 5: Identify the Kth Largest Stock
 * Input arguments: market - a pointer to the Market heap
 *                  k - an integer value representing the kth largest stock
 * Output argument: none
 * Return: pointer to the Kth largest stock
 *         NULL if k is invalid
 * Dependencies: removeStock
 *               stdlib.h - malloc, free
 */
Stock* findKthLargest(Market *market, int k)
{
	//check if k is in bounds
	if(k < 1 || k > market->size)
	{
		return NULL;
	}
	//allocate space
	Market* temp = malloc(sizeof(Market));

	//temp size = market size
	temp->size = market->size;

	//loop through the stocks and set temp stocks = market stocks
	for(int i = 0; i < market->size; i++)
	{
		temp->stocks[i] = market->stocks[i];
	}

	//look through kth elements times
	Stock* Kthlargest =  malloc(sizeof(Stock));
	for(int i = 0; i < k; i++)
	{
		*Kthlargest = temp->stocks[0];
		//keep removing kth largest
		removeStock(temp,Kthlargest->identifier);
	}
	//free and return kthlargest
	free(temp);

	return Kthlargest;

}


/**
 * Task 6: Find the Top K Most Frequent Stocks
 * Input arguments: market - a pointer to the Market heap
 *                  k - an integer representing the number of stocks to show
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void topFreqStocks(Market *market, int k)
{
	//initialize variables
	int count[MAX_STOCKS];
	float performances[MAX_STOCKS];
	int size = 0;
	int found;
	float current;

	//iterate through the stocks
	for(int i = 0; i < market->size; i++)
	{
		found = 0;
		current = market->stocks[i].performance;

		//have we found the stock?
		for(int j = 0; j < size ; j++)
		{
		//if yes increment value in count
			if(performances[j] == current)
			{
				count[j]++;
				found = 1;
			}
		}
		if(found == 0)
		{
			//add new performance
			performances[size] = current;
			//add count = 0
			count[size] = 0;
			//use same index
			//increment the size
			size++;
		}
	}	

	//bubble sort
	for(int i = 0; i < size - 1;i++)
	{
		for(int j = 0; j < size - i - 1; j++)
		{
			//if count is less than next or equal and performance is <
			if(count[j] < count[j + 1] || ((count[j] == count[j + 1]) &&
			performances[j] < performances[j + 1]))
			{
				//swap both
				//swap count
				int tempcount = count[j];
				count[j] = count[j + 1];
				count[j + 1] = tempcount;

				//swap performance
				float tempperf = performances[j];
				performances[j] = performances[j + 1];
				performances[j + 1] = tempperf;
			}
		}
	}

	//print statements
	if(k > size)
	{
		printf("There is not enough performances.\n");
		printf("Showing the top %d frequent stocks based on perfromance:\n", size);
	}
	printf("Top %d frequent stocks based on performance:", k);

	for(int i = 0; i < k; i++)
	{
		printf("Performance: %.2f (Occurrences: %d\n)",performances[i], count[i]);
	}

}


// heap functions
/**
 * Function: upHeapify
 * Input arguments: market - a pointer to the Market heap
 *                  index - the index of the root of the subtree to heapify
 * Output argument: the subtree in the market is heapified
 * Return: none
 * Dependencies: swap, upHeapify (recursive)
 */
void upHeapify(Market *market, int index)
{
	//calcualte parent index
	int parent = (index - 1) / 2;
	//check if not root and parrent preformance < current perf
	if(index != 0 && market->stocks[parent].performance
		< market->stocks[index].performance)
	{
		//swap 
		swap(&market->stocks[parent], &market->stocks[index]);
		//recursive upheapify
		upHeapify(market, parent);
	}
}


/**
 * Function: downHeapify
 * Input arguments: market - a pointer to the Market heap
 *                  index - the index of the root of the subtree to heapify
 * Output argument: the subtree in the market is heapified
 * Return: none
 * Dependencies: swap, downHeapify (recursive)
 */
void downHeapify(Market *market, int index)
{
	//initialize variables
	int largest = index;

	//calculate r and left index
	int left = index * 2 + 1;
	int right = index * 2 + 2;

	//check r exists and bigger than current largest = left
	if(market->stocks[right].performance > market->stocks[largest].performance &&
		right < market->size)
	{
		largest = right;
	}

	//if left is less and exists largest = left
	if(market->stocks[left].performance > market->stocks[largest].performance &&
		left < market->size)
	{
		largest = left;
	}

	//if largest isnt currect swap and recurssive recall
	if(largest != index)
	{
		swap(&market->stocks[largest], &market->stocks[index]);
		downHeapify(market, largest);
	}
}


/**
 * Function: swap
 * Input arguments: a, b - pointers to a stock
 * Output argument: none
 * Return: none
 * Dependencies: none
 */
void swap(Stock *a, Stock *b)
{
	Stock temp = *a;

	*a = *b;

	*b = temp;
}

