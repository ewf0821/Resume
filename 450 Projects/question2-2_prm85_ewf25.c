//compilation instructions/examples:    
//gcc -fopenmp point_epsilon_starter.c -o point_epsilon_starter
//sometimes you need to link against the math library with -lm:
//gcc -fopenmp point_epsilon_starter.c -lm -o point_epsilon_starter

//math library needed for the square root

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "omp.h"

//N is 100000 for the submission. However, you may use a smaller value of testing/debugging.
//#define N 100000
// debug value
#define N 1000
//#define N 10
//Do not change the seed, or your answer will not be correct
#define SEED 72


struct pointData{
    double x;
    double y;
};


struct hashMap {
    double cellSize;
    //struct pointData data;
    double x;
    double y;
    //struct hashMap *nextPtr;
};
void generateDataset(struct pointData * data);


int main(int argc, char *argv[])
{


    //Read epsilon distance from command line
    if (argc!=2)
    {
        printf("\nIncorrect number of input parameters. Please input an epsilon distance.\n");
	    return 0;
    }
	
	
    char inputEpsilon[20];
    strcpy(inputEpsilon,argv[1]);
    double epsilon=atof(inputEpsilon);



    //generate dataset:
    struct pointData * data;
    data=(struct pointData*)malloc(sizeof(struct pointData)*N);
    printf("\nSize of dataset (MiB): %f",(2.0*sizeof(double)*N*1.0)/(1024.0*1024.0));
    generateDataset(data);


    //change OpenMP settings:
    omp_set_num_threads(1);

    double tstart=omp_get_wtime();

	
    //Write your code here:
    //The data you need to use is stored in the variable "data", 
    //which is of type pointData

    //find the mins and maxes
    double minX=data[0].x;
    double maxX=data[0].x;
    double minY = data[0].y;
    double maxY = data[0].y;
    for (int i=1; i<N; i++) {
        if (data[i].x < minX) {
            minX = data[i].x;
        }
        if (data[i].x > maxX) {
            maxX = data[i].x;
        }
        if (data[i].y < minY) {
            minY = data[i].y;
        }
        if (data[i].y > maxY) {
            maxY = data[i].y;
        }
    }

    //create the grid 
    int gridX = (int)((maxX - minX) / epsilon);
    int gridY = (int)((maxY - minY) / epsilon);
    

    //allocate space for cells (we should use a fixed size dynamic too complicated)
    int MAX_CELL_SIZE = 1000; // should this be N?
    struct pointData cell[gridX][gridY];
    //MORE HERE
    
    
    //put the points in the grid
    for(int i=0; i<N; i++) {
        int cellX = (int)((data[i].x - minX) / epsilon);
        int cellY = (int)((data[i].y - minY) / epsilon);
        if(cellX < gridX && cellY < gridY) {
            cell[cellX][cellY].x = data[i].x;
            cell[cellX][cellY].y = data[i].y;
        }
    }

    //find total pairs
    long totalCount = 0;
    //parallelize
    #pragma omp parallel for reduction(+:totalCount)
    //for i to N
    for(int i = 0; i < N; i++)
    {
        //find the cell
        int cellX = (int)((data[i].x - minX) / epsilon);
        int cellY = (int)((data[i].y - minY) / epsilon);
        //check the neighbors
        for (int changeX = -1; changeX <= 1; changeX++) 
        {
            for(int changeY = -1; changeY <= 1; changeY++) 
            {
               //check if in bounds
               int x = cellX + changeX;
               int y = cellY + changeY;
               //if it is in the bounds 
               if (x >= 0 && x <= gridX && y >= 0 && y <= gridY) 
               {
                    for (int j = 0; j < y; j++) 
                    {
                        //get the euclidean distance
                        double distance = sqrt(pow(data[i].x - cell[x][j].x, 2) + pow(data[i].y - cell[x][j].y, 2));
                        //if distance is less the epsilon
                        if (distance <= epsilon) 
                        {
                            //add to total
                            totalCount += 1;
                        }
                   }
               }            
            }
        }
    }
    //end time and print count and time
    double tend=omp_get_wtime();
	printf("\ntotalSum: %ld", totalCount);
    printf("\nTotal time (s): %f",tend-tstart);


    free(data);
    printf("\n");
    return 0;
}


//Do not modify the dataset generator or you will get the wrong answer
void generateDataset(struct pointData * data)
{

    //seed RNG
    srand(SEED);


    for (unsigned int i=0; i<N; i++){
        data[i].x=1000.0*((double)(rand()) / RAND_MAX);	
        data[i].y=1000.0*((double)(rand()) / RAND_MAX);	
    }


}

double euclidiean_distance()
{
    //return sqrt(pow(data[i].x - cell[x][y][j].x, 2) + pow(data[i].y - cell[x][y][j].y, 2));
    return 0.0;
}