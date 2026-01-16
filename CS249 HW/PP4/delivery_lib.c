// header files
#include "delivery_lib.h"

/**
 * Function: swapOrders (provided)
 * Input argument: two pointer to orders
 * Output argument: swapped orders
 * Return: none
 * Dependencies: none
 */
void swapOrders(Order* leftOrder, Order* rightOrder)
{
    // temporary order receives the left order
    Order temp = *leftOrder;
    // the left order is set to the right order
    *leftOrder = *rightOrder;
    // the right order is set to the temporary variable
    *rightOrder = temp;
}

/**
 * Task 1: Organizing Orders by Category (sortOrders)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by category
 * Return: none
 * Dependencies: swapOrders (provided), stdio.h
 */
void sortOrders(Order orders[], int size)
{

}


/**
 * Task 2: Prioritizing High-Priority Deliveries (findKthHighestPriority)
 * Input argument: - array of orders
 *                 - an integer value representing the array size
 *                 - integer value representing k
 * Output argument: none
 * Return: integer value representing the k-th priority or an error code
 * Dependencies: mergesort, stdlib.h
 */
int findKthHighestPriority(const Order orders[], int size, int k)
{

}


/**
 * Task 2.1: merge (helper function)
 * Input argument: - array of integers
 *                 - left, middle and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: stdlib.h
 */
void merge(int arr[], int left, int mid, int right)
{
    int lefthalf = mid - left + 1;
    int righthalf = right - mid;

    int templeft[lefthalf];
    int tempright[righthalf];

    for(int i = 0; i < lefthalf; i++ )
    {
        templeft[i] = arr[i+1];
    }
    for(int j = 0; j < righthalf; j++)
    {
        tempright[j] = arr[j + mid + 1];
    }

    int i = 0;
    int j = 0;
    int h = left;

    while(i < lefthalf && j< righthalf )
    {
        if(templeft[i] <= tempright[j])
        {
            arr[h] = templeft[i];
            i++;
        }
        else{
            arr[h] = tempright[j];
            j++;
        }
        h++
    }
    while(i < lefthalf)
    {
        arr[h] = templeft[i];
        i++;
        h++;
    }
    while(j < righthalf)
    {
        arr[h] = tempright[j];
        j++;
        h++;
    }


}


/**
 * Task 2.2: mergesort (helper function)
 * Input argument: - array of integers
 *                 - left and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: mergesort (recursive), merge
 */
void mergeSort(int arr[], int left, int right)
{
    if(left < right)
    {
        int mid = 1 + (right - 1) / 2;
        mergeSort(arr, 1, mid);
        mergeSort(arr, mid + 1, right);




        merge(arr, 1, mid, right);

    }
}



/**
 * Task 3: Detecting Duplicate Orders (containsDuplicateOrder)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: true if there are duplicates, false otherwise
 * Dependencies: string.h
 */

bool containsDuplicateOrder(const Order orders[], int size)
{
    if(size < 2)
    {
        return false;
    }
    for(int i = 0; i < size; i++)
        {
            for(j = 0; j < size; j+=)
            {
                if(orders[i].id == orders[j].id)
                {
                    return true;
                }
            }
        }
    return false;
}


/**
 * Task 4: Balancing Customer Satisfaction (findTriplets)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: error code when memory allocation fails; success code otherwise
 * Dependencies: quicksort, stdlib.h - malloc, free
 */
int findTriplets(const Order orders[], int size)
{
      
}


/**
 * Task 4.1: partition (helper function)
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: array partitioned at the pivot value
 * Return: the index of the pivot element after partitioning
 * Dependencies: none
 */
int partition(int arr[], int left, int right)
{
    int pivot = arr[right];

    int i = left - 1;



    for(int j = left; j <= right -1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }   
    }
    swap(&arr[i+1], &arr[right]);
    return i+1;

}


/**
 * Task 4.2: quicksort (helper function)
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: sorted array
 * Return: none
 * Dependencies: partition, quicksort
 */
void quicksort(int arr[], int left, int right)
{
    if(left < right )
    {
        int pivot = partition(arr, left, right);

        quicksort(arr, left, pivot - 1);
        quicksort(arr, pi + 1, right);
    }
}


/**
 * Task 5: Grouping Orders by Cuisine (groupOrders)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: insertionsort, string.h, stdio.h
 */



/**
 * Task 5.1: insertionsort (helper function)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: string.h
 */
void insertionsort(Order orders[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        Order key = orders[i];

        int j = i - 1;

        while(j < 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}


/**
 * Task 6: Ranking Delivery Staff by Performance (sortStaffFromOrders)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */



/**
 * Function: displayMenu (provided)
 * Input argument: none
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void displayMenu() 
{
    // print the title of the order management system
    printf("\nQuickBite Order Management System\n");
    // print the option to view orders
    printf("1. View Orders\n");
    // print the option to reset orders to the original state
    printf("2. Reset Orders to Original\n");
    // print the option to sort orders by category
    printf("3. Sort Orders by Category\n");
    // print the option to find the k-th highest priority order
    printf("4. Find k-th Highest Priority\n");
    // print the option to detect duplicate orders
    printf("5. Detect Duplicate Orders\n");
    // print the option to find route triplets among orders
    printf("6. Find Customer Service Score Triplets\n");
    // print the option to group orders by cuisine
    printf("7. Sort and Group Orders by Cuisine\n");
    // print the option to sort staff by performance
    printf("8. Print Staff by Performance\n");
    // print the option to exit the program
    printf("9. Exit\n");
}

/**
 * Function: readCSV (provided)
 * Input argument: filename, array of orders, a pointer to the array size
 * Output argument: filled array of orders, updated array size
 * Return: success or error code
 * Dependencies: stdio.h
 */
int readCSV(const char* filename, Order orders[], int* size) 
{
    // open the file for reading
    FILE* file = fopen(filename, "r");
    // if the file is open
    if (!file) 
    {
        // print the error
        perror("Failed to open file");
        // return the error code
        return ERROR;
    }

    // start an index at 0
    int i = 0;
    // while there's data to read in the file
    while (fscanf(file, "%d,%49[^,],%d,%d,%d,%49[^,],%d", 
                  &orders[i].id, 
                  orders[i].clientName,
                  (int*)&orders[i].category, 
                  &orders[i].priority, 
                  &orders[i].staffScore, 
                  orders[i].cuisine, 
                  &orders[i].customerSatisfaction) == 7) 
    {
        // increment the index
        i++;
    }
    // set the size pointer to index
    *size = i;
    // close the file
    fclose(file);
    // return success
    return SUCCESS;
}

/**
 * Function: printOrders (provided)
 * Input argument: array of orders, an integer value representing the array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void printOrders(const Order orders[], int size)
{
    // traverse the array
    for (int i = 0; i < size; i++) 
    {
        // print details of each order
        printf("Order #%d - %s, Category: %d, Priority: %d, Staff Score: %d,"
            "Cuisine: %s, Customer Satisfaction Score: %d\n", orders[i].id, 
            orders[i].clientName, orders[i].category, orders[i].priority,
            orders[i].staffScore, orders[i].cuisine, 
            orders[i].customerSatisfaction); 
    }
}