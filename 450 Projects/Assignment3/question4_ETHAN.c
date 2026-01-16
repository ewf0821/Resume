#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct arguments
{
    int counter;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    int total;
};

void *increment_work(void *arg);
void *decrement_work(void *arg);

int main()
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t thread1, thread2;
    struct arguments args1;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    args1.counter = 0;
    args1.total = 0;
    args1.mutex = &mutex;
    args1.cond = &cond;

    pthread_create(&thread1, NULL, increment_work, &args1);
    pthread_create(&thread2, NULL, decrement_work, &args1);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

void *increment_work(void *arg)
{
    struct arguments *args = (struct arguments *)arg;

    while (args->total < 50)
    {
        pthread_mutex_lock(args->mutex);
        while (args->counter == 10)
        {
            pthread_cond_wait(args->cond, args->mutex);
        }
        printf("Count is now (inc fn): %d\n", args->counter);
        args->counter++;
        args->total++;

        pthread_cond_signal(args->cond);
        pthread_mutex_unlock(args->mutex);
    }
    return NULL;
}

void *decrement_work(void *arg)
{
    struct arguments *args = (struct arguments *)arg;

    while (args->total <= 50)
    {
        pthread_mutex_lock(args->mutex);

        while (args->counter == 0)
        {
            pthread_cond_wait(args->cond, args->mutex);
        }
        printf("Count is now (dec fn): %d\n", args->counter);
        args->counter--;
        args->total++;

        pthread_cond_signal(args->cond);
        pthread_mutex_unlock(args->mutex);
    }
    return NULL;
}