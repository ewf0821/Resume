#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <pthread.h>

#define SIZE 50
#define NUM_THREADS 2

double matrix[SIZE][SIZE];
double thread_time[NUM_THREADS];
int counter[NUM_THREADS];

typedef struct thread_args
{
  int tid;
  int start;
  int end;
} thread_args;

double do_crazy_computation(int i, int j);
void *do_work(void *arg);

int main(int argc, char **argv)
{

  // creat the threads
  pthread_t threads[NUM_THREADS];
  thread_args args[NUM_THREADS];

  // set the number of iterations to be exactly half
  int iterations = SIZE / NUM_THREADS;

  // create the threads
  for (int i = 0; i < NUM_THREADS; i++)
  {
    // set their values
    args[i].tid = i;
    args[i].start = i * iterations;
    args[i].end = (i + 1) * iterations;
    pthread_create(&threads[i], NULL, do_work, &args[i]);
  }
  // join the threads
  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // print the thread times
  for (int i = 0; i < NUM_THREADS; i++)
  {
    printf("Thread %d time: %f\n", i, thread_time[i]);
  }

  // print the load imbalance
  printf("Load imbalance: %f\n", fabs(thread_time[0] - thread_time[1]));

  exit(0);
}

void *do_work(void *arg)
{
  // set up the therad arguments
  thread_args *arguments = (thread_args *)arg;

  // set the variables
  int tid = arguments->tid;
  int start = arguments->start;
  int end = arguments->end;

  // create a counter
  int local_count = 0;

  // start the timer
  double timer = omp_get_wtime();

  // do the for loop
  for (int i = start; i < end; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      matrix[i][j] = do_crazy_computation(i, j);
      // increment the counter
      local_count++;
    }
  }
  // stop the timer
  thread_time[tid] = omp_get_wtime() - timer;

  // set the global count for each tid to the counter
  counter[tid] = local_count;

  // print the number of iterations
  printf("Number of iterations for thread %d: %d\n", tid, counter[tid]);

  // return null
  return NULL;
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
