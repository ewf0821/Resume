#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct arguments
{
    int id;
    struct shared *shared;
    pthread_mutex_t *mutex;
};

struct shared
{
    int total;
    int correct;
    int buffer[3];
    int counter;
};

void *do_work(void *args);

int main()
{
    struct shared shared = {0};
    pthread_mutex_t mutex;
    pthread_t thread1, thread2, thread3;
    struct arguments args1, args2, args3;

    pthread_mutex_init(&mutex, NULL);

    args1.id = 1;
    args1.shared = &shared;
    args1.mutex = &mutex;

    args2.id = 2;
    args2.shared = &shared;
    args2.mutex = &mutex;

    args3.id = 3;
    args3.shared = &shared;
    args3.mutex = &mutex;

    pthread_create(&thread1, NULL, do_work, &args1);
    pthread_create(&thread2, NULL, do_work, &args2);
    pthread_create(&thread3, NULL, do_work, &args3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("Total sequences generated: %d\n", shared.total);
    printf("Number of correct sequences: %d\n", shared.correct);

    return 0;
}

void *do_work(void *arg)
{
    struct arguments *args = (struct arguments *)arg;
    int id = args->id;
    struct shared *shared = args->shared;
    pthread_mutex_t *mutex = args->mutex;

    while (shared->correct < 10)
    {
        pthread_mutex_lock(mutex);

        shared->buffer[shared->counter] = id;
        printf("My id: %d\n", id);
        shared->counter++;

        if (shared->counter == 3)
        {
            if (shared->buffer[0] == 1 && shared->buffer[1] == 2 && shared->buffer[2] == 3)
            {
                shared->correct++;
                printf("123\n");
            }
            shared->total++;
            shared->counter = 0;
        }
        pthread_mutex_unlock(mutex);
        usleep(500000);
    }
    return NULL;
}