#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void random_sleep(double a, double b);
void *housekeeper(void *args);
int main(int argc, char **argv);

#define NUM_ITERATIONS 10
#define NUM_WASHERS 3
#define NUM_DRYERS 3

// Helper function to sleep a random number of microseconds
// picked between two bounds (provided in seconds)
// pass 0.2 and 0.5 into this function as arguments
void random_sleep(double lbound_sec, double ubound_sec)
{
  int num_usec;
  num_usec = lbound_sec * 1000000 +
             (int)((ubound_sec - lbound_sec) * 1000000 * ((double)(rand()) / RAND_MAX));
  usleep(num_usec);
  return;
}

typedef struct
{
  int id;
  int type;
  void *shared;

} housekeeper_args;

typedef struct
{
  int num_washers;
  int num_dryers;
  pthread_mutex_t lock;
  pthread_cond_t washer_cond;
  pthread_cond_t dryer_cond;
} shared;

void *housekeeper(void *args)
{
  housekeeper_args *keeper_args = (housekeeper_args *)args;
  shared *shared_data = keeper_args->shared;

  // char to hold the current name
  const char *name;

  // if 0 its a washer
  if (keeper_args->type == 0)
  {
    name = "Washer housekeeper";
  }
  // if 1 its a dryer
  else if (keeper_args->type == 1)
  {
    name = "Dryer housekeeper";
  }
  // else its both which would be 2
  else if (keeper_args->type == 2)
  {
    name = "Washer/dryer housekeeper";
  }

  // for i to iterations
  for (int i = 0; i < NUM_ITERATIONS; i++)
  {
    // print whichever thread is working
    printf("[%s %d] is working...\n", name, keeper_args->id);
    // set a random sleep
    random_sleep(0.2, 0.5);

    // if the therad is a washer
    if (keeper_args->type == 0)
    {
      // lock
      pthread_mutex_lock(&shared_data->lock);
      // check to see if there is a washer avaliable
      while (shared_data->num_washers == 0)
      {
        // if not wait
        pthread_cond_wait(&shared_data->washer_cond, &shared_data->lock);
      }
      // if there is decrement the numebr of washers
      shared_data->num_washers--;
      // say which thread wants and gets a washer
      printf("[%s %d] wants a washer...\n", name, keeper_args->id);
      printf("[%s %d] has got a washer...\n", name, keeper_args->id);

      // unlock
      pthread_mutex_unlock(&shared_data->lock);

      // print for putting laundry in the washer and taking stuff out
      printf("[%s %d] has put laundry in the washer...\n", name, keeper_args->id);
      // sleep in the middle so that its a fake time
      random_sleep(0.2, 0.5);
      printf("[%s %d] has taken articles out of the washer...\n", name, keeper_args->id);

      // get the lock again
      pthread_mutex_lock(&shared_data->lock);
      // increment the number of avaliable washers
      shared_data->num_washers++;
      // print finished with the washer
      printf("[%s %d] has finished with the washer...\n", name, keeper_args->id);
      // signal washers to wake up
      pthread_cond_signal(&shared_data->washer_cond);
      // give up the lock
      pthread_mutex_unlock(&shared_data->lock);
    }
    // if its a dryer
    if (keeper_args->type == 1)
    {
      // aquire the lock
      pthread_mutex_lock(&shared_data->lock);
      // while there are 0 dryers avaliable
      while (shared_data->num_dryers == 0)
      {
        // wait until this is one avaliable
        pthread_cond_wait(&shared_data->dryer_cond, &shared_data->lock);
      }
      // decrement the number of dryers
      shared_data->num_dryers--;
      // print that you want and got a dryer
      printf("[%s %d] wants a dryer...\n", name, keeper_args->id);
      printf("[%s %d] has got a dryer...\n", name, keeper_args->id);

      // give up your lock
      pthread_mutex_unlock(&shared_data->lock);

      // print that youre putting laundry in the dryer and taking it out
      printf("[%s %d] has put laundry in the dryer...\n", name, keeper_args->id);
      // sleep in the middle to simulate time
      random_sleep(0.2, 0.5);
      printf("[%s %d] has taken articles out of the dryer...\n", name, keeper_args->id);

      // aquire the lock again
      pthread_mutex_lock(&shared_data->lock);
      // increment the number of avaliable dryers
      shared_data->num_dryers++;
      // print that its finished with the dryer
      printf("[%s %d] has finished with the dryer...\n", name, keeper_args->id);
      // signal other dryers to wake up
      pthread_cond_signal(&shared_data->dryer_cond); // give up the lock
      pthread_mutex_unlock(&shared_data->lock);
    }
    // else its both washer and dryer
    else if (keeper_args->type == 2)
    {
      // aquire the lock
      pthread_mutex_lock(&shared_data->lock);
      // while there are 0 washers avaliable
      while (shared_data->num_washers == 0)
      {
        // wait until this is one avaliable
        pthread_cond_wait(&shared_data->washer_cond, &shared_data->lock);
      }

      // decrement the number of washers
      shared_data->num_washers--;
      // print that you want and got a washer
      printf("[%s %d] wants a washer...\n", name, keeper_args->id);
      printf("[%s %d] has got a washer...\n", name, keeper_args->id);
      // give up the lock
      pthread_mutex_unlock(&shared_data->lock);

      // aquire the lock
      pthread_mutex_lock(&shared_data->lock);
      // while there are 0 dryers avaliable
      while (shared_data->num_dryers == 0)
      {
        // wait until this is one avaliable
        pthread_cond_wait(&shared_data->dryer_cond, &shared_data->lock);
      }
      // decrement the number of dryers
      shared_data->num_dryers--;
      // print that you want and got a washer
      printf("[%s %d] wants a dryer...\n", name, keeper_args->id);
      printf("[%s %d] has got a dryer...\n", name, keeper_args->id);
      // give up the lock
      pthread_mutex_unlock(&shared_data->lock);

      // print that you put laundry in the dryer and youre taking it out
      printf("[%s %d] has started using both the washer and dryer...\n", name, keeper_args->id);
      // sleep to show time passed
      random_sleep(0.2, 0.5);
      printf("[%s %d] has taken articles out of the washer and dryer...\n", name, keeper_args->id);

      // aquire the lock
      pthread_mutex_lock(&shared_data->lock);
      // increment the number of washers
      shared_data->num_washers++;
      // say that youre finished with the washer
      printf("[%s %d] has finished with the washer...\n", name, keeper_args->id);
      // increment the number of dryers
      shared_data->num_dryers++;
      // print that youre done with the dryer
      printf("[%s %d] has finished with the dryer...\n", name, keeper_args->id);
      // signal washer and dryer
      pthread_cond_signal(&shared_data->washer_cond);
      pthread_cond_signal(&shared_data->dryer_cond);
      // give up the lock
      pthread_mutex_unlock(&shared_data->lock);
    }
  }
  // return NULL
  return NULL;
}

