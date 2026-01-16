// Include the header file for puzzle-related functions
#include "puzzle_lib.h"

// Main function
int main() 
{
    // Task 1: The Box Builder's Challenge
        // define box sizes
    int boxSizes[] = {1, 2, 3, 4, 5};

        // define container size
    int containerSize = 10;  

        // print the title
    printf("\nThe Box Builder's Challenge:\n");
    printf("----------------------------------\n");
        // print the container size
    printf("Filling up a container of size %d\n", containerSize);
        // print the number of boxes
    printf("There are %d boxes of the following sizes: {", N_BOXES);
        // traverse the array of boxes
    for (size_t i = 0; i < N_BOXES; i++)
    {
        // print each boxes size
        printf("%d", boxSizes[i]);
        // cosmetic: do not print comma in the last number
        if (i != N_BOXES-1)
        {
            printf(", ");
        }
    }
    // cosmetic: close the array printing
    puts("}");
    
    // print header for Fill Container Box task
    printf("Output: ");  

    // try to fill the container box
    if (fillContainerBox(containerSize, boxSizes, 5, 0)) 
    {
        // print the successful message
        printf("Success!\n\n");
    } 
    else 
    {
        // print the failure message
        printf("Failure!\n\n");
    }


    // Task 2: The Labyrinth Challenge
        // define the map data
    int map[4][4] =
    {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
        // create the matrix of visited paths
    bool visited[4][4] = { {false} };
        // create the array for individual paths
    char path[MAX_PATH_LENGTH];

        // print the title
    printf("The Labyrinth Challenge:\n");
    printf("--------------------------------------\n");
        // print the map size
    printf("Map Size: %dx%d (N = %d)\n\n", MAZE_SIZE, MAZE_SIZE, MAZE_SIZE);
        // traverse the rows of the map
    for (int i = 0; i < MAZE_SIZE; i++) 
    {
            // traverse the columns of the map
        for (int j = 0; j < MAZE_SIZE; j++) 
        {
            // print the current position in the map
            printf("%d ", map[i][j]);
        }
        // break a line at the end of the row
        printf("\n");
    }
    // cosmetic
    puts("\nPossible paths from entrance to exit:");

    // print each path in the map
    solveMaze(MAZE_SIZE, map, 0, 0, path, 0, visited);
    

    // Task 3: The Financial Puzzle
        // define the list of investments options
    int investments[MAX_SUBSET_SIZE] = {100, 200, 300, 500};
        // define target sum
    int targetSum = 500;
        // define the array to store each subset
    int currentSubset[MAX_SUBSET_SIZE];

        // print the title
    printf("\nThe Financial Puzzle:\n");
    printf("----------------------------------\n");
        // print the investment options
    printf("Investment options available: {");
        // traverse the array of investments
    for (int i = 0; i < MAX_SUBSET_SIZE; i++)
    {
        // print the current investiment option
        printf("%d", investments[i]);
        // cosmetic: do not print comma in the last number
        if (i != MAX_SUBSET_SIZE - 1)
        {
            printf(", ");
        }
    }
        // cosmetic: close the array printing
    puts("}");
        // print the target sum
    printf("Target sum to achieve: %d\n", targetSum);

        // find the subsets of investiment options
    printf("The following selected options are available:\n");
    findSubsets(
        investments, MAX_SUBSET_SIZE, targetSum, 0, 0, currentSubset, 0);

    // end of program message
    puts("\n\nEnd of program\n");
    // return success
    return 0;  
}
