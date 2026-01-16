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

  double thread_time[2];

  double tstart = omp_get_wtime();

  omp_set_num_threads(2);
// modify code here
#pragma omp parallel private(i, j)
  {
    int tid = omp_get_thread_num();
    double total = omp_get_wtime();

#pragma omp for schedule(static) nowait
    for (i = 0; i < SIZE; i++)
    { /* loop over the rows */
      for (j = 0; j < SIZE; j++)
      { /* loop over the columns */
        mat[i][j] = do_crazy_computation(i, j);
        fprintf(stderr, ".");
      }
    }

    thread_time[tid] = omp_get_wtime() - total;
  }

  double tend = omp_get_wtime();
  double elapsed = tend - tstart;

  printf("Elapsed time: %f seconds\n", elapsed);
  printf("Thread 1 Time: %f\n", thread_time[0]);
  printf("Thread 2 Time: %f\n", thread_time[1]);
  printf("Load Imbalance: %f\n", fabs(thread_time[0] - thread_time[1]));

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
