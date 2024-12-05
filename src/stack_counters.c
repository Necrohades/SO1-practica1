#define _POSIX_C_SOURCE 200112L
#include <pthread.h>
#include "my_lib.c"

const int NUM_THREADS = 10;
const int NUM_ITERATIONS = 1e6;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct my_stack stack;  // TODO: inicializar

struct t_worker {
    int id, iterations;
};

void *worker(void *ptr) {
    int iterations = ((struct t_worker*) ptr)->iterations;
    while (iterations--) {
        pthread_mutex_lock(&mutex);
        int item = *((int*) my_stack_pop(&stack));
        pthread_mutex_unlock(&mutex);
        item++;
        pthread_mutex_lock(&mutex);
        my_stack_push(&stack, &item);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[NUM_THREADS];
    struct t_worker workers[NUM_THREADS];
    int rc, i;
    for (i = 0; i < NUM_THREADS; i++) {
        workers[i].id = i;
        workers[i].iterations = NUM_ITERATIONS;
        rc = pthread_create(threads + i, NULL, worker, (void*) worker + i);
    }
    pthread_exit(NULL);
    return 0;
}
