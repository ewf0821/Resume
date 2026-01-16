// header files
#include "mosaic_lib.h"

/**
 * Task 1: Reordering the Mosaic Tiles
 * Input argument: the mural as a 2D array of integer
 * Output argument: the tranposed mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void transpose(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrix[j][i] = matrix[i][j];
        }
    }
}
    

/**
 * Task 2: Realigning the Rotated Tiles
 * Input argument: the mural as a 2D array of integer
 * Output argument: the rotated mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void rotate(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrix[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrix[i][j] = matrix[SIZE - i - 1][j];
        }

    }
}


/**
 * Task 3: Restoring the Blank Spaces
 * Input argument: the mural as a 2D array of integer
 * Output argument: the restored mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void zeroMatrix(int matrix[SIZE][SIZE])
{
    //initialize bad row and col
    int badrow[SIZE] = {0};
    int badcol[SIZE] = {0};

    //loop though to check for 0's
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
           if (matrix[i][j] == 0)
           {
                //make it so the program knows theres a bad row or col
                badrow[i] = 1;
                badcol[j] = 1;
           }
        }
    }
    //loop again just for zeroing 
    for (int i = 0; i < SIZE; ++i)
    {
        //if there is a bad row
        if (badrow[i])
        {
            for (int j = 0; j < SIZE; ++j)
            {
                //set that row to have 0s
                matrix[i][j] = 0;
            }
        
        }
    }
    //loop through again but zeroing cols
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            //if col has bad 
            if(badcol[j])
            {
                matrix[i][j] = 0;
            }
        }
    }
}



/**
 * Task 4: Rotating the Mosaic Row
 * Input argument: the mural as a 2D array of integer, k number of steps
 * Output argument: the mural with a rotated row as a 2D array of integer
 * Return: none
 * Dependencies: stdlib.h - rand
 */
void rotateRow(int matrix[SIZE][SIZE], int k)
{
    int random = rand() % SIZE; 
    for(int i = 0; i < k; i++)
        {
            for (int j = 0; j < SIZE; ++j)
            {

                int temp = matrix[random][j];
                matrix[random][j] = matrix[random][j - 1];
                matrix[random][j - 1] = temp;
            }
        }
}


/**
 * Task 5: Unveiling the Spiral Mural
 * Input argument: the mural as a 2D array of integer
 * Output argument: none
 * Return: dynamically allocated array of integers
 * Dependencies: none
 */
int* spiralOrder(int matrix[SIZE][SIZE])
{
    int *array = (int*)malloc(sizeof(int)*SIZE*SIZE);
    int colIndex = 0;
    int rowIdex = 0;
    int colStartIndex = 0;
    int colEndIndex = SIZE - 1;
    int rowStartIndex = 0;
    int rowEndIntex = SIZE - 1;
    int outIndex = 0;

    while(colStartIndex != colEndIndex || rowStartIndex != rowEndIntex)
    {
        for (colIndex = colStartIndex; colIndex <= colEndIndex ; ++colIndex)
        {
            array[outIndex] = matrix[rowIdex][colIndex];
            outIndex++;
        }

        rowStartIndex++;

        for (rowIdex = rowStartIndex; rowIdex <= rowEndIntex; ++rowIdex)
        {
            array[outIndex] = matrix[rowIdex][colIndex];
            outIndex++;
        }

        colEndIndex--;


        for (colIndex = colEndIndex; colIndex>= colStartIndex; ++colIndex)
        {
            array[outIndex] = matrix[rowIdex][colIndex];
            outIndex++;
        }

        rowEndIntex--;

        for (rowIdex = rowEndIntex; rowIdex >= rowEndIntex; ++rowIdex)
        {
            array[outIndex] = matrix[rowIdex][colIndex];
            outIndex++;
        }

        colStartIndex++;
    }
    return array;
}

/**
 * Function: printMatrix (provided)
 * Input argument: the mural as a constant 2D array of integer
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void printMatrix(const int matrix[SIZE][SIZE])
{
    // traverse the mural rows
    for (int i = 0; i < SIZE; i++)
    {
        // traverse the mural columns
        for (int j = 0; j < SIZE; j++)
        {
            // print the current row-column value
            printf("%3d ", matrix[i][j]);
        }
        // break a line at the end of the row
        printf("\n");
    }
}