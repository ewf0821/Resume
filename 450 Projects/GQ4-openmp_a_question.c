#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 40000
#define THRESHOLD 1.0

#define NTHREADS 1

void populatedata(double *x, double *y);
double expodist(double lambda);
double computedistance(double *a, double *b);
int main(int argc, char **argv)
{

  // do not change
  srand(26);

  omp_set_num_threads(NTHREADS);

  double *x = (double *)malloc(sizeof(double) * N);
  double *y = (double *)malloc(sizeof(double) * N);
  int *z = (int *)malloc(sizeof(int) * N);
  printf("\nAllocated %f GiB", ((sizeof(double) * N * 2.0) + (sizeof(int) * N * 1.0)) / (1024 * 1024 * 1024.0));
  populatedata(x, y);

  // Write code here
  int pairs = 0;
  double start = omp_get_wtime();
#pragma omp parallel for

  for (int i = 0; i < N; i++)
  {
    if (computedistance(&x[i], &y[i]) <= THRESHOLD)
    {
      z[i] = 1;
    }
  }
  double end = omp_get_wtime();

  for (int i = 0; i < N; i++)
  {
    if (z[i] == 1)
    {
      pairs++;
    }
  }

  double total = end - start;

  printf("\n%.10lf", total);
  printf("\npairs: %d", pairs);

  free(x);
  free(y);
  free(z);
  printf("\n\n");
  return 0;
}

double computedistance(double *a, double *b)
{

  return (fabs((*a) - (*b)));
}

void populatedata(double *x, double *y)
{
  double lambda = 0.5;
  int i;
  for (i = 0; i < N; i++)
  {
    x[i] = expodist(lambda);
    y[i] = expodist(lambda);
  }
}

double expodist(double lambda)
{
  double u;
  u = rand() / (RAND_MAX + 1.0);
  return -log(1 - u) / lambda;
}