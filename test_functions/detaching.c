#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int shared_variable;
    pthread_mutex_t mutex;
} ThreadData;

void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&data->mutex);
        data->shared_variable++;
        printf("Thread %ld: %d\n", pthread_self() % 10, data->shared_variable);
        pthread_mutex_unlock(&data->mutex);
    }

    free(data);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    ThreadData *data1 = (ThreadData *)malloc(sizeof(ThreadData));

    pthread_mutex_init(&data1->mutex, NULL);

    data1->shared_variable = 0;

    pthread_create(&thread1, NULL, thread_function, data1);

    pthread_create(&thread2, NULL, thread_function, data1);


    sleep(2);
    pthread_detach(thread1);
    pthread_detach(thread2);


    pthread_mutex_destroy(&data1->mutex);
    pthread_mutex_destroy(&data1->mutex);

    free(data1);

    return 0;
}