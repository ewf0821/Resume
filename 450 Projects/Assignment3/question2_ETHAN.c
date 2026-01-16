#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct arguments
{
    int id;
    struct shared *shared1;
    struct shared *shared2;
    pthread_mutex_t *mutex;
};

struct shared
{
    int total;
    int correct;
    int buffer[3];
    int counter;
    int win_flag;
};

void *do_work(void *args);

void *do_work2(void *args);

int main()
{
    struct shared shared1 = {0};
    struct shared shared2 = {0};
    pthread_mutex_t mutex;
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6;
    struct arguments args1, args2, args3, args4, args5, args6;

    pthread_mutex_init(&mutex, NULL);

    args1.id = 1;
    args1.shared1 = &shared1;
    args1.shared2 = &shared2;
    args1.mutex = &mutex;

    args2.id = 2;
    args2.shared1 = &shared1;
    args2.shared2 = &shared2;
    args2.mutex = &mutex;

    args3.id = 3;
    args3.shared1 = &shared1;
    args3.shared2 = &shared2;
    args3.mutex = &mutex;

    args4.id = 4;
    args4.shared2 = &shared2;
    args4.shared1 = &shared1;
    args4.mutex = &mutex;

    args5.id = 5;
    args5.shared2 = &shared2;
    args5.shared1 = &shared1;
    args5.mutex = &mutex;

    args6.id = 6;
    args6.shared2 = &shared2;
    args6.shared1 = &shared1;
    args6.mutex = &mutex;

    pthread_create(&thread1, NULL, do_work, &args1);
    pthread_create(&thread2, NULL, do_work, &args2);
    pthread_create(&thread3, NULL, do_work, &args3);

    pthread_create(&thread4, NULL, do_work2, &args4);
    pthread_create(&thread5, NULL, do_work2, &args5);
    pthread_create(&thread6, NULL, do_work2, &args6);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);

    printf("Total sequences generated team1: %d\n", shared1.total);
    printf("Number of correct sequences team1: %d\n", shared1.correct);

    printf("Total sequences generated team2: %d\n", shared2.total);
    printf("Number of correct sequences team2: %d\n", shared2.correct);

    return 0;
}

void *do_work(void *arg)
{
    struct arguments *args = (struct arguments *)arg;
    int id = args->id;
    struct shared *shared1 = args->shared1;
    struct shared *shared2 = args->shared2;
    pthread_mutex_t *mutex = args->mutex;

    while (shared1->correct < 10 && shared2->win_flag == 0)
    {
        pthread_mutex_lock(mutex);

        shared1->buffer[shared1->counter] = id;
        printf("My id: %d\n", id);
        shared1->counter++;

        if (shared1->counter == 3)
        {
            if (shared1->buffer[0] == 1 && shared1->buffer[1] == 2 && shared1->buffer[2] == 3)
            {
                shared1->correct++;
                printf("123\n");
            }
            if (shared1->correct == 10 && shared2->win_flag == 0)
            {
                shared1->win_flag = 1;
                printf("Team 1 won!\n");
            }
            shared1->total++;
            shared1->counter = 0;
        }
        pthread_mutex_unlock(mutex);
        usleep(500000);
    }

    return NULL;
}

void *do_work2(void *arg)
{
    struct arguments *args = (struct arguments *)arg;
    int id = args->id;
    struct shared *shared1 = args->shared1;
    struct shared *shared2 = args->shared2;
    pthread_mutex_t *mutex = args->mutex;

    while (shared2->correct < 10 && shared1->win_flag == 0)
    {
        pthread_mutex_lock(mutex);

        shared2->buffer[shared2->counter] = id;
        printf("My id: %d\n", id);
        shared2->counter++;

        if (shared2->counter == 3)
        {
            if (shared2->buffer[0] == 4 && shared2->buffer[1] == 5 && shared2->buffer[2] == 6)
            {
                shared2->correct++;
                printf("456\n");
            }
            if (shared2->correct == 10 && shared1->win_flag == 0)
            {
                shared2->win_flag = 1;
                printf("Team 2 won!\n");
            }
            shared2->total++;
            shared2->counter = 0;
        }
        pthread_mutex_unlock(mutex);
        usleep(500000);
    }

    return NULL;
}