#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS 5
#define NUM_RESOURCES 3
sem_t resource_semaphore;
void* worker(void* arg) {
 int id = *(int*)arg;
 printf("Thread %d: Attempting to acquire resource\n", id);

 sem_wait(&resource_semaphore);
 printf("Thread %d: Resource acquired\n", id);

 // Simulate using the resource
 sleep(rand() % 3 + 1);

 printf("Thread %d: Releasing resource\n", id);
 sem_post(&resource_semaphore);

 free(arg);
 return NULL;
}
int main() {
 pthread_t threads[NUM_THREADS];

 // Initialize semaphore with NUM_RESOURCES
 sem_init(&resource_semaphore, 0, NUM_RESOURCES);

 for (int i = 0; i < NUM_THREADS; i++) {
 int* id = malloc(sizeof(int));
 *id = i;
 pthread_create(&threads[i], NULL, worker, id);
 }

 for (int i = 0; i < NUM_THREADS; i++) {
 pthread_join(threads[i], NULL);
 }

 sem_destroy(&resource_semaphore);
 return 0;
}
