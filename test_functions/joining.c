#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int shared_variable;
    pthread_mutex_t mutex;
} ThreadData;

void *thread_function(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = 0; i < 100; ++i) {
        pthread_mutex_lock(&data->mutex);
        data->shared_variable++;
        printf("Thread %ld: %d\n", pthread_self() % 10, data->shared_variable);
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData));

    pthread_mutex_init(&data->mutex, NULL);

    data->shared_variable = 0;

    pthread_create(&thread1, NULL, thread_function, data);

    pthread_create(&thread2, NULL, thread_function, data);

    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);


    pthread_mutex_destroy(&data->mutex);

    free(data);

    return 0;
}
