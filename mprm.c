#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


#define NUM_CHILDREN 3
#define NUM_RESOURCES 2
#define BUFFER_SIZE 100

sem_t *semaphore;
int pipes[NUM_CHILDREN][2];

void child_process(int id) {

    // TODO: Implement child process logic

    printf("Child process: PID = %d\n", getpid());
    printf("Thread %d: Attempting to acquire resource\n", id);

    sem_wait(&semaphore);
    printf("Thread %d: Resource acquired\n", id);

    // Simulate using the resource
    for (long i = 0; i < 1000000000; i++) {
        // Perform some meaningless calculation
        double result = 3.14159 * i;
    }

    printf("Thread %d: Releasing resource\n", id);
    sem_post(&semaphore);

    close(pipes[id][0]); // Close unused read end

    printf("Child: Sending data...\n");
    const char *message = "Completed Work!";
    int bytes_read = write(pipes[id][1], message, strlen(message)+1 );

    close(pipes[id][1]);

    free(id);
    return NULL;

}

int main() {

    int priority = nice(0);
    // Initialize semaphore with NUM_RESOURCES
    sem_init(&semaphore, 0, NUM_RESOURCES);

    if (pipe(pipes) == -1) {
        perror("pipe");
        exit(1);
    }

    // TODO: Fork child processes

    pid_t pids[10];
    int i;
    int n = 10;

    /* Start children. */
    for (i = 0; i < n; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            child_process(pids[i]);
            exit(0);
        }
    }

    // TODO: Set different priorities for children
    
    // TODO: Wait for child processes and read from pipes

    close(pipes[1]); // Close unused write end
    printf("Parent: Sending message...\n");
    read(pipes[0], buffer, BUFFER_SIZE);
    close(pipes[1]);
    wait(NULL); // Wait for child to finish
    
    // TODO: Clean up resources
    sem_destroy(&semaphore);
    return 0;
}
