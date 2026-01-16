// header files
#include "puzzle_lib.h"  

/**
 * Task 1: Fill the container box
 * Arguments: - the size of the container
 *            - an array of boxes to be placed in the container
 *            - the number of boxes in the array
 *            - the index in the array where the placement should start
 * Return: true if a combination of boxe's sizes is equal to the container size
 *         false otherwise
 * Dependencies: fillContainerBox (recursive)
 */
bool fillContainerBox(
    int containerSize, int* boxSizes, int numBoxes, int index)
{
    if(containerSize == 0)
    {
        //means that we completed the function
        return true;
    }
    if(index >= numBoxes || containerSize < 0)
    {
        //check to see if there are no more boxes avaliable
        //or if we used to many boxes
        return false;
    }
    //first recursion that acrtually does the math
    if(fillContainerBox(containerSize - boxSizes[index], boxSizes, numBoxes, 
            index + 1))
    {
        return true;
    }
    //if that fails it just increases the index
    return fillContainerBox(containerSize, boxSizes, numBoxes, index + 1);

}


/**
 * Task 2: The labyrinth challenge
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
    bool visited[size][size])
{
    //base cases
    if(x == size - 1 && y == size - 1)
    {
        //print path here
        path[pathIndex] = '\0';
        printf("%s \n", path);
        return;
    }
    //set visted tiles to true
    visited[x][y] = true;
    //check to see if safe and if safe to the right add 'r' to array
    if(isSafe(size, maze, x, y + 1, visited))
        {
            path[pathIndex] = 'R';
            solveMaze(size, maze, x, y  + 1, path, pathIndex + 1, visited);
        }
    //same but add d
    if(isSafe(size, maze, x + 1, y, visited))
        {
            path[pathIndex] = 'D';
            solveMaze(size, maze, x + 1, y, path, pathIndex + 1, visited);
        }
        //same but for l
    if(isSafe(size, maze, x, y - 1, visited))
        {
            path[pathIndex] = 'L';
            solveMaze(size, maze, x, y - 1, path, pathIndex + 1, visited);        
        }
        //same but for u
    if(isSafe(size, maze, x - 1, y, visited))
        {
            path[pathIndex] = 'U';
            solveMaze(size, maze, x - 1, y, path, pathIndex + 1, visited);
        }
        //if it cant go anywhere set the current location to false and rewind
    visited[x][y] = false;
}


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
    bool visited[size][size])
{
    return (x >= 0
        && x < size
        && y >= 0
        && y < size
        && maze[x][y] == 1
        && (!visited[x][y] || visited == NULL));
}

/**
 * Task 3: The financial puzzle
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
    int currentSum, int currentSubset[], int subsetIndex)
{
    //base case
    if(currentSum == target)
    {
        //print the left bracket
        printf("{");
        //printing each number and adding commas in between them
        for(int i = 0; i < subsetIndex; i++)
            {
                printf("%d", currentSubset[i]);
                if(subsetIndex - 1 != i)
                {
                    printf(",");
                }
            }
            //print the right bracket and new line
        printf("}");
        printf("\n");
        return; 
    }
    //base case if the whole thing fails
    if(index >= numInvestments || currentSum > target)
    {
        return;
    }
    //we set the current index of investments to the current index in subsets
    currentSubset[subsetIndex] = investments[index];
    //runs findSubsets and increases both indexes and adds the index value to 
    //current sum
    findSubsets(investments, numInvestments, target, index + 1,
        currentSum + investments[index], currentSubset, subsetIndex + 1);

    //increments index if the value cant be added
    findSubsets(investments, numInvestments, target, index + 1,
        currentSum, currentSubset, subsetIndex);
}