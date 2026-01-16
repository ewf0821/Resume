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
    int counter;
};

void *do_work(void *arg);

int main()
{
    struct shared shared = {0};
    pthread_mutex_t mutex;
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6,
        thread7, thread8, thread9, thread10;
    struct arguments args1, args2, args3, args4, args5, args6,
        args7, args8, args9, args10;

    pthread_mutex_init(&mutex, NULL);

    args1.id = 0;
    args1.shared = &shared;
    args1.mutex = &mutex;

    args2.id = 1;
    args2.shared = &shared;
    args2.mutex = &mutex;

    args3.id = 2;
    args3.shared = &shared;
    args3.mutex = &mutex;

    args4.id = 3;
    args4.shared = &shared;
    args4.mutex = &mutex;

    args5.id = 4;
    args5.shared = &shared;
    args5.mutex = &mutex;

    args6.id = 5;
    args6.shared = &shared;
    args6.mutex = &mutex;

    args7.id = 6;
    args7.shared = &shared;
    args7.mutex = &mutex;

    args8.id = 7;
    args8.shared = &shared;
    args8.mutex = &mutex;

    args9.id = 8;
    args9.shared = &shared;
    args9.mutex = &mutex;

    args10.id = 9;
    args10.shared = &shared;
    args10.mutex = &mutex;

    pthread_create(&thread1, NULL, do_work, &args1);
    pthread_create(&thread2, NULL, do_work, &args2);
    pthread_create(&thread3, NULL, do_work, &args3);
    pthread_create(&thread4, NULL, do_work, &args4);
    pthread_create(&thread5, NULL, do_work, &args5);
    pthread_create(&thread6, NULL, do_work, &args6);
    pthread_create(&thread7, NULL, do_work, &args7);
    pthread_create(&thread8, NULL, do_work, &args8);
    pthread_create(&thread9, NULL, do_work, &args9);
    pthread_create(&thread10, NULL, do_work, &args10);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    pthread_join(thread8, NULL);
    pthread_join(thread9, NULL);
    pthread_join(thread10, NULL);

    printf("Total: %d\n", shared.total);

    return 0;
}

void *do_work(void *arg)
{
    struct arguments *args = (struct arguments *)arg;
    int id = args->id;
    struct shared *shared = args->shared;
    pthread_mutex_t *mutex = args->mutex;

    while (shared->total < 990)
    {
        pthread_mutex_lock(mutex);

        if (shared->counter == id && shared->total < 990)
        {
            shared->total += id;
            printf("My num: %d, total: %d\n", id, shared->total);
            shared->counter++;
        }
        shared->counter %= 10;
        pthread_mutex_unlock(mutex);
    }
    return NULL;
}
