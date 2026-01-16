// Include the stock market library header file
#include "stock_market_lib.h"

// Define the main function
int main() 
{
    // declare a variable to store the market
    Market market;
    //initialize the market
    market.size = 0;

    // declare variables for user input
    int choice = 0;
    int k;
    // declare a variable to store the stock performance
    float performance;
    // declare an array to store the stock identifier
    char identifier[20];

    // 
    while (choice != 7) 
    {
        // print the menu options
        printf("\nStock Market Analysis Menu:\n");
        printf("1. Add Stock\n");
        printf("2. Remove Stock\n");
        printf("3. View All Stocks\n");
        printf("4. Sort Stocks by Performance\n");
        printf("5. Find Kth Largest Stock\n");
        printf("6. Find Top K Frequent Stocks\n");
        printf("7. Exit\n");

        // prompt user for the menu option
        printf("Enter your choice: ");
        // read the user's choice
        scanf("%d", &choice);
        // choose the user's option
        switch (choice) 
        {
            // Task 2: Add a new stock to the market
            case 1:
                // prompt user for the stock identifier and performance
                printf("Enter Stock Identifier: ");
                // read the identifier
                scanf("%s", identifier);

                // prompt user for the stock performance
                printf("Enter Stock Performance: ");
                // read the performance
                scanf("%f", &performance);

                // add the stock to the market
                if(addStock(&market, identifier, performance))
                {
                    // print a confimation message
                    puts("Stock added successfully");
                }
                // otherwise
                else
                {
                    // print an error message
                    puts("Market may be full. Try again later");
                }
                // end case
                break;

            // Task 3: Remove a Stock
            case 2:
                // prompt user for the identifier of the stock to remove
                printf("Enter Stock Identifier to Remove: ");
                // read the identifier
                scanf("%s", identifier);

                // remove the specified stock
                if(removeStock(&market, identifier))
                {
                    // print a confimation message
                    puts("Stock removed successfully");
                }
                // otherwise
                else
                {
                    // print an error message
                    puts("Stock cannot be found in the current market");
                }
                // end case
                break;
            // Task 4: View all stocks in the market
            case 3:
                // display all stocks
                viewAllStocks(&market);
                // end case
                break;

            // Task 5: Sort stocks by performance
            case 4:
                // sort stocks by performance
                sortStocks(&market);
                // print a message
                puts("Market successfully sorted");
                // end case
                break;

            // Task 6: Identify the Kth Largest Stock
            case 5:
                // prompt user for the K value
                printf("Enter value of K: ");
                // read the value of K
                scanf("%d", &k);

                // find the kth stock by performance
                Stock *kthLargest = findKthLargest(&market, k);

                // if the kth largest stock is found
                if (kthLargest) 
                {
                    // print the stock's identifier and performance
                    printf("Kth Largest Stock: Identifier: %s, "
                        "Performance: %.2f\n", kthLargest->identifier,
                        kthLargest->performance);
                } 
                // otherwise, K is invalid
                else 
                {
                    // print an error message
                    printf("Invalid value for K.\n");
                }
                // free the kthLargest
                free(kthLargest);
                // exit case
                break;

            // Task 7: Find the top K frequent stocks in the market
            case 6:
                // prompt user for the value of K
                printf("Enter value of K: ");
                // read the value of K
                scanf("%d", &k);
                // display top K frequent stocks
                topFreqStocks(&market, k);
                // exit case
                break;

            // Case 7: exit the program
            case 7:
                // print a message
                puts("Come back another time!\n");
                // end case
                break;
            // default case: invalid menu choice input
            default:
                // print an error message
                printf("Invalid choice. Try again.\n");
                // end case
                break;
        }
    }
}