// main function
int main(int argc, char **argv)
{

  int seed;
  int num_washer_staff;
  int num_dryer_staff;
  int num_washer_dryer_staff;

  // Process command-line arguments
  if (argc != 5)
  {
    fprintf(stderr, "Usage: %s <# washers only> <# dryers only> <# both washers and dryers> <seed>\n", argv[0]);
    exit(1);
  }

  if ((sscanf(argv[1], "%d", &num_washer_staff) != 1) ||
      (sscanf(argv[2], "%d", &num_dryer_staff) != 1) ||
      (sscanf(argv[3], "%d", &num_washer_dryer_staff) != 1) ||
      (sscanf(argv[4], "%d", &seed) != 1) ||
      (num_washer_staff < 1) ||
      (num_dryer_staff < 1) ||
      (num_washer_dryer_staff < 1) ||
      (seed < 0))
  {
    fprintf(stderr, "Invalid command-line arguments... Aborting\n");
    exit(1);
  }

  /* Seed the random number generator */
  srand(seed);

  // Create shared data structure
  shared shared_data;
  shared_data.num_washers = NUM_WASHERS;
  shared_data.num_dryers = NUM_DRYERS;
  pthread_mutex_init(&shared_data.lock, NULL);
  pthread_cond_init(&shared_data.washer_cond, NULL);
  pthread_cond_init(&shared_data.dryer_cond, NULL);

  int total_threads = num_washer_staff + num_dryer_staff + num_washer_dryer_staff;
  pthread_t *threads = malloc(total_threads * sizeof(pthread_t));

  int thread_number = 0;

  for (int i = 0; i < num_washer_staff; i++)
  {
    housekeeper_args *args = malloc(sizeof(housekeeper_args));

    args->id = i;
    args->type = 0;
    args->shared = &shared_data;

    pthread_create(&threads[thread_number], NULL, housekeeper, args);
    thread_number++;
  }
  for (int i = 0; i < num_dryer_staff; i++)
  {
    housekeeper_args *args = malloc(sizeof(housekeeper_args));

    args->id = i;
    args->type = 1;
    args->shared = &shared_data;

    pthread_create(&threads[thread_number], NULL, housekeeper, args);
    thread_number++;
  }
  for (int i = 0; i < num_washer_dryer_staff; i++)
  {
    housekeeper_args *args = malloc(sizeof(housekeeper_args));

    args->id = i;
    args->type = 2;
    args->shared = &shared_data;

    pthread_create(&threads[thread_number], NULL, housekeeper, args);
    thread_number++;
  }

  for (int i = 0; i < total_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }

  free(threads);
  exit(0);
}
