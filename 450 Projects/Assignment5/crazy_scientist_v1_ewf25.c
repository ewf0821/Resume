#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SIZE 50

double do_crazy_computation(int i, int j);

int main(int argc, char **argv)
{
  double mat[SIZE][SIZE];
  int i, j;

  double tstart = omp_get_wtime();

  omp_set_num_threads(2);
// modify code here
// set the parallel section
#pragma omp parallel private(i, j)
  {
    // start the timer
    int tid = omp_get_thread_num();

    // if the thread id is 0
    if (tid == 0)
    {
      for (i = 0; i < 25; i++)
      { /* loop over the rows */
        for (j = 0; j < SIZE; j++)
        { /* loop over the columns */
          mat[i][j] = do_crazy_computation(i, j);
          fprintf(stderr, ".");
        }
      }
    }
    // if the thread id is 1
    if (tid == 1)
    {
      for (i = 25; i < 50; i++)
      { /* loop over the rows */
        for (j = 0; j < SIZE; j++)
        { /* loop over the columns */
          mat[i][j] = do_crazy_computation(i, j);
          fprintf(stderr, ".");
        }
      }
    }
  }

  // end timer
  double tend = omp_get_wtime();
  // calculate the elapsed time
  double elapsed = tend - tstart;
  // print the elapsed time
  printf("Elapsed time: %f seconds\n", elapsed);

  exit(0);
}

// Crazy computation
double do_crazy_computation(int x, int y)
{
  int iter;
  double value = 0.0;

  for (iter = 0; iter < 5 * x * x * x + 1 + y * y * y + 1; iter++)
  {
    value += (cos(x * value) + sin(y * value));
  }
  return value;
}
